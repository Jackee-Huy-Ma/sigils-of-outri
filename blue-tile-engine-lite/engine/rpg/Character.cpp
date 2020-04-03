#include "Character.h"

Character::Character(std::string name, glm::vec3 position,
            glm::vec3 rotation, glm::vec3 scale, const char * texturePath) : 
                GameObject{name, position, rotation, scale, texturePath} {

                    m_velocity = glm::vec3(0);
                    m_speed = 0.0f;
                    m_health = 0;
                    m_mana = 0;
                    m_currentHealth = 0;
                    m_currentMana = 0;
}

Character::~Character() {

}

void Character::update(float deltaTime) {

}

void Character::setLevel(int level) {
    std::cout << "Character setLevel called" << std::endl;
}