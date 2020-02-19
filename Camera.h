#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"

class Camera {
public:
	Camera(const Window& window);

	void update();
	void setCursorPos(double x, double y);
	inline void enable() { 
		enabled = true;
		glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	};
	inline void disable() {
		enabled = false;
		glfwSetInputMode(window.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	};
	inline void setProjection() {
		uniformBuffer.projection = glm::perspective(glm::radians(45.0f),
			(float)window.getWidth() / window.getHeight(), 0.1f, 100.0f);
		glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(uniformBuffer.projection),
			glm::value_ptr(uniformBuffer.projection));
	}
private:

	struct UniformBuffer {
		glm::mat4 projection;
		glm::mat4 view;
	};

	const Window& window;

	GLuint UBO;
	UniformBuffer uniformBuffer;

	glm::vec3 pos{ 0, 0, 0 };
	glm::vec3 up{ 0, 1, 0 };
	glm::vec3 front;

	double prevTime = glfwGetTime();
	const float baseSpeed = 1;
	const double sensitivity = 0.1;

	double yaw = -90;
	double pitch = 0;
	double prevX, prevY;
	bool enabled = true;
};
