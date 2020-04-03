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
int Slam::activate(Stats & stat, Character & target) {
    std::cout << m_name << " activated" << std::endl;
    
    int damage = (stat.attack + 20) - target.stats.defense;

    return damage;
}
