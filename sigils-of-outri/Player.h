#pragma once
#include <engine/rpg/Character.h>
#include <vector>
#include <random>
#include <map>

class Skill;
class Equipment;
class Enemy;
class Player : public Character {
public:    
    Player(std::string name, glm::vec3 position,
            glm::vec3 rotation, glm::vec3 scale, const char * texturePath);
    
    ~Player();

    //Player's skill list
    std::vector<Skill *> m_skill;

    //Inventory
    std::map<int, std::vector<Equipment *>> inventory;

    void update(float deltaTime);

    void generate(std::map<int, std::vector<Equipment *>> & inventory);

    void printMap();

    void setLevel(int level);

    void simulate(Player & player, Enemy & target);

    void autoEquip();
};