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
float Cyclone::activate(Stats & stat, Character & target) {
    std::cout << m_name << " activated" << std::endl;
    
    float damage = 50 + stat.attack * 2 - target.stats.defense;

    return damage;
}

