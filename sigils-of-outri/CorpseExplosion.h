#pragma once

#include <engine/rpg/Skill.h>

class Stats;
class CorpseExplosion : public Skill {
public:
    CorpseExplosion(const char * name);
    ~CorpseExplosion();
    
    virtual float activate(Stats & stats, Character & target) override;

private:

};