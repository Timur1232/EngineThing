#include "Events.h"

#include "../window/Window.h"
#include <GLFW\glfw3.h>
#include <string.h>

#include <types.h>
#include <iostream>

bool Events::s_Keys[KEYS_SIZE] = { 0 };
uint_32 Events::s_Frames[KEYS_SIZE] = { 0 };
uint_32 Events::s_CurrentFrame = 0;
glm::vec2 Events::s_MousePos = glm::vec2(0.0);
glm::vec2 Events::s_MouseDeltaPos = glm::vec2(0.0);
bool Events::s_CursorLoked = false;
bool Events::s_CursorStarted = false;
float Events::s_MouseScrollDelta = 0.0;
bool Events::s_MouseRelease = false;

int Events::initialize()
{
	GLFWwindow* window = Window::sm_Window;

	glfwSetKeyCallback(window, keyCallback);
	glfwSetMouseButtonCallback(window, mouseButtonCallback);
	glfwSetCursorPosCallback(window, cursorPositionCallback);
	glfwSetScrollCallback(window, scrollCallback);

	return 0;
}

void Events::pollIvents()
{
	s_CurrentFrame++;
	s_MouseDeltaPos = glm::dvec2(0.0);
	s_MouseScrollDelta = 0.0;
	glfwPollEvents();
}

bool Events::keyPressed(int keycode)
{
	if (keycode < 0 || keycode >= MOUSE_BUTTONS)
		return false;
	return s_Keys[keycode];
}

bool Events::keyJPressed(int keycode)
{
	if (keycode < 0 || keycode >= MOUSE_BUTTONS)
		return false;
	return s_Keys[keycode] && s_Frames[keycode] == s_CurrentFrame;
}

bool Events::mousePressed(int button)
{
	int index = MOUSE_BUTTONS + button;
	return s_Keys[index];
}

bool Events::mouseReleased(int button)
{
	int index = MOUSE_BUTTONS + button;
	return !s_Keys[index] && (s_Frames[index] == s_CurrentFrame);
}

bool Events::mouseJPressed(int button)
{
	int index = MOUSE_BUTTONS + button;
	return s_Keys[index] && (s_Frames[index] == s_CurrentFrame);
}

const glm::vec2& Events::mousePos()
{
	return s_MousePos;
}

const glm::vec2& Events::mouseDeltaPos()
{
	return s_MouseDeltaPos;
}

float Events::mouseScrollDelta()
{
	return s_MouseScrollDelta;
}

void Events::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (action == GLFW_PRESS) {
		s_Keys[key] = true;
		s_Frames[key] = s_CurrentFrame;
	}
	else if (action == GLFW_RELEASE) {
		s_Keys[key] = false;
		s_Frames[key] = s_CurrentFrame;
	}
}

void Events::mouseButtonCallback(GLFWwindow* window, int button, int action, int mode)
{
	int index = MOUSE_BUTTONS + button;

	if (action == GLFW_PRESS) {
		s_Keys[index] = true;
		s_Frames[index] = s_CurrentFrame;
	}
	else if (action == GLFW_RELEASE) {
		s_Keys[index] = false;
		s_Frames[index] = s_CurrentFrame;
	}
}

void Events::cursorPositionCallback(GLFWwindow* window, double x_pos, double y_pos)
{
	if (s_CursorStarted) {
		s_MouseDeltaPos.x += x_pos - s_MousePos.x;
		s_MouseDeltaPos.y += y_pos - s_MousePos.y;
	}
	else {
		s_CursorStarted = true;
	}
	s_MousePos.x = x_pos;
	s_MousePos.y = y_pos;
}

void Events::scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	s_MouseScrollDelta = yoffset;
}
