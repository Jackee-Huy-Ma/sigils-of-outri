#pragma once
#include <engine/rpg/Character.h>
#include <vector>

class Skill;
class Player : public Character {
public:    
    Player(std::string name, glm::vec3 position,
            glm::vec3 rotation, glm::vec3 scale, const char * texturePath);
    
    ~Player();
    void update(float deltaTime);
};