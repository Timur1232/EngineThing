#include "Object2DBase.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

Object2DBase::Object2DBase(const glm::ivec2& pos)
	: position(pos)
{
}
