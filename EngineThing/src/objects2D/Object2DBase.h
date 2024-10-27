#pragma once

#include <glm/glm.hpp>
#include <types.h>

class Object2DBase
{
public:

	Object2DBase() = default;
	Object2DBase(const glm::ivec2& pos);

	virtual void draw() = 0;
	virtual bool onHover() = 0;

	glm::vec2 position = glm::vec2(0.0f);
	glm::vec2 scale = glm::vec2(1.0f);
	float angleRad = 0.0f;

};