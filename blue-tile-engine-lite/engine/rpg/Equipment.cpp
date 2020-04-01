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

void Equipment::generate(std::vector<Equipment *> & equipment) {
    std::default_random_engine e;
    std::uniform_int_distribution<int> u(-2, 10);

    equipment.clear();

    int i = 0;
    
    while(equipment.size() != 10) {
        Stats stats = {u(e), u(e), u(e), u(e)};

        equipment.push_back(new Equipment(i, stats));
        i++;
    }
}