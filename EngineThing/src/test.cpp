#include <iostream>
#include <exception>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include "window/Window.h"
#include "graphics/shader/Shader.h"
#include "events/Events.h"
#include "graphics/render2D/Primitives2D.h"

#include "objects2D/circle2D/Circle2D.h"

constexpr int WIDTH = 800;
constexpr int HEIGHT = 600;

int main()
{
	if (Window::initialize(WIDTH, HEIGHT, "test"))
	{
		std::cerr << "Failed to initialize Gl\n";
		return -1;
	}
	Events::initialize();

	Render2D::initialize();

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	Circle2D circle1(glm::vec2((float)WIDTH / 2, (float)HEIGHT / 2), 0.2f),
			 circle2(glm::vec2((float)WIDTH / 2, (float)HEIGHT / 2), 0.1f);
	bool hold1 = false, hold2 = false;

	//circle1.color = glm::vec3(1.0f, 0.0f, 0.0f);
	//circle2.color = glm::vec3(0.0f, 1.0f, 0.0f);

	while (!Window::shouldClose())
	{
		Events::pollIvents();

		if (Events::mouseScrollDelta() > 0)
		{
			circle1.radius = glm::clamp(circle1.radius + 0.1f, 0.1f, 1.0f);
		}
		else if (Events::mouseScrollDelta() < 0)
		{
			circle1.radius = glm::clamp(circle1.radius - 0.1f, 0.2f, 1.0f);
		}

		if (circle2.onHover() && Events::mouseJPressed(GLFW_MOUSE_BUTTON_LEFT))
		{
			circle2.color = glm::vec3(0.0f, 0.0f, 1.0f);
			hold2 = true;
		}
		else if (Events::mouseReleased(GLFW_MOUSE_BUTTON_LEFT))
		{
			circle2.color = glm::vec3(1.0f, 1.0f, 1.0f);
			hold2 = false;
		}
		if (circle1.onHover() && Events::mouseJPressed(GLFW_MOUSE_BUTTON_LEFT) && !hold2)
		{
			hold1 = true;
		}
		else if (Events::mouseReleased(GLFW_MOUSE_BUTTON_LEFT) && hold1)
		{
			hold1 = false;
		}
		
		if (hold2)
		{
			circle2.position += Events::mouseDeltaPos();
		}
		else if (hold1)
		{
			circle1.position += Events::mouseDeltaPos();
		}

		circle1.draw();
		circle2.draw();

		Window::swapBuffers();
		Window::clearScreen();
	}
}