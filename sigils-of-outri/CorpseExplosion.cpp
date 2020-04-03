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
float CorpseExplosion::activate(Stats & stat, Character & target) {
    std::cout << m_name << " activated" << std::endl;
    
    int damage = (stat.magicAttack * 2) - (target.stats.magicDefense);
    return damage;
}
