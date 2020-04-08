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

constexpr int MINSTATS = -2;
constexpr int MAXSTATS = 10;
Player::Player(std::string name, glm::vec3 position,
            glm::vec3 rotation, glm::vec3 scale, const char * texturePath) : 
                Character{name, position, rotation, scale, texturePath} {

                    m_velocity = glm::vec3(0);
                    m_speed = 10.0f;
                    m_health = 1;
                    m_mana = 1;
                    m_currentHealth = 1;
                    m_currentMana = 1;
                    generate(inventory);
                    m_skill.push_back(new Fireball("Fireball"));
                    m_skill.push_back(new Cyclone("Cyclone"));
                    m_skill.push_back(new Zombie("Zombie"));
                    stats.attack = 1;
                    stats.defense = 1;
                    stats.magicAttack = 1;
                    stats.magicDefense = 1;
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
    std::uniform_int_distribution<int> u(MINSTATS, MAXSTATS);

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
                    << " Fitness:" << it->second[j]->fitness
                    << std::endl;
        }
        std::cout << std::endl;
    }
}

void Player::autoEquip() {
    for(auto it = inventory.begin(); it!= inventory.end(); ++it) {
        std::cout << "{Slot:" << it->first << "}" << std::endl
            << "Items:" << std::endl;
        std::sort(it->second.begin(), it->second.end(), [](Equipment * a, Equipment * b) { return a->fitness > b->fitness;});
        for(int j = 0; j < it->second.size(); j++) {
            it->second[0]->isEquip = true;
            if(it->second[j]->isEquip == true) {
                std::cout << "ID:" << it->second[j]->m_id
                        << " Attack:" << it->second[j]->m_stats.attack
                        << " Defense:" << it->second[j]->m_stats.defense
                        << " MagicAttack:" << it->second[j]->m_stats.magicAttack
                        << " MagicDefense:" << it->second[j]->m_stats.magicDefense
                        << " Fitness:" << it->second[j]->fitness
                        << std::endl;
                stats.attack += it->second[j]->m_stats.attack;
                stats.defense += it->second[j]->m_stats.defense;
                stats.magicAttack += it->second[j]->m_stats.magicAttack;
                stats.magicDefense += it->second[j]->m_stats.magicDefense;
            }
        }
    }
}
//Simple Level system.
//Can be changed later.
void Player::setLevel(int level) {
    stats.attack = level * stats.attack;
    stats.defense = level * stats.defense;
    stats.magicAttack = level * stats.magicAttack;
    stats.magicDefense = level * stats.magicDefense;

    m_health = level * 123;
    m_mana = m_mana * 10 * level;
    m_currentHealth = m_health;
    m_currentMana = m_mana;
    
}

