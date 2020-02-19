#include "stdafx.h"

#include "Window.h"
#include "Quad.h"

int main() {
	Window window;
	Shader quadShader("quad");
	Quad quad({ -0.5, -0.5, 0 }, { 1, 1 });

	while(window.isOpen()) {
		glClearColor(0, 0, 0, 1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		quad.draw(quadShader);

		window.swapBuffers();
		glfwPollEvents();
	}
}