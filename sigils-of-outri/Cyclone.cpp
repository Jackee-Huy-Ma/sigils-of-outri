#include "Cyclone.h"
#include <engine/rpg/Stats.h>
#include <iostream>
#include <engine/rpg/Character.h>

Cyclone::Cyclone(const char * name) : Skill{name} {

}

Cyclone::~Cyclone() {

}

//Parameters.
//Stats object to do math.
//Target to use the skill on.
//Returns damage.
int Cyclone::activate(Stats & stat, Character & target) {
    std::cout << m_name << " activated" << std::endl;
    
    int damage = (stat.attack * 200) - (target.stats.defense);

    return damage;
}

