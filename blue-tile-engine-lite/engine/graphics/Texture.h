#pragma once
#include <glad/glad.h>
#include <iostream>

class Texture {
public:
    //The default constructor of Texture
    Texture(const char * imagePath);

    //The deconstructor of Texture.
    ~Texture();

    //Getters
    GLuint getTextureId();
    GLsizei getWidth();
    GLsizei getHeight();

private:
     //The id of the texture
    GLuint m_textureId;

    //The width of the texture.
    GLsizei m_width;

    //The height of the texture
    GLsizei m_height;

    // Number of channels
    // RGB = 3, RGBA = 4
    int m_numberOfChannels;
};