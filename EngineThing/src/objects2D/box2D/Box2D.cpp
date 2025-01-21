#include "Box2D.h"

#include "../../graphics/render2D/Render2D.h"

#include "../../events/Events.h"
#include "../../window/Window.h"

namespace EngineThing
{

Box2D::Box2D(const glm::vec2& pos, float width, float height, float thickness, const glm::vec3& color)
    : Object2DBase(pos), width(width), height(height), thickness(thickness), color(color)
{
}

void Box2D::draw(const Window& window)
{
    sm_Renderer2D.drawBox(position, width, height, thickness, color, window);
}

bool Box2D::onHover(const Events& events, const Window& window)
{
    return events.mousePos().x >= (position.x - (width / 4 * window.getHeight())) &&
        events.mousePos().x <= (position.x + (width / 4 * window.getHeight())) &&
        events.mousePos().y >= (position.y - (height / 4 * window.getHeight())) &&
        events.mousePos().y <= (position.y + (height / 4 * window.getHeight()));
}

} // EngineThing