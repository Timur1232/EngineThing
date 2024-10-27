#pragma once

struct GLFWwindow;
class Events;

class Window
{
public:

	friend Events;

	static int initialize(int width, int height, const char* title);
	static void terminate();

	static bool shouldClose();
	static void setShouldClose(bool flag);
	static void swapBuffers();
	static int getWidth();
	static int getHeight();
	static void clearScreen();

private:

	static GLFWwindow* sm_Window;
	static int sm_Width;
	static int sm_Height;

};

