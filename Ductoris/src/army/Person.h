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
        uint16_t m_health{0};
        uint16_t m_morale{0};
        uint16_t m_attack{0};
        uint16_t m_defence{0};
        uint16_t m_stamina{0};
        uint16_t m_speed{0};

        void addBonus(SkillTree::LevelBonus bonus)
        {
            m_health += bonus.m_healthBonus;
            m_defence += bonus.m_defenceBonus;
            m_attack += bonus.m_attackBonus;
            m_morale += bonus.m_moraleBonus;
            m_speed += bonus.m_speedBonus;
            m_stamina += bonus.m_stamina;
        }
    };

    Person();
    Person(const Person &other);
    Person& operator=(const Person &other);
    virtual ~Person();

    void setPosition(uint32_t x, uint32_t y);
    std::pair<uint32_t, uint32_t> getPosition() const;

    virtual bool addExp(uint16_t exp);
    virtual void changeArmor(Armor &&armor);
    virtual void addWeapon(const Weapon &weapon);
protected:
    //Type
    //PersonType m_type;
    std::unique_ptr<SkillTree> m_skillTree{nullptr};
    //Person Stats
    Stats m_stats;
    uint32_t m_exp{0};
    uint8_t m_level{0};
    //equipment
    Armor m_armor;
    std::vector<Weapon> m_weapons;
    //location
    std::pair<uint32_t, uint32_t> m_position;
};

#endif // PERSON_H
