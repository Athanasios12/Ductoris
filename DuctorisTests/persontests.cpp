#include "persontests.h"
#include "Person.h"
#include <QQmlProperty>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQmlApplicationEngine>

class PersonTestChild : public Person
{
public:
    PersonTestChild();
    PersonTestChild();

    void setWeaponAchorPoint(const QPoint &position)
    {
        m_weaponAnchorPoint = position;
    }//use this to set the parent variable

    bool heckIfEnemyInWeaponRange(const QQuickItem *enemyUiItem)
    {
        if(m_uiItem && enemyUiItem)
        {
            auto currentWeapon = m_weapons[m_currentWeaponIdx];
            if(currentWeapon)
            {
                int weaponWidth = currentWeapon->getSize().width();
                int weaponHeight = currentWeapon->getSize().height();
                const int x0 = m_weaponAnchorPoint.x();
                const int y0 = m_weaponAnchorPoint.y();
                for(int x_weapon = x0; x_weapon < weaponWidth + x0; x_weapon++)
                {
                    for(int y_weapon = y0; y_weapon < weaponHeight + y0; y_weapon++)
                    {
                        auto weaponPosInEnemyCoords = m_uiItem->mapToItem(enemyUiItem, QPoint{x_weapon, y_weapon}).toPoint();
                        if(enemyUiItem->contains(weaponPosInEnemyCoords))
                        {
                            return true;
                        }
                    }
                }
            }
        }
        return false;
    }
};

void PersonTests::TestCase_Person_DeafultContructor()
{
    Person person;
    QVERIFY(person.getHeight() == 0);
    QVERIFY(person.getWidth() == 0);
    QVERIFY(person.getRotation() == 0);
    QVERIFY(person.getExp() == 0);
    QVERIFY(person.getLevel() == 0);
    QVERIFY(person.getPosition() == QPoint(0, 0));
    QVERIFY(!person.isConnectedToUi());
}

void PersonTests::TestCase_Person_setUiItem_isNullPtr()
{
    Person person;
    std::unique_ptr<QQuickItem> uiItem(nullptr);
    person.setUiItem(uiItem);

    QVERIFY(person.getHeight() == 0);
    QVERIFY(person.getWidth() == 0);
    QVERIFY(person.getRotation() == 0);
    QVERIFY(person.getPosition() == QPoint(0, 0));
    QVERIFY(!person.isConnectedToUi());
}

void PersonTests::TestCase_Person_setUiItem_Valid()
{
    Person person;
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    const QPoint personPos(10, 10);
    const QSize personSize(10, 10);
    const qreal personRotation = 25;

    uiItem->setRotation(personRotation);
    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);

    person.setUiItem(uiItem);

    QVERIFY(person.isConnectedToUi());
    QVERIFY(person.getPosition() == personPos);
    QVERIFY(person.getWidth() == personSize.width());
    QVERIFY(person.getHeight() == personSize.height());
    QVERIFY(person.getRotation() == personRotation);
}

//Movement Test Cases - rotation angle and positioning in local and global coordinates system
//custom rotation angle calculation for coordinates system:
// o------> x
// '
// '
// v y
void PersonTests::TestCase_Person_move_Rotation_0()
{
    Person person;
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    const QPoint personPos(100, 100);
    const QSize personSize(10, 10);
    const qreal personRotation = 0;

    uiItem->setRotation(personRotation);
    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    person.setUiItem(uiItem);

    int newX = 100;
    int newY = 90;
    const int newRotation = 0;
    const int rotationTolerance = 1;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &onUpdateMovementData);
    person.move(newX + static_cast<int>(personSize.width() / 2), newY + static_cast<int>(personSize.height() / 2));

    QVERIFY(person.isConnectedToUi());
    QVERIFY(newX == _newPos.x());
    QVERIFY(newY == _newPos.y());
    QVERIFY((_newRotation >= newRotation - rotationTolerance) && (_newRotation <= newRotation + rotationTolerance));
}

void PersonTests::TestCase_Person_move_Rotation_ClockWise_45()
{
    Person person;
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    const QPoint personPos(100, 100);
    const QSize personSize(10, 10);
    const qreal personRotation = 0;

    uiItem->setRotation(personRotation);
    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    person.setUiItem(uiItem);

    int newX = 110;
    int newY = 90;
    const int newRotation = 45;
    const int rotationTolerance = 1;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &onUpdateMovementData);
    person.move(newX + static_cast<int>(personSize.width() / 2), newY + static_cast<int>(personSize.height() / 2));

    QVERIFY(person.isConnectedToUi());
    QVERIFY(newX == _newPos.x());
    QVERIFY(newY == _newPos.y());
    QVERIFY((_newRotation >= newRotation - rotationTolerance) && (_newRotation <= newRotation + rotationTolerance));
}

