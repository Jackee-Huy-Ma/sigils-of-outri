#include "Enemy.h"
Enemy::Enemy(std::string name, glm::vec3 position,
            glm::vec3 rotation, glm::vec3 scale, const char * texturePath) : 
                Character{name, position, rotation, scale, texturePath} {

                    m_velocity = glm::vec3(0);
                    m_speed = 0;
}

Enemy::~Enemy() {

}
