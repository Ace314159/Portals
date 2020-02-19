#include "stdafx.h"

#include "Camera.h"
#include "Quad.h"
#include "Room.h"
#include "Shader.h"
#include "Window.h"

int main() {
	Window window;
	Camera camera(window);
	Shader quadShader("quad");

	Room room(quadShader);
	
	Quad portal({ -1.5, -2, 0 }, { 3, 4 });

	glm::mat4 portal1Model = glm::translate(glm::mat4(1), { 0, 2, -room.getRoomSize() });

	glm::mat4 portal2Model = glm::translate(glm::mat4(1), { -room.getRoomSize(), 2, 0 });
	portal2Model = glm::rotate(portal2Model, glm::radians(90.0f), { 0, 1, 0 });

;	while(window.isOpen()) {
		camera.update();

		glClearColor(0, 0, 0, 1);
		glStencilMask(0xFF);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

		// Set stencil buffer for portal 1
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);
		quadShader.use();
		quadShader.setVec4("color", { 1, 1, 1, 1 });
		quadShader.setMat4("model", portal1Model);
		portal.draw();

		// Draw into portal
		glStencilFunc(GL_EQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);
		const glm::mat4 oldCameraView = camera.getView();
		camera.setView(oldCameraView * portal1Model *
			glm::rotate(glm::mat4(1), glm::radians(180.0f), { 0, 1, 0 }) * glm::inverse(portal2Model));
		room.draw();
		camera.setView(oldCameraView);
		
		// Set stencil buffer for portal 2
		glStencilFunc(GL_ALWAYS, 2, 0xFF);
		glStencilMask(0xFF);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);
		quadShader.use();
		quadShader.setVec4("color", { 1, 1, 1, 1 });
		quadShader.setMat4("model", portal2Model);
		portal.draw();

		// Draw into portal
		glStencilFunc(GL_EQUAL, 2, 0xFF);
		glStencilMask(0x00);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);
		camera.setView(oldCameraView * portal2Model *
			glm::rotate(glm::mat4(1), glm::radians(180.0f), { 0, 1, 0 }) * glm::inverse(portal1Model));
		room.draw();
		camera.setView(oldCameraView);

		// Draw rest of the room
		glStencilFunc(GL_EQUAL, 0, 0xFF);
		quadShader.use();
		room.draw();

		window.swapBuffers();
		glfwPollEvents();
	}
}