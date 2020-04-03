#include "Zombie.h"
#include <engine/rpg/Stats.h>
#include <iostream>
#include <engine/rpg/Character.h>

Zombie::Zombie(const char * name) : Skill{name} {

}

Zombie::~Zombie() {

}

//Parameters.
//Stats object to do math.
//Target to use the skill on.
//Returns damage.
float Zombie::activate(Stats & stat, Character & target) {
    std::cout << m_name << " activated:" << std::endl;
    
    float damage =  50 + (stat.attack * 2) - (target.stats.magicDefense + 1);

    return damage;
}

