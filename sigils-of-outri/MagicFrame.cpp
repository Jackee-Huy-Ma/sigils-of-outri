#include "MagicFrame.h"
#include <engine/rpg/Stats.h>
#include <iostream>
#include <engine/rpg/Character.h>
MagicFrame::MagicFrame(const char * name) : Skill{name} {

}

MagicFrame::~MagicFrame() {

}

//Parameters.
//Stats object to do math.
//Target to use the skill on.
//Returns damage.
float MagicFrame::activate(Stats & stat, Character & target) {
    std::cout << m_name << " activated" << std::endl;
    
    float damage = (100 + stat.magicAttack) - target.stats.magicDefense;

    return damage;
}
