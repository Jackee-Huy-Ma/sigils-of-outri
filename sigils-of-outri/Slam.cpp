#include "Slam.h"
#include <engine/rpg/Stats.h>
#include <iostream>
#include <engine/rpg/Character.h>
Slam::Slam(const char * name) : Skill{name} {

}

Slam::~Slam() {

}

//Parameters.
//Stats object to do math.
//Target to use the skill on.
//Returns damage.
float Slam::activate(Stats & stat, Character & target) {
    std::cout << m_name << " activated" << std::endl;
    
    float damage = (stat.attack) - (target.stats.defense);

    return damage;
}
