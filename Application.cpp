#include "stdafx.h"

#include "Camera.h"
#include "Window.h"
#include "Quad.h"

int main() {
	Window window;
	Shader quadShader("quad");
	Quad quad({ -0.5, -0.5, 0 }, { 1, 1 });
	Camera camera(window);

	while(window.isOpen()) {
		camera.update();

		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		quadShader.use();
		quadShader.setVec4("color", { 0.6, 0.5, 0, 1 });
		quad.draw();

		window.swapBuffers();
		glfwPollEvents();
	}
}