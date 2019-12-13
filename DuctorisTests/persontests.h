#ifndef PERSONTESTS_H
#define PERSONTESTS_H
#include <QTest>
#include "Person.h"

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
    //this transitions occurs if enemy moved out of our attacking range -
    //disenaged or retreating. Unit will automaticly pursue enemy if
    //that was ordered or unit type is not disciplined
    void TestCase_Person_attack_OponnentInRange_Attacking_To_MovingToAttack();
    //Killed engaged unit or the unit ran away and the person is disciplined
    //and was ordered not too pursue the fleeing enemy.
    void TestCase_Person_attack_OponnentInRange_Attacking_To_Idle();

    void TestCase_Person_onAttackedByEnemy_Idle_To_Defending();
    void TestCase_Person_onAttackedByEnemy_Defending_To_Retreat();
    void TestCase_Person_onAttackedByEnemy_Attacking_To_Retreat();
    void TestCase_Person_onAttackedByEnemy_Death();

    //Interceptions during movement
    void TestCase_Person_onAttackedByEnemy_FrontIntercept_Moving_To_Defending();
    void TestCase_Person_onAttackedByEnemy_FlankIntercept_Moving_To_Defending();
    void TestCase_Person_onAttackedByEnemy_RearIntercept_Moving_To_Defending();
    void TestCase_Person_onAttackedByEnemy_FrontIntercept_MovingToAttack_To_Defending();
    void TestCase_Person_onAttackedByEnemy_FlankIntercept_MovingToAttack_To_Defending();
    void TestCase_Person_onAttackedByEnemy_RearIntercept_MovingToAttack_To_Defending();
    //Flanked or/and reared during attack - think how the squad or single unit
    //should behave when attacked from rear -
    //1.Change the enemy if single unit and turn on current enemy
    //2.If unit is part of squad then assign new enemy if not directly engaged with frontal attack
    // - back ranks. Have to introduce a difference between individual or part of
    //the squad. If part of the squad, only the front fights first, the back ranks wait
    //unitl they die to step in or if unit organized as roman legion type behaviour
    //the front is changed cyclicly based on stamina and health loss - new line steps in
    //when current first line exausts itself enough or receives to much damage.
    //For phalanx does not apply or less trained units.
    //This class represents just a person, so only a basic behaviour should be considered
    // - person is a single unit. For specific classes that are squadrons then
    // test for different behaviour should be considered as mentioned before.
    void TestCase_Person_onAttackedByEnemy_Flanked_During_Attack();
    void TestCase_Person_onAttackedByEnemy_Reared_During_Attack();

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
