#pragma once

#include "Shader.h"
#include "Quad.h"

class Room {
public:
	Room(const Shader& quadShader);
	void draw();
	int getRoomSize() { return roomSize; };
private:
	Shader quadShader;
	const int roomSize = 10;
	Quad wall{ { -roomSize, -roomSize, 0 }, { 2 * roomSize, 2 * roomSize } };

	// Model Matrices
	glm::mat4 floorModel;
	glm::mat4 wall1Model;
	glm::mat4 wall2Model;
	glm::mat4 wall3Model;
	glm::mat4 wall4Model;
};

