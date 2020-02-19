#include "stdafx.h"

#include "Window.h"

Window::Window() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
	if(window == nullptr) spdlog::error("Failed to create GLFW window!");
	glfwMakeContextCurrent(window);

	if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		SPDLOG_CRITICAL("Failed to initialize GLAD");
	}

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	glDebugMessageCallback(glDebugCallback, nullptr);
	GLuint ignoredIDs[] = { 0x20071 };
	glDebugMessageControl(GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_OTHER, GL_DONT_CARE, 1, ignoredIDs, GL_FALSE);
	glfwSetErrorCallback([](int errorCode, const char* desc) {
		SPDLOG_CRITICAL("GLFW Error {}: {}", errorCode, desc);
	});
#endif

	glEnable(GL_DEPTH_TEST);

	glViewport(0, 0, width, height);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		width = width;
		height = height;
		glViewport(0, 0, width, height);
	});
}

void Window::swapBuffers() {
	glfwSwapBuffers(window);
	
	double curTime = glfwGetTime();
	double dTime = curTime - prevTime;
	if(dTime > 1) {
		glfwSetWindowTitle(window, (title + " - " + std::to_string(framesPassed / dTime) + " FPS").c_str());
		prevTime = curTime;
		framesPassed = 0;
	} else framesPassed++;
}

Window::~Window() {
	glfwTerminate();
}
