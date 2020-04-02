#pragma once
#include "../GameObject.h"
#include "Stats.h"

class Character : public GameObject {
public:    
    Character(std::string name, glm::vec3 position,
            glm::vec3 rotation, glm::vec3 scale, const char * texturePath);
    
    ~Character();
    void update(float deltaTime);
    
    int m_health = 0;
    int m_mana= 0;

    Stats stats;
};
