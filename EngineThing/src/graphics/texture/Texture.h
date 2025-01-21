#pragma once

#include <string>
#include <types.h>

namespace EngineThing
{

class Texture
{
public:
	Texture() = default;
	~Texture();

	void loadTexture(const char* fileName);
	void deleteTexture();
	void bind() const;

private:
	uint m_Id = 0;
	int m_Width = 0;
	int m_Height = 0;
};

} // EngineThing