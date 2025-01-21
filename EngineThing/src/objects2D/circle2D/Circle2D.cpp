#include "Circle2D.h"

#include "../../graphics/render2D/Render2D.h"

#include "../../events/Events.h"
#include "../../window/Window.h"

namespace EngineThing
{

Circle2D::Circle2D(const glm::vec2& pos, float radius, float thickness, const glm::vec3& color)
	: Object2DBase(pos), radius(radius), thickness(thickness), color(color)
{
}

void Circle2D::draw(const Window& window)
{
	sm_Renderer2D.drawCircle(position, radius, thickness, color, window);
}

bool Circle2D::onHover(const Events& events, const Window& window)
{
	float length = glm::length(events.mousePos() - position) / window.getHeight() * 2;
	if (length <= radius)
		return true;
	return false;
}

} // EngineThing