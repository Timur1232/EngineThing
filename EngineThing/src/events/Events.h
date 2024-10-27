#pragma once

#include <types.h>

#include <glm/glm.hpp>

struct GLFWwindow;

#define KEYS_SIZE 1032
#define MOUSE_BUTTONS 1024

class Events
{
public:

	static int initialize();
	static void pollIvents();

	static bool keyPressed(int keycode);
	static bool keyJPressed(int keycode);

	static bool mousePressed(int button);
	static bool mouseJPressed(int button);
	static bool mouseReleased(int button);

	static const glm::vec2& mousePos();
	static const glm::vec2& mouseDeltaPos();
	static float mouseScrollDelta();

private:

	static bool s_Keys[KEYS_SIZE];
	static uint_32 s_Frames[KEYS_SIZE];
	static uint_32 s_CurrentFrame;
	static glm::vec2 s_MousePos;
	static glm::vec2 s_MouseDeltaPos;
	static bool s_CursorLoked;
	static bool s_CursorStarted;
	static float s_MouseScrollDelta;
	static bool s_MouseRelease;

	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
	static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mode);
	static void cursorPositionCallback(GLFWwindow* window, double x_pos, double y_pos);
	static void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);

};

