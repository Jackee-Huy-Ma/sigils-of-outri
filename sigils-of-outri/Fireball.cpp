#include "Fireball.h"
#include <engine/rpg/Stats.h>
#include <iostream>
#include <engine/rpg/Character.h>

Fireball::Fireball(const char * name) : Skill{name} {

}

Fireball::~Fireball() {

}

//Parameters.
//Stats object to do math.
//Target to use the skill on.
//Returns damage.
int Fireball::activate(Stats & stat, Character & target) {
    std::cout << m_name << " activated" << std::endl;
    
    int damage = (stat.magicAttack * 100) - target.stats.magicDefense;

    return damage;
}


