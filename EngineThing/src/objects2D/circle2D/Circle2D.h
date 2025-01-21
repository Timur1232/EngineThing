#pragma once

#include "glm/glm.hpp"

#include "../Object2DBase.h"
#include "../../graphics/shader/Shader.h"


namespace EngineThing
{

class Events;
class Window;

class Circle2D : public Object2DBase
{
public:
	Circle2D() = default;
	Circle2D(const glm::vec2& pos, float radius = 1.0f, float thickness = 1.0f, const glm::vec3& color = glm::vec3(1.0f));

	void draw(const Window& window) override;
	bool onHover(const Events& events, const Window& window) override;

public:
	float radius = 1.0f;
	float thickness = 1.0f;
	glm::vec3 color = glm::vec3(1.0f);
};

} // EngineThing