#pragma once
#include <vector>
#include <random>
#include "Stats.h"

class Equipment {
public:
    Equipment(int id, const Stats & stats);
    ~Equipment();
    int m_id;
    Stats m_stats;
    bool isEquip;
    void generate(std::vector<Equipment *> & equipment);
private:
};