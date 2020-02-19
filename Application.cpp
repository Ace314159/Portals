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

	glm::mat4 portal1Model = glm::translate(glm::mat4(1), { 0, 2, -room.getRoomSize() + 0.01 });

	glm::mat4 portal2Model = glm::translate(glm::mat4(1), { -room.getRoomSize() + 0.01, 2, 0 });
	portal2Model = glm::rotate(portal2Model, glm::radians(90.0f), { 0, 1, 0 });
;	while(window.isOpen()) {
		camera.update();

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		room.draw();
		
		// Portal 1
		quadShader.setVec4("color", {1, 1, 1, 1});
		quadShader.setMat4("model", portal1Model);
		portal.draw();
		
		// Portal 2
		quadShader.setVec4("color", { 1, 1, 1, 1 });
		quadShader.setMat4("model", portal2Model);
		portal.draw();

		window.swapBuffers();
		glfwPollEvents();
	}
}