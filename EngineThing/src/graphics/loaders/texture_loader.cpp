#pragma warning(disable : 4996)

#include "texture_loader.h"

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <png.h>

#include <types.h>


uint_32 png_load(const char* fileName, int* width, int* height)
{
    FILE* file;

    bool isPng;
    int bitDepth, colorType;
    size_t rowBytes;
    png_infop infoPtr, endInfo;
    png_uint_32 t_width, t_height;
    png_byte header[8], *imageData;
    png_bytepp rowPointers;
    png_structp pngPtr;
    int alpha;

    uint textureId;

    if (!(file = fopen(fileName, "rb")))
    {
        return 0;
    }

    fread(header, 1, 8, file);
    isPng = !png_sig_cmp(header, 0, 8);
    if (!isPng)
    {
        fclose(file);
        return 0;
    }

    pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
        NULL, NULL);
    if (!pngPtr)
    {
        fclose(file);
        return 0;
    }

    infoPtr = png_create_info_struct(pngPtr);
    if (!infoPtr)
    {
        png_destroy_read_struct(&pngPtr, (png_infopp)NULL,
            (png_infopp)NULL);
        fclose(file);
        return 0;
    }

    endInfo = png_create_info_struct(pngPtr);
    if (!endInfo)
    {
        png_destroy_read_struct(&pngPtr, (png_infopp)NULL,
            (png_infopp)NULL);
        fclose(file);
        return 0;
    }

    if (setjmp(png_jmpbuf(pngPtr)))
    {
        png_destroy_read_struct(&pngPtr, &infoPtr, &endInfo);
        fclose(file);
        return 0;
    }

    png_init_io(pngPtr, file);

    png_set_sig_bytes(pngPtr, 8);
    png_read_info(pngPtr, infoPtr);
    png_get_IHDR(pngPtr, infoPtr, &t_width, &t_height, &bitDepth,
        &colorType, NULL, NULL, NULL);

    *width = t_width;
    *height = t_height;

    png_read_update_info(pngPtr, infoPtr);
    rowBytes = png_get_rowbytes(pngPtr, infoPtr);
    imageData = (png_bytep)malloc(rowBytes * t_height * sizeof(png_byte));

    if (!imageData)
    {
        png_destroy_read_struct(&pngPtr, &infoPtr, &endInfo);
        fclose(file);
        return 0;
    }

    rowPointers = (png_bytepp)malloc(t_height * sizeof(png_bytep));
    if (!rowPointers)
    {
        png_destroy_read_struct(&pngPtr, &infoPtr, &endInfo);
        free(imageData);
        fclose(file);
        return 0;
    }

    for (unsigned int i = 0; i < t_height; ++i)
    {
        rowPointers[t_height - 1 - i] = imageData + i * rowBytes;
    }

    png_read_image(pngPtr, rowPointers);

    free(rowPointers);
    fclose(file);
    png_destroy_read_struct(&pngPtr, &infoPtr, &endInfo);

    switch (png_get_color_type(pngPtr, infoPtr))
    {
    case PNG_COLOR_TYPE_RGBA:
        alpha = GL_RGBA;
        break;
    case PNG_COLOR_TYPE_RGB:
        alpha = GL_RGB;
        break;
    default:
        printf("Color type %d not supported!\n",
            png_get_color_type(pngPtr, infoPtr));
        free(imageData);
        return 0;
    }

    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, t_width, t_height, 0,
        alpha, GL_UNSIGNED_BYTE, (GLvoid*)imageData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D, 0);

    free(imageData);

    return textureId;
}