void PersonTests::TestCase_Person_move_Rotation_ClockWise_90()
{
    Person person;
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    const QPoint personPos(100, 100);
    const QSize personSize(10, 10);
    const qreal personRotation = 0;

    uiItem->setRotation(personRotation);
    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    person.setUiItem(uiItem);

    int newX = 110;
    int newY = 100;
    const int newRotation = 90;
    const int rotationTolerance = 1;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &onUpdateMovementData);
    person.move(newX + static_cast<int>(personSize.width() / 2), newY + static_cast<int>(personSize.height() / 2));

    QVERIFY(person.isConnectedToUi());
    QVERIFY(newX == _newPos.x());
    QVERIFY(newY == _newPos.y());
    QVERIFY((_newRotation >= newRotation - rotationTolerance) && (_newRotation <= newRotation + rotationTolerance));
}

void PersonTests::TestCase_Person_move_Rotation_ClockWise_135()
{
    Person person;
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    const QPoint personPos(100, 100);
    const QSize personSize(10, 10);
    const qreal personRotation = 0;

    uiItem->setRotation(personRotation);
    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    person.setUiItem(uiItem);

    int newX = 110;
    int newY = 110;
    const int newRotation = 135;
    const int rotationTolerance = 1;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &onUpdateMovementData);
    person.move(newX + static_cast<int>(personSize.width() / 2), newY + static_cast<int>(personSize.height() / 2));

    QVERIFY(person.isConnectedToUi());
    QVERIFY(newX == _newPos.x());
    QVERIFY(newY == _newPos.y());
    QVERIFY((_newRotation >= newRotation - rotationTolerance) && (_newRotation <= newRotation + rotationTolerance));
}

void PersonTests::TestCase_Person_move_Rotation_ClockWise_180()
{
    Person person;
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    const QPoint personPos(100, 100);
    const QSize personSize(10, 10);
    const qreal personRotation = 0;

    uiItem->setRotation(personRotation);
    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    person.setUiItem(uiItem);

    int newX = 100;
    int newY = 110;
    const int newRotation = 180;
    const int rotationTolerance = 1;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &onUpdateMovementData);
    person.move(newX + static_cast<int>(personSize.width() / 2), newY + static_cast<int>(personSize.height() / 2));

    QVERIFY(person.isConnectedToUi());
    QVERIFY(newX == _newPos.x());
    QVERIFY(newY == _newPos.y());
    QVERIFY((_newRotation >= newRotation - rotationTolerance) && (_newRotation <= newRotation + rotationTolerance));
}

void PersonTests::TestCase_Person_move_Rotation_CounterClockWise_45()
{
    Person person;
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    const QPoint personPos(100, 100);
    const QSize personSize(10, 10);
    const qreal personRotation = 0;

    uiItem->setRotation(personRotation);
    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    person.setUiItem(uiItem);

    int newX = 90;
    int newY = 90;
    const int newRotation = -45;
    const int rotationTolerance = 1;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &onUpdateMovementData);
    person.move(newX + static_cast<int>(personSize.width() / 2), newY + static_cast<int>(personSize.height() / 2));

    QVERIFY(person.isConnectedToUi());
    QVERIFY(newX == _newPos.x());
    QVERIFY(newY == _newPos.y());
    QVERIFY((_newRotation >= newRotation - rotationTolerance) && (_newRotation <= newRotation + rotationTolerance));
}

void PersonTests::TestCase_Person_move_Rotation_CounterClockWise_90()
{
    Person person;
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    const QPoint personPos(100, 100);
    const QSize personSize(10, 10);
    const qreal personRotation = 0;

    uiItem->setRotation(personRotation);
    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    person.setUiItem(uiItem);

    int newX = 90;
    int newY = 100;
    const int newRotation = -90;
    const int rotationTolerance = 1;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &onUpdateMovementData);
    person.move(newX + static_cast<int>(personSize.width() / 2), newY + static_cast<int>(personSize.height() / 2));

    QVERIFY(person.isConnectedToUi());
    QVERIFY(newX == _newPos.x());
    QVERIFY(newY == _newPos.y());
    QVERIFY((_newRotation >= newRotation - rotationTolerance) && (_newRotation <= newRotation + rotationTolerance));
}

