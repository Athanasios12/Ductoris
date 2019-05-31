#ifndef PERSON_H
#define PERSON_H
#include <utility>
#include <cstdint>
#include "armor.h"
#include "weapon.h"
#include <vector>
#include <memory>
#include "skilltree.h"

class Person
{
public:
    struct Stats
    {
        uint16_t m_health;
        uint16_t m_morale;
        uint16_t m_attack;
        uint16_t m_defence;
        uint16_t m_speed;
    };

    Person();
    Person(const Person &other);
    Person& operator=(const Person &other);
    virtual ~Person();

    void setPosition(uint32_t x, uint32_t y);
    std::pair<uint32_t, uint32_t> getPosition() const;

    virtual void addExp(uint16_t exp) = 0;
    virtual void changeArmor(Armor armor) = 0;
    virtual void addWeapon(Weapon weapon) = 0;
protected:
    //Type
    //PersonType m_type;
    std::unique_ptr<SkillTree> m_skillTree;
    //Person Stats
    Stats m_stats;
    uint32_t m_exp;
    uint8_t m_level;
    uint8_t m_maxLevel;
    //equipment
    Armor m_armor;
    std::vector<Weapon> m_weapons;
    //location
    std::pair<uint32_t, uint32_t> m_position;
};

#endif // PERSON_H
