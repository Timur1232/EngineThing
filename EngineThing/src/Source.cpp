#include <iostream>
#include <exception>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "window/Window.h"
#include "graphics/shader/Shader.h"
#include "events/Events.h"

//#include "graphics/render2D/Render2D.h"
#include "objects2D/box2D/Box2D.h"

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

	Box2D box(glm::vec2((float)WIDTH / 2, (float)HEIGHT / 2), 0.5f, 0.4f);

	while (!window.shouldClose())
	{
		events.pollIvents();

		if (box.onHover(events, window))
		{
			box.color = glm::vec3(1, 0, 0);
		}
		else
		{
			box.color = glm::vec3(1, 1, 1);
		}

		box.draw(window);

		window.swapBuffers();
		window.clearScreen();
	}
}