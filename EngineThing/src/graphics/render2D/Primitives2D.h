#pragma once

#include <glm/glm.hpp>
#include <types.h>
#include "../shader/Shader.h"

namespace Render2D
{

extern const float SCREEN_SPACE_QUAD[8];
extern const uint_32 SCREEN_SPACE_INDECIES[6];

int initialize();
	
void draw_circle(const glm::vec2& pos, float radius, float thickness, glm::vec3& color);
void draw_box(const glm::vec2& pos, float width, float height, float thickness, glm::vec3& color);

}