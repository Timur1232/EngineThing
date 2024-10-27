#include "Circle2D.h"

#include "../../graphics/render2D/Primitives2D.h"

#include "../../events/Events.h"
#include "../../window/Window.h"

Circle2D::Circle2D(const glm::ivec2& pos)
	: Object2DBase(pos)
{
}

Circle2D::Circle2D(const glm::ivec2& pos, float radius)
	: Object2DBase(pos), radius(radius)
{
}

Circle2D::Circle2D(const glm::ivec2& pos, float radius, float thickness)
	: Circle2D(pos, radius)
{
	this->thickness = thickness;
}

void Circle2D::draw()
{
	Render2D::draw_circle(position, radius, thickness, color);
}

bool Circle2D::onHover()
{
	float length = glm::length(Events::mousePos() - position) / Window::getHeight() * 2;
	if (length <= radius)
		return true;
	return false;
}
