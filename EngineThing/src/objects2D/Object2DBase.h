#pragma once

#include <glm/glm.hpp>
#include <types.h>

#include "../graphics/render2D/Render2D.h"

namespace EngineThing
{

class Events;
class Window;

class Object2DBase
{
public:
	Object2DBase() = default;
	Object2DBase(const glm::vec2& pos);

	virtual void draw(const Window& window) = 0;
	virtual bool onHover(const Events& events, const Window& window) = 0;

public:
	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 scale = glm::vec2(1.0f);
	float angleRad = 0.0f;

protected:
	static Render2D sm_Renderer2D;
};

} // EngineThing