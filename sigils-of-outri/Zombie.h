#pragma once

#include <engine/rpg/Skill.h>

class Stats;
class Zombie : public Skill {
public:
    Zombie(const char * name);
    ~Zombie();
    
    virtual float activate(Stats & stats, Character & target) override;

private:

};