#pragma once

#include <engine/rpg/Skill.h>

class Stats;
class Cyclone : public Skill {
public:
    Cyclone(const char * name);
    ~Cyclone();
    
    virtual float activate(Stats & stats, Character & target) override;

private:

};