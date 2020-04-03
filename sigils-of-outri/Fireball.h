#pragma once

#include <engine/rpg/Skill.h>

class Stats;
class Fireball : public Skill {
public:
    Fireball(const char * name);
    ~Fireball();
    
    virtual float activate(Stats & stats, Character & target) override;

private:

};