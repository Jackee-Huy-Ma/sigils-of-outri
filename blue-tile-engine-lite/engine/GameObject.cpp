#include "GameObject.h"
#include "graphics/Quad.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include <glm/gtc/matrix_transform.hpp>
int GameObject::idCounter = 0;

GameObject::GameObject(std::string name, glm::vec3 position,
            glm::vec3 rotation, glm::vec3 scale, const char * texturePath)
    : m_name(name)
    , m_position(position)
    , m_rotation(rotation)
    , m_scale(scale)
{
    m_Id = idCounter++;
    m_mesh = new Quad(texturePath);
}

GameObject::~GameObject() {
    delete m_mesh;
}

void GameObject::update(glm::vec2 windowSize) {
    m_transformMatrix = glm::mat4(1);
    float imageWidth = m_mesh->getTexture()->getWidth();
    float imageHeight = m_mesh->getTexture()->getHeight();
    
    glm::mat4 myOrtho = glm::ortho(0.0f, windowSize.x, 0.0f, windowSize.y);
    glm::vec3 imageDimensions = glm::vec3(imageWidth, imageHeight, 1);

    m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(windowSize.x / 2, windowSize.y / 2, 0));
    m_transformMatrix = glm::scale(m_transformMatrix, imageDimensions);    
    
    //TO-DO MAKE MVP VARIABLE.
    m_transformMatrix = myOrtho * m_transformMatrix;
    

}

void GameObject::Draw(Shader& shader) {
    shader.use();
    shader.setMat4("transform",m_transformMatrix);
    m_mesh->draw();
}
