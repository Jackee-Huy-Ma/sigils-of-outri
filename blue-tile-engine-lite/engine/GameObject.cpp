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

void GameObject::update(float deltaTime) {
   updateTransformMatrix();
}

void GameObject::Draw(Shader& shader) {
    shader.use();
    shader.setMat4("transform",m_transformMatrix);
    m_mesh->draw();
}

void GameObject::updateTransformMatrix() {
    //Rotatation
    
    glm::quat rotationQuaternion = glm::quat(m_rotation);
    glm::mat4 rotationMatrix = glm::mat4(rotationQuaternion);

    //Translation
    //Testing
    m_transformMatrix = glm::mat4(1);
    //m_transformMatrix = glm::translate(m_transformMatrix, glm::vec3(400.0f, 300.0f, 0));

    m_transformMatrix = glm::translate(glm::mat4(1), m_position);
    //Scaling
    float imageWidth = m_mesh->getTexture()->getWidth();
    float imageHeight = m_mesh->getTexture()->getHeight();
    glm::vec3 imageDimensions = glm::vec3(imageWidth, imageHeight, 1);
    m_transformMatrix = glm::scale(m_transformMatrix, imageDimensions * m_scale);    

    //glm::mat4 myOrtho = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f);

    //m_transformMatrix = myOrtho * m_transformMatrix;

    //m_transformMatrix = glm::scale(translationMatrix);
}

void GameObject::setTransformMatrix(glm::mat4 transformationMatrix) {
    m_transformMatrix = transformationMatrix;
}

glm::mat4 GameObject::getTransformMatrix() {
    return m_transformMatrix;
}
