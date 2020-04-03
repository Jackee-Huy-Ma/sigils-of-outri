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
int Zombie::activate(Stats & stat, Character & target) {
    std::cout << m_name << " activated:" << std::endl;
    
    int damage = 50;

    return damage;
}

