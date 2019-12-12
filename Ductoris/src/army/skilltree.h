#ifndef SKILLTREE_H
#define SKILLTREE_H
#include <vector>
#include <cstdint>

class SkillTree
{
public:
    //perks will be checked by strategy design pattern based algorithm family
    //If unit has one enabled then it unlocks:
    // - additional behaviour - unlocks unit additional skills
    // - bonuses : like for commander number of officers, bodyguard increase,
    //for unit additional stats bonuses against different types of foes,
    //terrain type or damage type
    class Perk
    {
        uint8_t perkplaceholder;
    };

    //will be some class that defines specific behaviour
    //example skills - form testudo, form phalanx, form shieldwall, rotated attack(legionaries),
    //charge, javelin throw before attack, skirmish (attack and run away automatically
    //when enemy to close.Can be passive or have to be activated explicitly
    class Skills
    {
        uint8_t skillplaceholder;
    };

    struct UnitStats
    {
        uint16_t m_health{0};
        uint16_t m_morale{0};
        uint16_t m_attack{0};
        uint16_t m_defence{0};
        uint16_t m_stamina{0};
        uint16_t m_speed{0};
    };

    SkillTree();
    virtual ~SkillTree();

    virtual bool checkIfLevelThresholdReached(uint32_t exp) const = 0;
    uint16_t getMoraleRetreatThreshold(uint8_t currentLevel) const;
    uint8_t getMaxLevel() const;
protected:
    virtual void levelUp(uint8_t levelNumber) const = 0;
protected:
    UnitStats m_unitStartStats;
    UnitStats m_levelUpBonus;
    std::vector<Perk> m_perks;    
    std::vector<uint32_t> m_levelThresholds;
    std::vector<uint8_t> m_moraleThresholds;
};

#endif // SKILLTREE_H
