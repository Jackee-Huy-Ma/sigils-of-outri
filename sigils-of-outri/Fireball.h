#pragma once

#include <engine/rpg/Skill.h>

class Stats;
class Fireball : public Skill {
public:
    Fireball(const char * name);
    ~Fireball();
    
    virtual int activate(Stats & stats, Character & target) override;

private:

};