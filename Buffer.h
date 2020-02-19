#pragma once

#include <glad/glad.h>

class Buffer {
public:
	inline Buffer() {
		glCreateBuffers(1, &ID);
	}
	inline ~Buffer() {
		glDeleteBuffers(1, &ID);
	}

	inline void bufferData(GLsizeiptr size, const void* data, GLenum usage) {
		glNamedBufferData(ID, size, data, usage);
	}
	
	friend class VertexArray;
private:
	GLuint ID;
};

