#include "Enemy.h"

Enemy::Enemy(std::string name, glm::vec3 position,
            glm::vec3 rotation, glm::vec3 scale, const char * texturePath) : 
                Character{name, position, rotation, scale, texturePath} {

                    m_velocity = glm::vec3(0);
                    m_speed = 0;
                    setLevel(1);

                    m_skill.push_back(new CorpseExplosion("CorpseExplosion"));
                    m_skill.push_back(new MagicFrame("MagicFrame"));
                    m_skill.push_back(new Slam("Slam"));

                    m_health = 1;
                    m_mana = 1;
                    m_currentMana = 1;
                    m_currentHealth = 1;

}

Enemy::~Enemy() {

}

void Enemy::setLevel(int level) {
    stats.attack = level * stats.attack;
    stats.defense = level * stats.defense;
    stats.magicAttack = level * stats.magicAttack;
    stats.magicDefense = level * stats.magicDefense;

    m_health = level * 136;
    m_mana = m_mana * 11 * level;
    m_currentHealth = m_health;
    m_currentMana = m_mana;
}
