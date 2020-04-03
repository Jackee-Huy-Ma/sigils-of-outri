#include "Player.h"
#include "engine/rpg/Equipment.h"
#include "engine/rpg/Skill.h"
#include "Enemy.h"
#include "Fireball.h"
#include "Cyclone.h"
#include "Zombie.h"
#include <algorithm>
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
                    m_health = 1;
                    m_mana = 1;
                    generate(inventory);
                    m_skill.push_back(new Fireball("Fireball"));
                    m_skill.push_back(new Cyclone("Cyclone"));
                    m_skill.push_back(new Zombie("Zombie"));
                    //printMap();
}

Player::~Player() {
    for(auto it = inventory.begin(); it!= inventory.end(); it++) {
        for(int j = 0; j < it->second.size(); j++) {
            delete it->second[j];
        }
    }
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
            std::sort(it->second.begin(), it->second.end(), [](Equipment * a, Equipment * b) { return a->fitness > b->fitness;});
            std::cout << "ID:" << it->second[j]->m_id
                      << " Attack:" << it->second[j]->m_stats.attack
                      << " Defense:" << it->second[j]->m_stats.defense
                      << " MagicAttack:" << it->second[j]->m_stats.magicAttack
                      << " MagicDefense:" << it->second[j]->m_stats.magicDefense
                      << " Fitness:" << it->second[j]->fitness
                      << std::endl;
        }
        std::cout << std::endl;
    }
}

//Simple Level system.
//Can be changed later.
void Player::setLevel(int level) {
    stats.attack = level * stats.attack;
    stats.defense = level * stats.defense;
    stats.magicAttack = level * stats.magicAttack;
    stats.magicDefense = level * stats.magicDefense;

    m_health = m_health * 10 * level;
    m_mana = m_mana * 10 * level;
    m_currentHealth = m_health;
    m_currentMana = m_mana;
    
}

void Player::simulate(Player & player,Enemy & target) {
    //Setting the player and target to be the same level
    
    player.setLevel(50);
    target.setLevel(50);
    
    std::string playerSkillName;
    std::string enemySkillName;

    int playerDamage = 0;
    int enemyDamage = 0;

    float totalDamageReceived = 0;
    float totalDamage = 0;

    int turns = 0;
    //std::cout << "Enemy Stats:" << target.stats.attack << std::endl;
    for(auto it = player.inventory.begin(); it!=player.inventory.end(); ++it) {
        for(int j = 0; j < it->second.size(); j++) {
            while(player.m_currentHealth >= 0 || target.m_currentHealth >= 0) {
                if(playerDamage == 0) {
                    //Setup the way to figure out what skill does the most damage.
                    //Execute only once per Equipment Gear being simulated.

                    Stats playerTempStats;
                    
                    playerTempStats.attack = player.stats.attack + it->second[j]->m_stats.attack;
                    playerTempStats.defense = player.stats.defense + it->second[j]->m_stats.defense;
                    playerTempStats.magicAttack = player.stats.magicAttack + it->second[j]->m_stats.magicAttack;
                    playerTempStats.magicDefense = player.stats.magicDefense + it->second[j]->m_stats.magicDefense;    
                    
                    for(int k = 0; k < player.m_skill.size(); k++) {
                        //std::cout << "Player casting:" << player.m_skill[k]->m_name << std::endl;
                        int playerSkillDamage = player.m_skill[k]->activate(playerTempStats,target);
                        if(playerDamage <= playerSkillDamage) {
                            playerDamage = playerSkillDamage;
                        }  
                    }

                    for(int l = 0; l < target.m_skill.size(); l++) {
                        //std::cout << "Enemy casting:" << target.m_skill[l]->m_name << std::endl;
                        int enemySkillDamage = target.m_skill[l]->activate(target.stats, player);
                        if(enemyDamage <= enemySkillDamage) {
                            enemySkillName = target.m_skill[l] ->m_name;
                            enemyDamage = enemySkillDamage;
                        }
                    }
                }
               
                player.m_currentHealth = player.m_currentHealth - enemyDamage;
                target.m_currentHealth = target.m_currentHealth - playerDamage;

                totalDamage += playerDamage;
                totalDamageReceived += enemyDamage;
                turns++;
                
                if(!(player.m_currentHealth >= 0 || target.m_currentHealth >= 0)) {
                    enemySkillName.clear();
                }
            }
            it->second[j]->fitness =  totalDamage / totalDamageReceived;
            player.setLevel(50);
            target.setLevel(50);
            playerDamage = 0;
            enemyDamage = 0;
            turns = 0;

        }

    }
    
}
