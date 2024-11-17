#pragma once

#include "glm/glm.hpp"

#include "../Object2DBase.h"
#include "../../graphics/shader/Shader.h"

class Events;
class Window;

class Circle2D : public Object2DBase
{
public:

	Circle2D() = default;
	Circle2D(const glm::ivec2& pos);
	Circle2D(const glm::ivec2& pos, float radius);
	Circle2D(const glm::ivec2& pos, float radius, float thickness);

	void draw(const Window& window) override;
	// TODO: Переделать метод
	bool onHover(const Events& events, const Window& window) override;

	float radius = 1.0f;
	float thickness = 1.0f;
	glm::vec3 color = glm::vec3(1.0f);

};