#pragma once

#include <string>
#include <types.h>

class Texture
{
private:

	uint m_Id = 0;
	int m_Width = 0;
	int m_Height = 0;

public:

	Texture() = default;
	~Texture();

	void loadTexture(const char* fileName);
	void deleteTexture();
	void bind() const;

};

