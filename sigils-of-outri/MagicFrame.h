#pragma once

#include <engine/rpg/Skill.h>

class Stats;
class MagicFrame : public Skill {
public:
    MagicFrame(const char * name);
    ~MagicFrame();
    
    virtual float activate(Stats & stats, Character & target) override;

private:

};