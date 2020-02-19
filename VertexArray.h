#pragma once

#include <glad/glad.h>

#include "Buffer.h"

class VertexArray {
public:
	inline VertexArray() {
		glCreateVertexArrays(1, &ID);
	}
	inline ~VertexArray() {
		glDeleteVertexArrays(1, &ID);
	}

	inline void addAttribute(GLuint index, GLint size, GLenum type, GLboolean normalized, GLuint offset) {
		glEnableVertexArrayAttrib(ID, index);
		glVertexArrayAttribFormat(ID, index, size, type, normalized, offset);
		glVertexArrayAttribBinding(ID, index, 0);
	}
	
	inline void bind(const Buffer& VBO, const Buffer& EBO, GLsizei vertexSize) {
		glBindVertexArray(ID);
		glVertexArrayVertexBuffer(ID, 0, VBO.ID, 0, vertexSize);
		glVertexArrayElementBuffer(ID, EBO.ID);
	}
private:
	GLuint ID;
};

