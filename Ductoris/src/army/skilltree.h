#ifndef SKILLTREE_H
#define SKILLTREE_H
#include <vector>
#include <cstdint>

class SkillTree
{
public:
    //perks will be checked by strategy design pattern based algorithm family
    //If unit has one enabled then it unlocks:
    // - additional behaviour - action
    // - bonuses : like for commander number of officers, bodyguard increase
    class Perk
    {
        uint8_t skillplaceholder; //will be some class that defines specific behaviour
    };
    struct LevelBonus
    {
        uint16_t m_healthBonus{0};
        uint16_t m_moraleBonus{0};
        uint16_t m_attackBonus{0};
        uint16_t m_defenceBonus{0};
        uint16_t m_speedBonus{0};
        uint16_t m_stamina{0};
    };

    enum ArmyType
    {
        Roman,
        Macedon,
        Gallic
    };

    SkillTree();
    virtual ~SkillTree();

    virtual bool checkIfThresholdReached(uint32_t exp) const = 0;
    virtual LevelBonus getLevelBonus(uint8_t levelNumber) const = 0;
    uint8_t getMaxLevel() const;
    ArmyType getArmyType() const;
protected:
    ArmyType m_armyType;
    std::vector<Perk> m_perks;
    std::vector<uint32_t> m_levelThresholds;    
};

#endif // SKILLTREE_H
