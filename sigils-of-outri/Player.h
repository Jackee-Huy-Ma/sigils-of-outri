#pragma once
#include <engine/GameObject.h>

class Player : public GameObject {
public:    
    Player(std::string name, glm::vec3 position,
            glm::vec3 rotation, glm::vec3 scale, const char * texturePath);
    
    ~Player();

    void update(float deltaTime);

    glm::vec3 m_velocity;

    float m_speed = 0.0f;
};