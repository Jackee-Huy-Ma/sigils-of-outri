#pragma once
#include <glad/glad.h>

class Texture {
public:
    //The default constructor of Texture
    Texture();

    //The deconstructor of Texture.
    ~Texture();

    void loadTexture();

private:
     //The id of the texture
    GLuint m_id;

    //The width of the texture.
    GLsizei m_width;

    //The height of the texture
    GLsizei m_height;
};