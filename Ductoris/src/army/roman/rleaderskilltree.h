#ifndef RLEADERSKILLTREE_H
#define RLEADERSKILLTREE_H
#include "skilltree.h"

class RLeaderSkillTree : public SkillTree
{
public:
    RLeaderSkillTree();
    ~RLeaderSkillTree();

    bool checkIfThresholdReached(uint32_t exp) const;
    UnitStats getLevelBonus(uint8_t levelNumber) const;
};

#endif // RLEADERSKILLTREE_H
