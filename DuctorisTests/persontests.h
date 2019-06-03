#ifndef PERSONTESTS_H
#define PERSONTESTS_H
#include <QTest>

class PersonTests : public QObject
{
    Q_OBJECT
private slots:
    void TestCase_Person_DeafultContructor();

    //action - movement attack
    void TestCase_Person_movePressed_validPosition();

    void TestCase_Person_onWeaponChange_ChangeToMeleeWeapon();
    void TestCase_Person_onWeaponChange_ChangeToRangedWeapon();

    void TestCase_Person_onAttackPressed_NoOpponentInRange();
    void TestCase_Person_onAttackPressed_OpponentInRange();

    void TestCase_Person_addExp_EnemyKilled_NoLevelUp();
    void TestCase_Person_addExp_EnemyKilled_NoLevelUp();

    void TestCase_Person_ReceivedDamage_DamageNonLethal();
    void TestCase_Person_ReceivedDamage_DamageLethal();

    void TestCase_Person_changeArmor_newArmorEquipped();
    void TestCase_Person_addWeapon_NewWeaponAdded_FitsInInventory();
    void TestCase_Person_addWeapon_NewWeaponNotFitsInInventory();
    void TestCase_Person_replaceWeapon_FullInventory_MeleeWeapon_1_Replaced();

};

#endif // PERSONTESTS_H
