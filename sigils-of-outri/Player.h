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

    //TO-DO boolean parameter if item is equiped.
    void printMap();

    void setLevel(int level);

    //TO-DO
    //Goal is to calculate a type float called fitness value.
    // Fitness value = total damage dealt / total damage mitagated.
    // I need a boss.
    // Character & target.
    // go inside my map. inside for loop of it->second (while character hp not dead... simulate).
    // once i'm done that for loop, every equipment should have a new float value called fitness.
    // Break out manually.
    void simulate(Player & player, Enemy & target);

};