#include "GameObject.h"
#include "graphics/Quad.h"
#include "graphics/Shader.h"

int GameObject::idCounter = 0;

GameObject::GameObject(std::string name, glm::vec3 position,
            glm::vec3 rotation, glm::vec3 scale)
    : m_name(name)
    , m_position(position)
    , m_rotation(rotation)
    , m_scale(scale)
{
    m_Id = idCounter++;
    m_mesh = new Quad();
}

GameObject::~GameObject() {
    delete m_mesh;
}

void GameObject::Draw(Shader& shader) {
    shader.use();
    glBindVertexArray(m_mesh->m_VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