void Player::simulate(Player & player,Enemy & target) {
    //Setting the player and target to be the same level
    
    player.setLevel(35);
    std::cout << "Maximum health:" << player.m_health 
                << " Maximum Mana:" << player.m_mana
                << " Attack:" << player.stats.attack
                << " Defense:" << player.stats.defense
                << " Magic Attack:" << player.stats.magicAttack
                << " Magic Defense:" << player.stats.defense
                << std::endl;  
    target.setLevel(35);

    std::cout << "Maximum health:" << target.m_health 
                << " Maximum Mana:" << target.m_mana
                << " Attack:" << target.stats.attack
                << " Defense:" << target.stats.defense
                << " Magic Attack:" << target.stats.magicAttack
                << " Magic Defense:" << target.stats.defense
                << std::endl;  

    std::string playerSkillName;
    std::string enemySkillName;

    float playerDamage = 0;
    float enemyDamage = 0;

    float totalDamageReceived = 0;
    float totalDamage = 0;

    int turns = 0;
    //std::cout << "Enemy Stats:" << target.stats.attack << std::endl;
    
    for(auto it = player.inventory.begin(); it!=player.inventory.end(); ++it) {
        for(int j = 0; j < it->second.size(); j++) {
            playerDamage = 0;
            while(totalDamageReceived < player.m_currentHealth && totalDamage < target.m_currentHealth) {
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
                        float playerSkillDamage = player.m_skill[k]->activate(playerTempStats,target);
                        if(playerDamage <= playerSkillDamage) {
                            playerDamage = playerSkillDamage;
                            playerSkillName = player.m_skill[k]->m_name;
                        }  
                    }

                    for(int l = 0; l < target.m_skill.size(); l++) {
                        //std::cout << "Enemy casting:" << target.m_skill[l]->m_name << std::endl;
                        float enemySkillDamage = target.m_skill[l]->activate(target.stats, player);
                        if(enemyDamage <= enemySkillDamage) {
                            enemySkillName = target.m_skill[l]->m_name;
                            enemyDamage = enemySkillDamage;
                        }
                    }
                }
                
                totalDamage += playerDamage;
                totalDamageReceived += enemyDamage;
                turns++;

                if(!(totalDamageReceived < player.m_currentHealth && totalDamage < target.m_currentHealth)) {
                    std::cout << "Total Turns:" << turns << std::endl;
                }
            }

            //Divide by zero case. Assuming player is so tanky and takes no damage.
            if(totalDamageReceived > 0) {
                it->second[j]->fitness =  totalDamage / totalDamageReceived;

                if(turns == 1) {
                    std::cout << "Player Damage Per Turn:" << playerDamage << " Enemy Damage Per Turn:" << enemyDamage << std::endl;
                    std::cout << std::endl;
                    std::cout << playerSkillName << "|" << enemySkillName << std::endl;
                    std::cout << "InvalidID:" << it->second[j]->m_id
                        << " Attack:" << it->second[j]->m_stats.attack
                        << " Defense:" << it->second[j]->m_stats.defense
                        << " MagicAttack:" << it->second[j]->m_stats.magicAttack
                        << " MagicDefense:" << it->second[j]->m_stats.magicDefense
                        << std::endl;
                }
            }
           
            playerDamage = 0;
            enemyDamage = 0;
            turns = 0;
            totalDamage = 0;
            totalDamageReceived = 0;

        }

    }
}

bool Player::combat(Player & player, Enemy & target) {
    bool isDead = true;
    int option = -1;

    float enemyDamage = 0;
    std::string enemySkillName = "";

    float playerDamage = 0;
    float enemyTotalDamage = 0;
    float playerTotalDamage = 0;
    for(int l = 0; l < target.m_skill.size(); l++) {
        //std::cout << "Enemy casting:" << target.m_skill[l]->m_name << std::endl;
        float enemySkillDamage = target.m_skill[l]->activate(target.stats, player);
        if(enemyDamage <= enemySkillDamage) {
            enemySkillName = target.m_skill[l]->m_name;
            enemyDamage = enemySkillDamage;
        }
    }

    std::cout << "Combat Start!" << std::endl;
    while(player.m_currentHealth > 0 && target.m_currentHealth > 0) {
        std::cout << "Select Skill:" << std::endl;
        for(int i = 0; i < player.m_skill.size(); i++) {
            std::cout << i << ":" << player.m_skill[i]->getName() << std::endl;
        }
        //Player is selecting skill.
        while(std::cin >> option) {
            if(option >= 0 && option < player.m_skill.size()) {
                std::cout << "Player selected:" << player.m_skill[option]->getName() << std::endl;
                std::cout << "Enemy selected:" << enemySkillName << std::endl;
                
                playerDamage = player.m_skill[option]->activate(stats, target);
                std::cout << "Player dealt:" << playerDamage << std::endl;
                std::cout << "Enemy dealt:" << enemyDamage << std::endl;
                playerTotalDamage += playerDamage;
                enemyTotalDamage += enemyDamage;
                std::cout << "Enemy current hp" << target.m_currentHealth - playerTotalDamage << std::endl;
                std::cout << "Player current hp" << player.m_currentHealth - enemyTotalDamage << std::endl;

                if(playerTotalDamage > target.m_currentHealth) {
                    isDead = true;
                    std::cout << "Enemy has been slained" << std::endl;
                    return isDead;
                }

                if(enemyTotalDamage > player.m_currentHealth) {
                    std::cout << "Player has been slained" << std::endl;
                    return isDead;
                }
            }
        }
    }
    return isDead;
}
