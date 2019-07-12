#ifndef WEAPONTESTS_H
#define WEAPONTESTS_H
#include <QTest>

class WeaponTests: public QObject
{
     Q_OBJECT
private slots:
    //Tests
    void TestCase_Weapon_DeafultConstructor();

    //UI Item
    void TestCase_Weapon_setUiItem_isNullPtr();
    void TestCase_Weapon_setUiItem_Valid();

    void TestCase_Weapon_checkIfOpponentInrange_InRange();
    void TestCase_Weapon_checkIfOpponentInrange_OutOfRange();
    // model is like that: if oponnent sprite colides with weapon sprite weapon is in range of attack
    // and holder can attack with it. Other guy has to get closer to have his weapon in range of the person sprite too

};

#endif // WEAPONTESTS_H
