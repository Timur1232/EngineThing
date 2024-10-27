#include "Texture.h"

#include <GL/glew.h>
#include <iostream>
#include <exception>
#include <string>

#include <types.h>

#include "../loaders/texture_loader.h"

Texture::~Texture()
{
    deleteTexture();
}

void Texture::loadTexture(const char* fileName)
{
    deleteTexture();
    m_Id = png_load(fileName, &m_Width, &m_Height);

    if (!m_Id)
    {
        std::string err("TEXTURE::LOAD: Failed to load texture\n");
        err += fileName;
        std::cerr << err << std::endl;
        m_Width = 0;
        m_Height = 0;
        throw std::runtime_error(err);
    }
}

void Texture::deleteTexture()
{
    if (m_Id)
    {
        glDeleteTextures(1, &m_Id);
        m_Id = 0;
    }
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_Id);
}