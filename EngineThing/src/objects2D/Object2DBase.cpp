#include "Object2DBase.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "../graphics/render2D/Render2D.h"

namespace EngineThing
{

Render2D Object2DBase::sm_Renderer2D;

Object2DBase::Object2DBase(const glm::vec2& pos)
	: position(pos)
{
	sm_Renderer2D.initialize();
}

} // EngineThing