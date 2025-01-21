#include <iostream>
#include <exception>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "window/Window.h"
#include "graphics/shader/Shader.h"
#include "events/Events.h"

#include "objects2D/circle2D/Circle2D.h"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

int main()
{
	using namespace EngineThing;

	Window window;
	if (window.initialize(WIDTH, HEIGHT, "test"))
	{
		std::cerr << "Failed to initialize Gl\n";
		return -1;
	}
	Events events;
	if (events.bindWindow(window))
	{
		std::cerr << "Failed to bind window\n";
		return -1;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Circle2D circle1(glm::vec2((float)WIDTH / 2, (float)HEIGHT / 2), 0.2f),
			 circle2(glm::vec2((float)WIDTH / 2, (float)HEIGHT / 2), 0.1f);
	bool hold1 = false, hold2 = false;

	//circle1.color = glm::vec3(1.0f, 0.0f, 0.0f);
	//circle2.color = glm::vec3(0.0f, 1.0f, 0.0f);

	while (!window.shouldClose())
	{
		events.pollIvents();

		if (events.mouseScrollDelta() > 0)
		{
			circle1.radius = glm::clamp(circle1.radius + 0.1f, 0.1f, 1.1f);
			circle1.thickness = circle1.radius + 0.1f;
		}
		else if (events.mouseScrollDelta() < 0)
		{
			circle1.radius = glm::clamp(circle1.radius - 0.1f, 0.1f, 1.1f);
			circle1.thickness = circle1.radius + 0.1f;
		}

		if (circle2.onHover(events, window) && events.mouseJPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			circle2.color = glm::vec3(0.0f, 0.0f, 1.0f);
			hold2 = true;
		}
		else if (events.mouseReleased(GLFW_MOUSE_BUTTON_LEFT))
		{
			circle2.color = glm::vec3(1.0f, 1.0f, 1.0f);
			hold2 = false;
		}

		if (circle1.onHover(events, window) && events.mouseJPressed(GLFW_MOUSE_BUTTON_LEFT) && !hold2)
		{
			hold1 = true;
		}
		else if (events.mouseReleased(GLFW_MOUSE_BUTTON_LEFT) && hold1)
		{
			hold1 = false;
		}
		
		if (hold2)
		{
			circle2.position += events.mouseDeltaPos();
		}
		else if (hold1)
		{
			circle1.position += events.mouseDeltaPos();
		}

		circle1.draw(window);
		circle2.draw(window);

		window.swapBuffers();
		window.clearScreen();
	}
}