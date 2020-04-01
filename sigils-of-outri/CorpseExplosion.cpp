#include "CorpseExplosion.h"
#include <engine/rpg/Stats.h>
#include <iostream>
#include <engine/rpg/Character.h>
CorpseExplosion::CorpseExplosion(const char * name) : Skill{name} {

}

CorpseExplosion::~CorpseExplosion() {

}

//Parameters.
//Stats object to do math.
//Target to use the skill on.
//Returns damage.
int CorpseExplosion::activate(Stats & stat, Character & target) {
    std::cout << m_name << " activated" << std::endl;
    
    int damage = target.m_health * 0.5;

    return damage;
}
