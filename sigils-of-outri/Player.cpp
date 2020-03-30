#include "Player.h"

Player::Player(std::string name, glm::vec3 position,
            glm::vec3 rotation, glm::vec3 scale, const char * texturePath) : 
                GameObject{name, position, rotation, scale, texturePath} {

                    m_velocity = glm::vec3(0);
                    m_speed = 10.0f;
}

Player::~Player() {

}

void Player::update(float deltaTime) {
    m_position += glm::vec3(m_velocity.x * deltaTime, m_velocity.y * deltaTime, m_velocity.z * deltaTime);
    updateTransformMatrix();
}
