#include "Equipment.h"
#include "Stats.h"
#include <random>

Equipment::Equipment(int id, const Stats & stats) {
    m_id = id;
    m_stats = stats;
    isEquip = false;
}

Equipment::~Equipment() {
}

