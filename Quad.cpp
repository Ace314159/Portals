#include "stdafx.h"

#include "Quad.h"

Quad::Quad(const glm::vec3& pos, const glm::vec2& size) : pos(pos), size(size) {
	vertices = {
		glm::vec3(pos.x         , pos.y         , pos.z),
		glm::vec3(pos.x + size.x, pos.y         , pos.z),
		glm::vec3(pos.x + size.x, pos.y + size.y, pos.z),
		glm::vec3(pos.x         , pos.y + size.y, pos.z),
	};

	indices = {
		0, 1, 2,
		0, 2, 3,
	};

	VAO.addAttribute(0, 3, GL_FLOAT, GL_FALSE, 0);
	VBO.bufferData(vertices.size() * sizeof(glm::vec3), vertices.data(), GL_STATIC_DRAW);
	EBO.bufferData(indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

void Quad::draw(const Shader& shader) {
	shader.use();
	VAO.bind(VBO, EBO, sizeof(glm::vec3));
	glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, 0);
}
