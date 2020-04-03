#pragma once
#include <engine/rpg/Character.h>
#include <vector>
#include "CorpseExplosion.h"
#include "MagicFrame.h"
#include "Slam.h"

class Skill;
class Enemy : public Character {
public:    
    Enemy(std::string name, glm::vec3 position,
            glm::vec3 rotation, glm::vec3 scale, const char * texturePath);
    
    ~Enemy();

    std::vector<Skill *> m_skill;
    void setLevel(int level);
};