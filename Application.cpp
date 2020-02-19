#include "stdafx.h"

#include "Camera.h"
#include "Window.h"
#include "Quad.h"

int main() {
	Window window;
	Shader quadShader("quad");
	int roomSize = 10;
	Quad wall({ -roomSize, -roomSize, 0 }, { 2 * roomSize, 2 * roomSize });
	Quad portal({ -1.5, -2, 0 }, { 3, 4 });
	Camera camera(window);

	glm::mat4 floorModel = glm::rotate(glm::mat4(1), glm::radians(90.0f), { 1, 0, 0 });

	glm::mat4 wall1Model = glm::translate(glm::mat4(1), { roomSize, roomSize, 0 });
	wall1Model = glm::rotate(wall1Model, glm::radians(90.0f), { 0, 1, 0 });

	glm::mat4 wall2Model = glm::translate(glm::mat4(1), { -roomSize, roomSize, 0 });
	wall2Model = glm::rotate(wall2Model, glm::radians(90.0f), { 0, 1, 0 });

	glm::mat4 wall3Model = glm::translate(glm::mat4(1), { 0, roomSize, roomSize });
	wall3Model = glm::rotate(wall3Model, glm::radians(90.0f), { 0, 0, 1 });

	glm::mat4 wall4Model = glm::translate(glm::mat4(1), { 0, roomSize, -roomSize });
	wall4Model = glm::rotate(wall4Model, glm::radians(90.0f), { 0, 0, 1 });

	glm::mat4 portal1Model = glm::translate(glm::mat4(1), { 0, 2, -roomSize + 0.01 });

	glm::mat4 portal2Model = glm::translate(glm::mat4(1), { -roomSize + 0.01, 2, 0 });
	portal2Model = glm::rotate(portal2Model, glm::radians(90.0f), { 0, 1, 0 });
;	while(window.isOpen()) {
		camera.update();

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		quadShader.use();
		// Floor
		quadShader.setVec4("color", { 0.75, 0.5, 0.5, 1 });
		quadShader.setMat4("model", floorModel);
		wall.draw();
		// Wall 1
		quadShader.setVec4("color", { 0, 0.5, 0, 1 });
		quadShader.setMat4("model", wall1Model);
		wall.draw();
		// Wall 2
		quadShader.setVec4("color", { 0.5, 0, 0, 1 });
		quadShader.setMat4("model", wall2Model);
		wall.draw();
		// Wall 3
		quadShader.setVec4("color", { 0, 0, 0.5, 1 });
		quadShader.setMat4("model", wall3Model);
		wall.draw();
		// Wall 4
		quadShader.setVec4("color", { 0.5, 0.5, 0.5, 1 });
		quadShader.setMat4("model", wall4Model);
		wall.draw();

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