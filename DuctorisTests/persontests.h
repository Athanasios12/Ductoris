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

    //movement angle and position tests
    void TestCase_Person_move_Rotation_0();
    void TestCase_Person_move_Rotation_ClockWise_45();
    void TestCase_Person_move_Rotation_ClockWise_90();
    void TestCase_Person_move_Rotation_ClockWise_135();
    void TestCase_Person_move_Rotation_ClockWise_180();
    void TestCase_Person_move_Rotation_CounterClockWise_45();
    void TestCase_Person_move_Rotation_CounterClockWise_90();
    void TestCase_Person_move_Rotation_CounterClockWise_135();

    //Movement - stamina loss tests

    //Attack - stamina loss tests

    //Attack - charge bonus tests - only for cavalry and shock troops that accelerate at the last phase of attack

    //Defend - morale increase loss, stamina loss when transition from retreating

    //Defend - no additional morale loss when transitioned from idle and facing the enemy, otherwise flanking  and back attack penalties

    //Defend - when intercepted during movement in MovingToAttack on another enemy or normal Moving - additional morale loss and stamina loss for this transition
    //based on angle of interception - if face on then no charge bonus, automatic changing locked on enemy to interceptor. If interceptor flanks,
    //bigger penalties then normal flanking stationary target, if back attack then penalties the same as the stationary target

    //

    //Person Battle and movement behaviour state machine tests
    void TestCase_Person_move_MoveToNewDestination_Idle_To_Moving();
    void TestCase_Person_move_ReachedDestination_Moving_To_Idle();
    void TestCase_Person_move_CancelAttack_MovingToAttack_To_Moving();

    void TestCase_Person_attack_OponnentNotInRange_Idle_To_MovingToAttack();
    void TestCase_Person_attack_OponnentNotInRange_Moving_To_MovingToAttack();
    void TestCase_Person_attack_OponnentInRange_Moving_To_Attacking();
    void TestCase_Person_attack_OponnentInRange_MovingToAttack_To_Attacking();
    void TestCase_Person_attack_OponnentInRange_Idle_To_Attacking();

    void TestCase_Person_move_DisengageAndRetreat_Attack_To_Retreat();
    void TestCase_Person_move_InterceptedDuringRetreat_Retreat_To_Defend();

    //Weapon test cases
    void TestCase_Person_onWeaponChange_ChangeToMeleeWeapon();
    void TestCase_Person_onWeaponChange_ChangeToRangedWeapon();
    void TestCase_Person_addWeapon_NewWeaponAdded_FitsInInventory();
    void TestCase_Person_addWeapon_NewWeaponNotFitsInInventory();
    void TestCase_Person_replaceWeapon_FullInventory_MeleeWeapon_1_Replaced();

    //Receiving damage test cases - health loss, stamina, morale
    void TestCase_Person_ReceivedDamage_DamageNonLethal();
    void TestCase_Person_ReceivedDamage_DamageLethal();

    //Armor test cases
    void TestCase_Person_changeArmor_newArmorEquipped();


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
