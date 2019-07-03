#ifndef PERSONTESTS_H
#define PERSONTESTS_H
#include <QTest>

class PersonTests : public QObject
{
    Q_OBJECT
public slots:
    void onUpdateMovementData(QVariant newX, QVariant newY, QVariant time, QVariant rotationAngle)
    {
        _newPos = QPoint(newX.toInt(), newY.toInt());
        _newTime = time.toInt();
        _newRotation = rotationAngle.toInt();
    }
    void onUpdatePersonMovementStats(QVariant newSpeed, QVariant newRotationSpeed)
    {
        _newSpeed = newSpeed.toUInt();
        _newRotationSpeed = newRotationSpeed.toUInt();
    }
signals:
    void positionChanged(int x, int y, int rotation);
private slots:
    void TestCase_Person_DeafultContructor();

    //UI Item
    void TestCase_Person_setUiItem_isNullPtr();
    void TestCase_Person_setUiItem_Valid();
    //action - movement attack
    void TestCase_Person_move_Rotation_0();
    void TestCase_Person_move_Rotation_ClockWise_45();
    void TestCase_Person_move_Rotation_ClockWise_90();
    void TestCase_Person_move_Rotation_ClockWise_135();
    void TestCase_Person_move_Rotation_ClockWise_180();
    void TestCase_Person_move_Rotation_CounterClockWise_45();
    void TestCase_Person_move_Rotation_CounterClockWise_90();
    void TestCase_Person_move_Rotation_CounterClockWise_135();

    void TestCase_Person_onWeaponChange_ChangeToMeleeWeapon();
    void TestCase_Person_onWeaponChange_ChangeToRangedWeapon();

    void TestCase_Person_onAttackPressed_NoOpponentInRange();
    void TestCase_Person_onAttackPressed_OpponentInRange();

    void TestCase_Person_addExp_EnemyKilled_NoLevelUp();
    void TestCase_Person_addExp_EnemyKilled_LevelUp();

    void TestCase_Person_ReceivedDamage_DamageNonLethal();
    void TestCase_Person_ReceivedDamage_DamageLethal();

    void TestCase_Person_changeArmor_newArmorEquipped();
    void TestCase_Person_addWeapon_NewWeaponAdded_FitsInInventory();
    void TestCase_Person_addWeapon_NewWeaponNotFitsInInventory();
    void TestCase_Person_replaceWeapon_FullInventory_MeleeWeapon_1_Replaced();

    void TestCase_Person_CopyContructor();
    void TestCase_Person_CopyAssignment();
    void TestCase_Person_MoveContructor();
    void TestCase_Person_MoveAssignment();
private:
    QPoint _newPos{0, 0};
    int _newTime{0};
    int _newRotation{0};
    quint16 _newSpeed{0};
    quint16 _newRotationSpeed{0};
};

#endif // PERSONTESTS_H