void PersonTests::TestCase_Person_move_Rotation_CounterClockWise_135()
{
    Person person;
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    const QPoint personPos(100, 100);
    const QSize personSize(10, 10);
    const qreal personRotation = 0;

    uiItem->setRotation(personRotation);
    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    person.setUiItem(uiItem);

    int newX = 90;
    int newY = 110;
    const int newRotation = -135;
    const int rotationTolerance = 1;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &onUpdateMovementData);
    person.move(newX + static_cast<int>(personSize.width() / 2), newY + static_cast<int>(personSize.height() / 2));

    QVERIFY(person.isConnectedToUi());
    QVERIFY(newX == _newPos.x());
    QVERIFY(newY == _newPos.y());
    QVERIFY((_newRotation >= newRotation - rotationTolerance) && (_newRotation <= newRotation + rotationTolerance));
}

//Battle movement and attacks test cases
void PersonTests::TestCase_Person_move_MoveToNewDestination_Idle_To_Moving()
{
    Person person;
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    const QPoint personPos(100, 100);
    const QSize personSize(10, 10);
    const qreal personRotation = 0;

    uiItem->setRotation(personRotation);
    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    person.setUiItem(uiItem);

    int newX = 90;
    int newY = 110;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &onUpdateMovementData);
    QVERIFY(person.getCurrentState() == Person::PersonState::Idle);
    person.move(newX + static_cast<int>(personSize.width() / 2), newY + static_cast<int>(personSize.height() / 2));
    QVERIFY(person.getCurrentState() == Person::PersonState::Moving);
}

void PersonTests::TestCase_Person_move_ReachedDestination_Moving_To_Idle()
{
    Person person;
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    const QPoint personPos(100, 100);
    const QSize personSize(10, 10);
    const qreal personRotation = 0;

    uiItem->setRotation(personRotation);
    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    person.setUiItem(uiItem);

    int newX = 90;
    int newY = 110;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &onUpdateMovementData);
    QObject::connect(this, &positionChanged, &person, &Person::onPositionChanged);
    QVERIFY(person.getCurrentState() == Person::PersonState::Idle);
    person.move(newX + static_cast<int>(personSize.width() / 2), newY + static_cast<int>(personSize.height() / 2));
    QVERIFY(person.getCurrentState() == Person::PersonState::Moving);
    //signal reaching destination
    positionChanged(newX, newY, 0);
    QVERIFY(person.getCurrentState() == Person::PersonState::Idle);
}

void PersonTests::TestCase_Person_move_CancelAttack_MovingToAttack_To_Moving()
{
    Person person;
    std::shared_ptr<Person> enemy(new Person);
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    std::unique_ptr<QQuickItem> enemyUiItem(new QQuickItem);
    const QPoint personPos(100, 100);
    const QPoint enemyPos(100, 150);
    const QSize personSize(10, 10);
    const qreal personRotation = 0;

    uiItem->setRotation(personRotation);
    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    enemyUiItem->setRotation(personRotation);
    enemyUiItem->setSize(personSize);
    enemyUiItem->setPosition(enemyPos);

    person.setUiItem(uiItem);
    enemy->setUiItem(enemyUiItem);

    QObject::connect(&person, &Person::updatePersonMovementData, this, &onUpdateMovementData);
    QObject::connect(this, &positionChanged, &person, &Person::onPositionChanged);
    QVERIFY(person.getCurrentState() == Person::PersonState::Idle);
    person.attack(enemy);
    QVERIFY(person.getCurrentState() == Person::PersonState::MovingToAttack);
    int newX = 90;
    int newY = 110;
    person.move(newX, newY);
    QVERIFY(person.getCurrentState() == Person::PersonState::Moving);
}
//dokończyć ten test case - dodać dodanie broni do person
void PersonTests::TestCase_Person_attack_OponnentNotInRange_Idle_To_MovingToAttack()
{
    PersonTestChild person;
    std::shared_ptr<Person> enemy(new Person);
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    std::unique_ptr<QQuickItem> enemyUiItem(new QQuickItem);

    const QPoint personPos(100, 100); //person position in global coordinates
    const QPoint enemyPos(100, 150);
    //person range depends on his size and the size of his currently held weapon
    const QSize personSize(10, 10);
    const qreal personRotation = 0;
    const QPoint personArmPosition(8, 8); // arm position in person coordinates system
    const QSize personArmSize(2, 4); //arm holding the weapon has a separate sprite which is subsprite of person Sprite
    const QSize weaponSize(2, 6);
    // in person's arm local coordinates system - its centered so that it fits evenly
    const QPoint weaponPersonAnchor(static_cast<int>(personArmSize.width() / 2) - static_cast<int>(weaponSize.width() / 2),
                                    personArmSize.height());
    //transform it to person coordinates system
    weaponPersonAnchor.setX(weaponPersonAnchor.x() + personArmPosition.x());
    weaponPersonAnchor.setY(weaponPersonAnchor.y() + personArmPosition.y());


    //Crete primary weapon - normally would be done with Weapon support classes that load specs from config files and
    // based on that load a specific sprite with stats defined in weapon config file
    //Weapon id is determined by specific person config - every person object has a config file which stores the
    //weapon ids that this person owns. During equipment shopping in Camp new weapons are added to specific units,
    //among other equipment. For specified units types - roman hastati has specified config file that is his base and holds
    //info about his equipment - those ids that are used to find the coresponding config file for weapon or armor.

    uiItem->setRotation(personRotation);
    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    enemyUiItem->setRotation(personRotation);
    enemyUiItem->setSize(personSize);
    enemyUiItem->setPosition(enemyPos);

    person.setUiItem(uiItem);
    enemy->setUiItem(enemyUiItem);
    person.setWeaponAchorPoint(weaponPersonAnchor); // for tests set it manually
    //normally when weapon pulled out or changed the signal is sent to ui to change the sprite, then on sprite change
    //the anchor point is recalculated to correctly position the weapon(size change trigger).
    //then the anchor point is read using QQmlProperty::read when checkIfInWeaponRange() method is called

    //set person weapon , make it primary

    QObject::connect(&person, &Person::updatePersonMovementData, this, &onUpdateMovementData);
    QObject::connect(this, &positionChanged, &person, &Person::onPositionChanged);
    QVERIFY(person.getCurrentState() == Person::PersonState::Idle);
    person.attack(enemy);
    QVERIFY(person.getCurrentState() == Person::PersonState::MovingToAttack);
}

