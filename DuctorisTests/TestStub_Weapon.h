#ifndef TESTSTUB_WEAPON_H
#define TESTSTUB_WEAPON_H
#include "weapon.h"

class TestStub_Weapon : public Weapon
{
public:
    TestStub_Weapon() = default;

    void tst_setWeaponType(const WeaponType weaponType);
};

#endif // TESTSTUB_WEAPON_H
