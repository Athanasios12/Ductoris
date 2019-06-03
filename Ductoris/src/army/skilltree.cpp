#include "skilltree.h"

SkillTree::SkillTree()
{

}

SkillTree::~SkillTree()
{

}

uint8_t SkillTree::getMaxLevel() const
{
    return m_levelThresholds.size();
}

SkillTree::ArmyType SkillTree::getArmyType() const
{
    return m_armyType;
}
