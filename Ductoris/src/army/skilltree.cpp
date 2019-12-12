#include "skilltree.h"

SkillTree::SkillTree()
{

}

SkillTree::~SkillTree()
{

}

uint16_t SkillTree::getMoraleRetreatThreshold(uint8_t currentLevel) const
{
    if (currentLevel < m_moraleThresholds.size())
    {
        return m_moraleThresholds[currentLevel];
    }
    return 0;
}

uint8_t SkillTree::getMaxLevel() const
{
    return static_cast<uint8_t>(m_levelThresholds.size());
}

