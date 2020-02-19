#pragma once

#include "VertexArray.h"
#include "Buffer.h"
#include "Shader.h"

class Quad {
public:
	Quad(const glm::vec3& pos, const glm::vec2& size);
	
	void draw();

	std::array<glm::vec3, 4> vertices;
	std::array<GLuint, 6> indices;
private:
	VertexArray VAO;
	Buffer VBO, EBO;

	glm::vec2 pos;
	glm::vec2 size;
};

