#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
public:
	Window();
	~Window();

	int getWidth() const { return width; };
	int getHeight() const { return height; };

	inline bool isOpen() { return !glfwWindowShouldClose(window); };
	void swapBuffers();
	GLFWwindow* window;
private:
	int width = 800, height = 600;

	const std::string& title = "Portals";
	double prevTime = glfwGetTime();
	unsigned int framesPassed = 0;
};

inline void APIENTRY glDebugCallback(GLenum source, GLenum mType, GLuint id, GLenum severity, GLsizei length,
	const GLchar* message, const void* userParam) {
	std::string src;
	switch(source) {
	case GL_DEBUG_SOURCE_API:
		src = "Windows";
		break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER:
		src = "Shader Compiler";
		break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:
		src = "Third Party";
		break;
	case GL_DEBUG_SOURCE_APPLICATION:
		src = "Application";
		break;
	case GL_DEBUG_SOURCE_OTHER:
		src = "Other";
		break;
	}

	std::string type;
	switch(mType) {
	case GL_DEBUG_TYPE_ERROR:
		type = "Error";
		break;
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
		type = "Deprecated Behavior";
		break;
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		type = "Undefined Behavior";
		break;
	case GL_DEBUG_TYPE_PORTABILITY:
		type = "Portability Error";
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		type = "Performance Error";
		break;
	case GL_DEBUG_TYPE_OTHER:
		type = "Other Message";
		break;
	}

	switch(severity) {
	case GL_DEBUG_SEVERITY_NOTIFICATION:
		SPDLOG_INFO("GL NOTIFICATION - {} {}: {}", src, type, message);
		break;
	case GL_DEBUG_SEVERITY_LOW:
		SPDLOG_WARN("GL LOW - {} {}: {}", src, type, message);
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		SPDLOG_ERROR("GL MEDIUM - {} {}: {}", src, type, message);
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		SPDLOG_CRITICAL("GL HIGH - {} {}: {}", src, type, message);
		break;
	}
}
