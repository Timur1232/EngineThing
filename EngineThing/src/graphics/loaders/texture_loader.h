#pragma once

#include <string>
#include <types.h>

[[nodiscard]]
uint_32 png_load(const char* fileName, int* width, int* height);