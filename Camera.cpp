#include "stdafx.h"

#include "Camera.h"

Camera::Camera(Window& window) : window(window) {
	glfwSetWindowUserPointer(window.window, this);
	glfwSetCursorPosCallback(window.window, [](GLFWwindow* window, double x, double y) {
		((Camera*)glfwGetWindowUserPointer(window))->setCursorPos(x, y);
	});
	glfwSetMouseButtonCallback(window.window, [](GLFWwindow* window, int button, int action, int mods) {
		if(button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
			((Camera*)glfwGetWindowUserPointer(window))->enable();
		}
	});

	prevX = window.getWidth() / 2;
	prevY = window.getHeight() / 2;

	glGenBuffers(1, &UBO);

	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(uniformBuffer), nullptr, GL_DYNAMIC_DRAW);
	setProjection(window.getWidth(), window.getHeight());

	glBindBufferRange(GL_UNIFORM_BUFFER, 0, UBO, 0, 2 * sizeof(glm::mat4));
	enable();
}

void Camera::update() {
	if(glfwGetKey(window.window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		disable();
		return;
	}
	if(!enabled) return;

	double curTime = glfwGetTime();
	double deltaTime = curTime - prevTime;
	prevTime = curTime;
	float speed = float(baseSpeed * deltaTime);

	glm::vec3 dPos(0, 0, 0);
	glm::vec3 front0Y = glm::normalize(glm::vec3(front.x, 0, front.z));
	if(glfwGetKey(window.window, GLFW_KEY_W) == GLFW_PRESS) dPos += front0Y * speed;
	if(glfwGetKey(window.window, GLFW_KEY_S) == GLFW_PRESS) dPos -= front0Y * speed;
	if(glfwGetKey(window.window, GLFW_KEY_A) == GLFW_PRESS)
		dPos -= glm::normalize(glm::cross(front0Y, up)) * speed;
	if(glfwGetKey(window.window, GLFW_KEY_D) == GLFW_PRESS)
		dPos += glm::normalize(glm::cross(front0Y, up)) * speed;
	if(glfwGetKey(window.window, GLFW_KEY_SPACE) == GLFW_PRESS)
		dPos += up * speed;
	if(glfwGetKey(window.window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		dPos -= up * speed;

	pos += dPos;
	float d = 0.1f;
	if(pos.x > -1.5 && pos.x < 1.5 && pos.z < -10 + d) {
		pos.z = 1.5 - (1.5 - pos.x);
		pos.x = -10 + d;
		yaw += 90;
		front = glm::normalize(glm::vec3(
			cos(glm::radians(pitch)) * cos(glm::radians(yaw)),
			sin(glm::radians(pitch)),
			cos(glm::radians(pitch)) * sin(glm::radians(yaw))
		));
	}

	if(pos.z > -1.5 && pos.z < 1.5 && pos.x < -10 + d) {
		pos.x = 1.5 - (1.5 - pos.z);
		pos.z = -10 + d;
		yaw -= 90;
		front = glm::normalize(glm::vec3(
			cos(glm::radians(pitch)) * cos(glm::radians(yaw)),
			sin(glm::radians(pitch)),
			cos(glm::radians(pitch)) * sin(glm::radians(yaw))
		));
	}

	uniformBuffer.view = glm::lookAt(pos, pos + front, up);

	glBufferSubData(GL_UNIFORM_BUFFER, sizeof(glm::mat4), sizeof(glm::mat4), &uniformBuffer.view);
}

void Camera::setCursorPos(double x, double y) {
	double dX = (x - prevX) * sensitivity;
	double dY = -(y - prevY) * sensitivity; // Negative since y values increase from top to bottom
	prevX = x;
	prevY = y;
	if(!enabled) return;

	yaw += dX;
	pitch += dY;
	if(pitch > 89) pitch = 89;
	else if(pitch < -89) pitch = -89;

	front = glm::normalize(glm::vec3(
		cos(glm::radians(pitch)) * cos(glm::radians(yaw)),
		sin(glm::radians(pitch)),
		cos(glm::radians(pitch)) * sin(glm::radians(yaw))
	));
}
