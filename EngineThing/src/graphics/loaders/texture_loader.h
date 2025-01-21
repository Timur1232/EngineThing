#pragma once

#include <types.h>

namespace EngineThing
{

[[nodiscard]]
uint_32 png_load(const char* fileName, int* width, int* height);

} // EngineThing