void PersonTests::TestCase_Person_attack_OponnentNotInRange_Moving_To_MovingToAttack()
{
    Person person;
    std::shared_ptr<Person> enemy(new Person);
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    std::unique_ptr<QQuickItem> enemyUiItem(new QQuickItem);
    const QPoint personPos(100, 100);
    const QPoint enemyPos(100, 150);
    const QSize personSize(10, 10);
    const qreal personRotation = 0;

    uiItem->setRotation(personRotation);
    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    enemyUiItem->setRotation(personRotation);
    enemyUiItem->setSize(personSize);
    enemyUiItem->setPosition(enemyPos);

    person.setUiItem(uiItem);
    enemy->setUiItem(enemyUiItem);

    int newX = 90;
    int newY = 110;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &onUpdateMovementData);
    QObject::connect(this, &positionChanged, &person, &Person::onPositionChanged);
    QVERIFY(person.getCurrentState() == Person::PersonState::Idle);
    person.move(newX + static_cast<int>(personSize.width() / 2), newY + static_cast<int>(personSize.height() / 2));
    QVERIFY(person.getCurrentState() == Person::PersonState::Moving);
    person.attack(enemy);
    QVERIFY(person.getCurrentState() == Person::PersonState::MovingToAttack);
}

void PersonTests::TestCase_Person_attack_OponnentInRange_Moving_To_Attacking()
{

}

void PersonTests::TestCase_Person_attack_OponnentInRange_MovingToAttack_To_Attacking()
{

}

void PersonTests::TestCase_Person_attack_OponnentInRange_Idle_To_Attacking()
{

}

void PersonTests::TestCase_Person_move_DisengageAndRetreat_Attack_To_Retreat()
{

}

void PersonTests::TestCase_Person_move_InterceptedDuringRetreat_Retreat_To_Defend()
{

}

void PersonTests::TestCase_Person_onWeaponChange_ChangeToMeleeWeapon()
{

}

void PersonTests::TestCase_Person_onWeaponChange_ChangeToRangedWeapon()
{

}

//Damage Tests
void PersonTests::TestCase_Person_ReceivedDamage_DamageNonLethal()
{

}

void PersonTests::TestCase_Person_ReceivedDamage_DamageLethal()
{

}

//Armor Tests
void PersonTests::TestCase_Person_changeArmor_newArmorEquipped()
{

}

void PersonTests::TestCase_Person_addWeapon_NewWeaponAdded_FitsInInventory()
{

}

//
void PersonTests::TestCase_Person_addWeapon_NewWeaponNotFitsInInventory()
{

}

void PersonTests::TestCase_Person_replaceWeapon_FullInventory_MeleeWeapon_1_Replaced()
{

}

//Non default Constructors
void PersonTests::TestCase_Person_CopyContructor()
{

}

void PersonTests::TestCase_Person_CopyAssignment()
{

}

void PersonTests::TestCase_Person_MoveContructor()
{

}

void PersonTests::TestCase_Person_MoveAssignment()
{

}
