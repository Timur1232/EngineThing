#pragma once

#include "../Object2DBase.h"
#include "../../graphics/shader/Shader.h"
#include "glm/glm.hpp"

class Circle2D : public Object2DBase
{
public:

	Circle2D() = default;
	Circle2D(const glm::ivec2& pos);
	Circle2D(const glm::ivec2& pos, float radius);
	Circle2D(const glm::ivec2& pos, float radius, float thickness);

	void draw() override;
	bool onHover() override;

	float radius = 1.0f;
	float thickness = 1.0f;
	glm::vec3 color = glm::vec3(1.0f);

};