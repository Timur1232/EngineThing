#include "Window.h"
#include <iostream>
#include <GL\glew.h>
#include <GLFW\glfw3.h>


GLFWwindow* Window::sm_Window = nullptr;
int Window::sm_Width = 0;
int Window::sm_Height = 0;

int Window::initialize(int width, int height, const char* title)
{
	glewExperimental = GL_TRUE;

	if (!glfwInit()) {
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	sm_Window = glfwCreateWindow(width, height, title, nullptr, nullptr);
	if (!sm_Window) {
		std::cerr << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(sm_Window);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0, 0, width, height);
	sm_Width = width;
	sm_Height = height;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	return 0;
}

void Window::terminate()
{
	glfwTerminate();
}

bool Window::shouldClose()
{
	return glfwWindowShouldClose(sm_Window);
}

void Window::setShouldClose(bool flag)
{
	glfwSetWindowShouldClose(sm_Window, flag);
}

void Window::swapBuffers()
{
	glfwSwapBuffers(sm_Window);
}

int Window::getWidth()
{
	return sm_Width;
}

int Window::getHeight()
{
	return sm_Height;
}

void Window::clearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT);
}
