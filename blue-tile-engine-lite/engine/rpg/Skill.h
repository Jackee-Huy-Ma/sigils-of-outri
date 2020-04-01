#pragma once

#include <string>
#include <iostream>

class Stats;
class Character;
class Skill {
public:
    Skill(const char * name);
    ~Skill();
    std::string m_name;
    virtual int activate(Stats & stats, Character & target);
};