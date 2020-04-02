#include "Player.h"
#include "engine/rpg/Equipment.h"
#include "engine/rpg/Skill.h"

//Used to test / play around with inventory sizes.
constexpr int INVENTORYSIZE = 30;

//Used to determine amount of maxumum gear player can equip.
//Also used to determine what type an equipment is.
//E.g equipmentID % MAXEQUIP = 0 to MAXEQUIP - 1. 
//0:helmet, 1 = body, 2 = lower body, 3 = boots, 4 = weapon.
constexpr int MAXEQUIP = 5;

Player::Player(std::string name, glm::vec3 position,
            glm::vec3 rotation, glm::vec3 scale, const char * texturePath) : 
                Character{name, position, rotation, scale, texturePath} {

                    m_velocity = glm::vec3(0);
                    m_speed = 10.0f;
                    generate(inventory);
                    printMap();
}

Player::~Player() {

}

void Player::update(float deltaTime) {
    m_position += glm::vec3(m_velocity.x * deltaTime, m_velocity.y * deltaTime, m_velocity.z * deltaTime); 
}

void Player::generate(std::map<int, std::vector<Equipment *>> & inventory) {
    std::default_random_engine e;
    std::uniform_int_distribution<int> u(-2, 10);

    //Setup initial contents of the map.

    for(int i = 0; i < MAXEQUIP; i++) {
        std::vector<Equipment *> temp;
        inventory.insert(std::pair<int, std::vector<Equipment *>>(i, temp));
    }
    
    int i = 0;
    while(i != INVENTORYSIZE) {
        Stats stats = {u(e), u(e), u(e), u(e)};
        Equipment * item = new Equipment(i, stats);
        inventory.at(i % MAXEQUIP).push_back(item);
        i++;
    }
}

void Player::printMap() {
       for(auto it = inventory.begin(); it!= inventory.end(); ++it) {
        std::cout << "{Slot:" << it->first << "}" << std::endl
            << "Items:" << std::endl;

        for(int j = 0; j < it->second.size(); j++) {
            std::cout << "ID:" << it->second[j]->m_id
                      << " Attack:" << it->second[j]->m_stats.attack
                      << " Defense:" << it->second[j]->m_stats.defense
                      << " MagicAttack:" << it->second[j]->m_stats.magicAttack
                      << " MagicDefense:" << it->second[j]->m_stats.magicDefense
                      << std::endl;
        }
        std::cout << std::endl;
    }
}