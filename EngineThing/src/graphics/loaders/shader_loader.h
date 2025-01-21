#pragma once

#include <string>
#include <types.h>

namespace EngineThing
{

[[nodiscard]]
uint_32 load_shader(const char* vertexShader, const char* fragmentShader);

} // EngineThing