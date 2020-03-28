#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>
#include "Texture.h"

Texture::Texture(const char * imagePath) {

    //Generates the texture
    glGenTextures(1, & m_textureId);
    glBindTexture(GL_TEXTURE_2D, m_textureId);

    //set texture wrapping/filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    //load texture
    //fixes inverted picture.
    stbi_set_flip_vertically_on_load(true);
    unsigned char * data = stbi_load(imagePath, &m_width, &m_height, &m_numberOfChannels, 0);
    
    if(data) {
        auto format = m_numberOfChannels == 3 ? GL_RGB : GL_RGBA;
        glTexImage2D(GL_TEXTURE_2D, 0, format, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);    
    
    }else {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
}

Texture::~Texture() {

}

GLuint::Texture::getTextureId() {
     return m_textureId;
}

GLsizei::Texture::getWidth() {
    return m_width;
}

GLsizei::Texture::getHeight() {
    return m_height;
}
