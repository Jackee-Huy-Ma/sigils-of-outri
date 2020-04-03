#include "Skill.h"
#include "Character.h"

Skill::Skill(const char * name) {
    m_name = name;
}

Skill::~Skill() {

}

float Skill::activate(Stats & stats, Character & target) {
    std::cout << m_name << " activated" << std::endl;
    return 0;
}

std::string Skill::getName() {
    return m_name;
}