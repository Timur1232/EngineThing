#pragma once

#include "glm/glm.hpp"

#include "../Object2DBase.h"
#include "../../graphics/shader/Shader.h"


namespace EngineThing
{

	class Events;
	class Window;

	class Box2D : public Object2DBase
	{
	public:
		Box2D() = default;
		Box2D(const glm::vec2& pos, float width = 0.5f, float height = 0.5f, float thickness = 1.0f, const glm::vec3& color = glm::vec3(1.0f));

		void draw(const Window& window) override;
		bool onHover(const Events& events, const Window& window) override;

	public:
		float width = 0.5f;
		float height = 0.5f;
		float thickness = 1.0f;
		glm::vec3 color = glm::vec3(1.0f);
	};

} // EngineThing