#pragma once

#include <engine/rpg/Skill.h>

class Stats;
class Slam : public Skill {
public:
    Slam(const char * name);
    ~Slam();
    
    virtual int activate(Stats & stats, Character & target) override;

private:

};