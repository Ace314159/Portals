#pragma once

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

class Shader {
public:
	Shader(const std::string& name);
	~Shader();

	inline void use() const { glUseProgram(ID); };

	// Uniforms
	inline void setFloat(const char* name, float value) const {
		glUniform1f(glGetUniformLocation(ID, name), value);
	}
	inline void setInt(const char* name, int value) const {
		glUniform1i(glGetUniformLocation(ID, name), value);
	}
	inline void setMat4(const char* name, const glm::mat4& value) const {
		glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(value));
	}
	inline void setVec3(const char* name, const glm::vec3& value) const {
		glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value));
	}
	inline void setVec4(const char* name, const glm::vec4& value) const {
		glUniform4fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(value));
	}
private:
	GLuint ID;
};

