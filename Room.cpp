#include "stdafx.h"

#include "Room.h"

Room::Room(const Shader& quadShader) : quadShader(quadShader) {
	floorModel = glm::rotate(glm::mat4(1), glm::radians(90.0f), { -1, 0, 0 });

	wall1Model = glm::translate(glm::mat4(1), { roomSize, roomSize, 0 });
	wall1Model = glm::rotate(wall1Model, glm::radians(90.0f), { 0, -1, 0 });

	wall2Model = glm::translate(glm::mat4(1), { -roomSize, roomSize, 0 });
	wall2Model = glm::rotate(wall2Model, glm::radians(90.0f), { 0, 1, 0 });

	wall3Model = glm::translate(glm::mat4(1), { 0, roomSize, roomSize });
	wall3Model = glm::rotate(wall3Model, glm::radians(180.0f), { 0, 1, 0 });

	wall4Model = glm::translate(glm::mat4(1), { 0, roomSize, -roomSize });
	wall4Model = glm::rotate(wall4Model, glm::radians(90.0f), { 0, 0, 1 });
}

void Room::draw() {
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
}
