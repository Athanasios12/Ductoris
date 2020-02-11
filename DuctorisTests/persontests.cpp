#include "persontests.h"
#include "TestStub_Person.h"
#include <QQmlProperty>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQmlApplicationEngine>
#include <QSignalSpy>
#include <QQuickWindow>

void PersonTests::initTestCase()
{
    //register whose enums to use them in Person signals
    qRegisterMetaType<Person::AttackOrientation>();
    qRegisterMetaType<Weapon::WeaponType>();
}

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
    int newY = 110;
    const int newRotation = 0;
    const int rotationTolerance = 1;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &PersonTests::onUpdateMovementData);
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

    int newX = 90;
    int newY = 110;
    const int newRotation = 45;
    const int rotationTolerance = 1;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &PersonTests::onUpdateMovementData);
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

    int newX = 90;
    int newY = 100;
    const int newRotation = 90;
    const int rotationTolerance = 1;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &PersonTests::onUpdateMovementData);
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

    int newX = 90;
    int newY = 90;
    const int newRotation = 135;
    const int rotationTolerance = 1;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &PersonTests::onUpdateMovementData);
    person.move(newX + static_cast<int>(personSize.width() / 2), newY + static_cast<int>(personSize.height() / 2));

    QVERIFY(person.isConnectedToUi());
    QVERIFY(newX == _newPos.x());
    QVERIFY(newY == _newPos.y());
    QVERIFY((_newRotation >= newRotation - rotationTolerance) && (_newRotation <= newRotation + rotationTolerance));
}

void PersonTests::TestCase_Person_move_Rotation_180()
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
    const int newRotation = 180;
    const int rotationTolerance = 1;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &PersonTests::onUpdateMovementData);
    person.move(newX + static_cast<int>(personSize.width() / 2), newY + static_cast<int>(personSize.height() / 2));

    QVERIFY(person.isConnectedToUi());
    QVERIFY(newX == _newPos.x());
    QVERIFY(newY == _newPos.y());
    QVERIFY((abs(_newRotation) >= newRotation - rotationTolerance) && (abs(_newRotation) <= newRotation + rotationTolerance));
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

    int newX = 110;
    int newY = 110;
    const int newRotation = -45;
    const int rotationTolerance = 1;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &PersonTests::onUpdateMovementData);
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

    int newX = 110;
    int newY = 100;
    const int newRotation = -90;
    const int rotationTolerance = 1;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &PersonTests::onUpdateMovementData);
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

    int newX = 110;
    int newY = 90;
    const int newRotation = -135;
    const int rotationTolerance = 1;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &PersonTests::onUpdateMovementData);
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

    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    person.setUiItem(uiItem);

    int newX = 90;
    int newY = 110;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &PersonTests::onUpdateMovementData);
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

    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    person.setUiItem(uiItem);

    int newX = 90;
    int newY = 110;
    QObject::connect(&person, &Person::updatePersonMovementData, this, &PersonTests::onUpdateMovementData);
    QObject::connect(this, &PersonTests::positionChanged, &person, &Person::onPositionChanged);
    QVERIFY(person.getCurrentState() == Person::PersonState::Idle);
    person.move(newX + static_cast<int>(personSize.width() / 2), newY + static_cast<int>(personSize.height() / 2));
    QVERIFY(person.getCurrentState() == Person::PersonState::Moving);
    //signal reaching destination
    positionChanged(newX, newY, 0);
    QVERIFY(person.getCurrentState() == Person::PersonState::Idle);
}

void PersonTests::TestCase_Person_move_CancelAttack_MovingToAttack_To_Moving()
{
    TestStub_Person person;
    std::shared_ptr<Person> enemy(new Person);
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    std::unique_ptr<QQuickItem> enemyUiItem(new QQuickItem);
    const QPoint personPos(100, 100);
    const QPoint enemyPos(100, 150);
    const QSize personSize(10, 10);

    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    enemyUiItem->setSize(personSize);
    enemyUiItem->setPosition(enemyPos);

    //create weapon, for tests manually a placeholder with no specified type, later on has to be done
    //from Weapon factory class, based on external config files holding the weapon parameters - attack, defence, speed, etc...
    std::unique_ptr<Weapon> weapon(new Weapon);
    person.addWeapon(weapon);
    person.setUiItem(uiItem);
    enemy->setUiItem(enemyUiItem);

    QObject::connect(&person, &Person::updatePersonMovementData, this, &PersonTests::onUpdateMovementData);
    QObject::connect(this, &PersonTests::positionChanged, &person, &Person::onPositionChanged);
    QVERIFY(person.getCurrentState() == Person::PersonState::Idle);
    person.attack(enemy);
    QVERIFY(person.getCurrentState() == Person::PersonState::MovingToAttack);
    int newX = 90;
    int newY = 110;
    person.move(newX, newY);
    QVERIFY(person.getCurrentState() == Person::PersonState::Moving);
}

void PersonTests::TestCase_Person_attack_OponnentNotInRange_Idle_To_MovingToAttack()
{
    TestStub_Person person;
    std::shared_ptr<Person> enemy(new Person);
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    std::unique_ptr<QQuickItem> enemyUiItem(new QQuickItem);

    const QPoint personPos(100, 100); //person position in global coordinates
    const QPoint enemyPos(100, 150);
    //person range depends on his size and the size of his currently held weapon
    const QSize personSize(10, 10);
    const QPoint personArmPosition(8, 8); // arm position in person coordinates system
    const QSize personArmSize(2, 4); //arm holding the weapon has a separate sprite which is subsprite of person Sprite
    const QSize weaponSize(2, 6);
    // in person's arm local coordinates system - its centered so that it fits evenly
    QPoint weaponPersonAnchor(static_cast<int>(personArmSize.width() / 2) -
                              static_cast<int>(weaponSize.width() / 2),
                              personArmSize.height());
    //transform it to person coordinates system
    weaponPersonAnchor.setX(weaponPersonAnchor.x() + personArmPosition.x());
    weaponPersonAnchor.setY(weaponPersonAnchor.y() + personArmPosition.y());

    std::unique_ptr<Weapon> weapon(new Weapon);
    weapon->setSize(weaponSize);
    person.addWeapon(weapon);

    //Crete primary weapon - normally would be done with Weapon support classes that load specs from config files and
    //based on that load a specific sprite with stats defined in weapon config file
    //Weapon id is determined by specific person config - every person object has a config file which stores the
    //weapon ids that this person owns. During equipment shopping in Camp new weapons are added to specific units,
    //among other equipment. For specified units types - roman hastati has specified config file that is his base and holds
    //info about his equipment - those ids that are used to find the coresponding config file for weapon or armor.
    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    enemyUiItem->setSize(personSize);
    enemyUiItem->setPosition(enemyPos);

    person.setUiItem(uiItem);
    enemy->setUiItem(enemyUiItem);
    person.tst_setWeaponAchorPoint(weaponPersonAnchor); // for tests set it manually
    //normally when weapon pulled out or changed the signal is sent to ui to change the sprite, then on sprite change
    //the anchor point is recalculated to correctly position the weapon(size change trigger).
    //then the anchor point is read using QQmlProperty::read when checkIfInWeaponRange() method is called

    //set person weapon , make it primary

    QObject::connect(&person, &Person::updatePersonMovementData, this,
                     &PersonTests::onUpdateMovementData);
    QObject::connect(this, &PersonTests::positionChanged, &person,
                     &Person::onPositionChanged);
    QVERIFY(person.getCurrentState() == Person::PersonState::Idle);
    person.attack(enemy);
    QVERIFY(person.getCurrentState() == Person::PersonState::MovingToAttack);
}

void PersonTests::TestCase_Person_attack_OponnentNotInRange_Moving_To_MovingToAttack()
{
    TestStub_Person person;
    std::shared_ptr<Person> enemy(new Person);
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    std::unique_ptr<QQuickItem> enemyUiItem(new QQuickItem);

    const QPoint personPos(100, 100); //person position in global coordinates
    const QPoint enemyPos(100, 150);
    //person range depends on his size and the size of his currently held weapon
    const QSize personSize(10, 10);
    const QPoint personArmPosition(8, 8); // arm position in person coordinates system
    const QSize personArmSize(2, 4); //arm holding the weapon has a separate sprite which is subsprite of person Sprite
    const QSize weaponSize(2, 6);
    // in person's arm local coordinates system - its centered so that it fits evenly
    QPoint weaponPersonAnchor(static_cast<int>(personArmSize.width() / 2) -
        static_cast<int>(weaponSize.width() / 2), personArmSize.height());
    //transform it to person coordinates system
    weaponPersonAnchor.setX(weaponPersonAnchor.x() + personArmPosition.x());
    weaponPersonAnchor.setY(weaponPersonAnchor.y() + personArmPosition.y());

    std::unique_ptr<Weapon> weapon(new Weapon);
    weapon->setSize(weaponSize);
    person.addWeapon(weapon);

    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    enemyUiItem->setSize(personSize);
    enemyUiItem->setPosition(enemyPos);

    person.setUiItem(uiItem);
    enemy->setUiItem(enemyUiItem);
    person.tst_setWeaponAchorPoint(weaponPersonAnchor);

    int newX = 90;
    int newY = 110;
    QObject::connect(&person, &Person::updatePersonMovementData, this,
                     &PersonTests::onUpdateMovementData);
    QObject::connect(this, &PersonTests::positionChanged, &person,
                     &Person::onPositionChanged);
    QVERIFY(person.getCurrentState() == Person::PersonState::Idle);
    person.move(newX + static_cast<int>(personSize.width() / 2), newY +
                static_cast<int>(personSize.height() / 2));
    QVERIFY(person.getCurrentState() == Person::PersonState::Moving);
    person.attack(enemy);
    QVERIFY(person.getCurrentState() == Person::PersonState::MovingToAttack);
}

void PersonTests::TestCase_Person_attack_OponnentInRange_Moving_To_Attacking()
{
    TestStub_Person person;
    std::shared_ptr<Person> enemy(new Person);
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    std::unique_ptr<QQuickItem> enemyUiItem(new QQuickItem);

    const QPoint personPos(100, 100); //person position in global coordinates

    //person range depends on his size and the size of his currently held weapon
    const QSize personSize(10, 10);
    const QPoint personArmPosition(8, 8); // arm position in person coordinates system
    const QSize personArmSize(2, 4); //arm holding the weapon has a separate sprite which is subsprite of person Sprite
    const QSize weaponSize(2, 6);
    // in person's arm local coordinates system - its centered so that it fits evenly
    QPoint weaponPersonAnchor(static_cast<int>(personArmSize.width() / 2) -
        static_cast<int>(weaponSize.width() / 2), personArmSize.height());
    //transform it to person coordinates system
    weaponPersonAnchor.setX(weaponPersonAnchor.x() + personArmPosition.x());
    weaponPersonAnchor.setY(weaponPersonAnchor.y() + personArmPosition.y());

    std::unique_ptr<Weapon> weapon(new Weapon);
    weapon->setSize(weaponSize);
    person.addWeapon(weapon);

    const QPoint enemyPos(personPos.x(), weaponPersonAnchor.y() +
                          weaponSize.height() + personPos.y());

    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    enemyUiItem->setSize(personSize);
    enemyUiItem->setPosition(enemyPos);

    person.setUiItem(uiItem);
    enemy->setUiItem(enemyUiItem);
    person.tst_setWeaponAchorPoint(weaponPersonAnchor);

    int newX = 90;
    int newY = 110;
    QObject::connect(&person, &Person::updatePersonMovementData, this,
                     &PersonTests::onUpdateMovementData);
    QObject::connect(this, &PersonTests::positionChanged, &person,
                     &Person::onPositionChanged);
    QVERIFY(person.getCurrentState() == Person::PersonState::Idle);
    person.move(newX + static_cast<int>(personSize.width() / 2), newY +
                static_cast<int>(personSize.height() / 2));
    QVERIFY(person.getCurrentState() == Person::PersonState::Moving);
    person.attack(enemy);
    QVERIFY(person.getCurrentState() == Person::PersonState::Attacking);
}

void PersonTests::TestCase_Person_attack_OponnentInRange_MovingToAttack_To_Attacking()
{
    TestStub_Person person;
    std::shared_ptr<Person> enemy(new Person);
    //Fake Ui Item
    std::unique_ptr<QQuickItem> uiItem(new QQuickItem);
    std::unique_ptr<QQuickItem> enemyUiItem(new QQuickItem);

    const QPoint personPos(100, 80); //person position in global coordinates

    //person range depends on his size and the size of his currently held weapon
    const QSize personSize(10, 10);
    const QPoint personArmPosition(8, 8); // arm position in person coordinates system
    const QSize personArmSize(2, 4); //arm holding the weapon has a separate sprite which is subsprite of person Sprite
    const QSize weaponSize(2, 6);
    // in person's arm local coordinates system - its centered so that it fits evenly
    //Weapon anchor is considered left botom corner of weapon ui item and its attached to
    //Top of person arm. Used in that way so in calculating if enemy is in range
    //of the weapon we use the anchor as 0,0 point of weapon coordinates system and increase
    // it to its height and width - top right corner of weapon to and transform in
    QPoint weaponPersonAnchor(static_cast<int>(personArmSize.width() / 2) -
                              static_cast<int>(weaponSize.width() / 2),
                              personArmSize.height());
    //transform it to person coordinates system
    weaponPersonAnchor.setX(weaponPersonAnchor.x() + personArmPosition.x());
    weaponPersonAnchor.setY(weaponPersonAnchor.y() + personArmPosition.y());

    std::unique_ptr<Weapon> weapon(new Weapon);
    weapon->setSize(weaponSize);
    person.addWeapon(weapon);

    const int yDiff = 20;
    const QPoint enemyPos(personPos.x(), weaponPersonAnchor.y() +
                          weaponSize.height() + personPos.y() + yDiff);

    uiItem->setSize(personSize);
    uiItem->setPosition(personPos);
    enemyUiItem->setSize(personSize);
    enemyUiItem->setPosition(enemyPos);

    person.setUiItem(uiItem);
    enemy->setUiItem(enemyUiItem);
    person.tst_setWeaponAchorPoint(weaponPersonAnchor);

    QObject::connect(&person, &Person::updatePersonMovementData,
                     this, &PersonTests::onUpdateMovementData);

    QObject::connect(this, &PersonTests::positionChanged, &person,
                     &Person::onPositionChanged);

    QVERIFY(person.getCurrentState() == Person::PersonState::Idle);
    person.attack(enemy);
    QVERIFY(person.getCurrentState() == Person::PersonState::MovingToAttack);
    //simulate moving a person to new position
    person.tst_setUiItemPosition(personPos + QPoint{0, yDiff});
    //send signal that person moved
    positionChanged(personPos.x(), personPos.y() + yDiff, 0);
    QVERIFY(person.getCurrentState() == Person::PersonState::Attacking);
}

void PersonTests::TestCase_Person_attack_OponnentInRange_Attacking_To_MovingToAttack()
{
    //this transitions occurs if enemy moved out of our attacking range -
    //disenaged or retreating. Unit will automaticly pursue enemy if
    //that was ordered or unit type is not disciplined
    std::shared_ptr<Person> defender(new TestStub_Person);
    std::shared_ptr<Person> attacker(new TestStub_Person);

    //Fake Ui Item
    std::unique_ptr<QQuickItem> defenderUiItem(new QQuickItem);
    std::unique_ptr<QQuickItem> attackerUiItem(new QQuickItem);

    const QPoint defenderPos(100, 110); //person position in global coordinates
    const QPoint attackerPos(100, 100);
    //person range depends on his size and the size of his currently held weapon
    const QSize personSize(10, 10);
    const QPoint personArmPosition(8, 8); // arm position in person coordinates system
    const QSize personArmSize(2, 4); //arm holding the weapon has a separate sprite which is subsprite of person Sprite
    const QSize weaponSize(2, 6);
    // in person's arm local coordinates system - its centered so that it fits evenly
    QPoint weaponPersonAnchor(static_cast<int>(personArmSize.width() / 2) -
                              static_cast<int>(weaponSize.width() / 2),
                              personArmSize.height());
    //transform it to person coordinates system
    weaponPersonAnchor.setX(weaponPersonAnchor.x() + personArmPosition.x());
    weaponPersonAnchor.setY(weaponPersonAnchor.y() + personArmPosition.y());

    std::unique_ptr<Weapon> attackerWeapon(new Weapon);
    std::unique_ptr<Weapon> defenderWeapon(new Weapon);

    attackerWeapon->setSize(weaponSize);
    attacker->addWeapon(attackerWeapon);
    defenderWeapon->setSize(weaponSize);
    defender->addWeapon(defenderWeapon);

    defenderUiItem->setSize(personSize);
    defenderUiItem->setPosition(defenderPos);
    attackerUiItem->setSize(personSize);
    attackerUiItem->setPosition(attackerPos);

    defender->setUiItem(defenderUiItem);
    attacker->setUiItem(attackerUiItem);
    //Set weapon achors for tests manually, normaly read from qml property
    static_cast<TestStub_Person*>(defender.get())->
        tst_setWeaponAchorPoint(weaponPersonAnchor);
    static_cast<TestStub_Person*>(attacker.get())->
        tst_setWeaponAchorPoint(weaponPersonAnchor);

    QSignalSpy attackedSpy(attacker.get(), &TestStub_Person::attackedEnemy);
    QSignalSpy defenderStateUpdateSpy(defender.get(),
                                      &TestStub_Person::personStateUpdate);

    //Initialize
    static_cast<TestStub_Person*>(attacker.get())->tst_setPersonState(
        Person::PersonState::MovingToAttack);
    static_cast<TestStub_Person*>(defender.get())->tst_setPersonState(
        Person::PersonState::Defending);

    //stub morale check - flee
    static_cast<TestStub_Person*>(defender.get())->tst_set_moraleCheck_UseStub(true);
    static_cast<TestStub_Person*>(defender.get())->tst_set_retreat_UseStub(true);
    static_cast<TestStub_Person*>(defender.get())->tst_set_moraleCheck_Return(false);

    attacker->attack(defender);

    QCOMPARE(attackedSpy.count(), 1u);
    QCOMPARE(defenderStateUpdateSpy.count(), 1u);
    QVERIFY(Person::PersonState::Retreating == defender->getCurrentState());
    QVERIFY(Person::PersonState::Attacking == attacker->getCurrentState());
    //this update would be called cyclicly for every unit in game in separate thread
    attacker->fightingUpdate();
    QVERIFY(Person::PersonState::MovingToAttack == attacker->getCurrentState());
}

//Attacked by enemy - slot onAttackedByEnemy() was called because
//of signal attackedEnemy() send by enemy
void PersonTests::TestCase_Person_onAttackedByEnemy_Idle_To_Defending()
{
    std::shared_ptr<Person> defender(new TestStub_Person);
    std::shared_ptr<Person> attacker(new TestStub_Person);

    //Fake Ui Item
    std::unique_ptr<QQuickItem> defenderUiItem(new QQuickItem);
    std::unique_ptr<QQuickItem> attackerUiItem(new QQuickItem);

    const QPoint defenderPos(100, 110); //person position in global coordinates
    const QPoint attackerPos(100, 100);
    //person range depends on his size and the size of his currently held weapon
    const QSize personSize(10, 10);
    const QPoint personArmPosition(8, 8); // arm position in person coordinates system
    const QSize personArmSize(2, 4); //arm holding the weapon has a separate sprite which is subsprite of person Sprite
    const QSize weaponSize(2, 6);
    // in person's arm local coordinates system - its centered so that it fits evenly
    QPoint weaponPersonAnchor(static_cast<int>(personArmSize.width() / 2) -
                              static_cast<int>(weaponSize.width() / 2),
                              personArmSize.height());
    //transform it to person coordinates system
    weaponPersonAnchor.setX(weaponPersonAnchor.x() + personArmPosition.x());
    weaponPersonAnchor.setY(weaponPersonAnchor.y() + personArmPosition.y());

    std::unique_ptr<Weapon> attackerWeapon(new Weapon);
    std::unique_ptr<Weapon> defenderWeapon(new Weapon);

    attackerWeapon->setSize(weaponSize);
    attacker->addWeapon(attackerWeapon);
    defenderWeapon->setSize(weaponSize);
    defender->addWeapon(defenderWeapon);

    defenderUiItem->setSize(personSize);
    defenderUiItem->setPosition(defenderPos);
    attackerUiItem->setSize(personSize);
    attackerUiItem->setPosition(attackerPos);

    defender->setUiItem(defenderUiItem);
    attacker->setUiItem(attackerUiItem);
    //Set weapon achors for tests manually, normaly read from qml property
    static_cast<TestStub_Person*>(defender.get())->
        tst_setWeaponAchorPoint(weaponPersonAnchor);
    static_cast<TestStub_Person*>(attacker.get())->
        tst_setWeaponAchorPoint(weaponPersonAnchor);

    QSignalSpy attackedSpy(attacker.get(), &TestStub_Person::attackedEnemy);
    QSignalSpy attackerStateUpdateSpy(attacker.get(),
                                      &TestStub_Person::personStateUpdate);
    QSignalSpy defenderStateUpdateSpy(defender.get(),
                                      &TestStub_Person::personStateUpdate);

    static_cast<TestStub_Person*>(attacker.get())->tst_setPersonState(
        Person::PersonState::MovingToAttack);
    static_cast<TestStub_Person*>(defender.get())->tst_setPersonState(
        Person::PersonState::Idle);

    //stub morale check - defended
    static_cast<TestStub_Person*>(defender.get())->tst_set_moraleCheck_UseStub(true);
    static_cast<TestStub_Person*>(defender.get())->tst_set_moraleCheck_Return(true);

    attacker->attack(defender);

    QCOMPARE(attackedSpy.count(), 1u);
    QCOMPARE(defenderStateUpdateSpy.count(), 1u);
    QCOMPARE(attackerStateUpdateSpy.count(), 1u);
    QVERIFY(Person::PersonState::Defending == defender->getCurrentState());
    QVERIFY(Person::PersonState::Attacking == attacker->getCurrentState());
}

void PersonTests::TestCase_Person_onAttackedByEnemy_Defending_To_Retreat()
{
    std::shared_ptr<Person> defender(new TestStub_Person);
    std::shared_ptr<Person> attacker(new TestStub_Person);

    //Fake Ui Item
    std::unique_ptr<QQuickItem> defenderUiItem(new QQuickItem);
    std::unique_ptr<QQuickItem> attackerUiItem(new QQuickItem);

    const QPoint defenderPos(100, 110); //person position in global coordinates
    const QPoint attackerPos(100, 100);
    //person range depends on his size and the size of his currently held weapon
    const QSize personSize(10, 10);
    const QPoint personArmPosition(8, 8); // arm position in person coordinates system
    const QSize personArmSize(2, 4); //arm holding the weapon has a separate sprite which is subsprite of person Sprite
    const QSize weaponSize(2, 6);
    // in person's arm local coordinates system - its centered so that it fits evenly
    QPoint weaponPersonAnchor(static_cast<int>(personArmSize.width() / 2) -
                              static_cast<int>(weaponSize.width() / 2),
                              personArmSize.height());
    //transform it to person coordinates system
    weaponPersonAnchor.setX(weaponPersonAnchor.x() + personArmPosition.x());
    weaponPersonAnchor.setY(weaponPersonAnchor.y() + personArmPosition.y());

    std::unique_ptr<Weapon> attackerWeapon(new Weapon);
    std::unique_ptr<Weapon> defenderWeapon(new Weapon);

    attackerWeapon->setSize(weaponSize);
    attacker->addWeapon(attackerWeapon);
    defenderWeapon->setSize(weaponSize);
    defender->addWeapon(defenderWeapon);

    defenderUiItem->setSize(personSize);
    defenderUiItem->setPosition(defenderPos);
    attackerUiItem->setSize(personSize);
    attackerUiItem->setPosition(attackerPos);

    defender->setUiItem(defenderUiItem);
    attacker->setUiItem(attackerUiItem);
    //Set weapon achors for tests manually, normaly read from qml property
    static_cast<TestStub_Person*>(defender.get())->
        tst_setWeaponAchorPoint(weaponPersonAnchor);
    static_cast<TestStub_Person*>(attacker.get())->
        tst_setWeaponAchorPoint(weaponPersonAnchor);

    QSignalSpy attackedSpy(attacker.get(), &TestStub_Person::attackedEnemy);
    QSignalSpy defenderStateUpdateSpy(defender.get(),
                                      &TestStub_Person::personStateUpdate);

    //Initialize
    static_cast<TestStub_Person*>(attacker.get())->tst_setPersonState(
        Person::PersonState::MovingToAttack);
    static_cast<TestStub_Person*>(defender.get())->tst_setPersonState(
        Person::PersonState::Defending);

    //stub morale check - flee
    static_cast<TestStub_Person*>(defender.get())->tst_set_moraleCheck_UseStub(true);
    static_cast<TestStub_Person*>(defender.get())->tst_set_moraleCheck_Return(false);

    attacker->attack(defender);

    QCOMPARE(attackedSpy.count(), 1u);
    QCOMPARE(defenderStateUpdateSpy.count(), 1u);
    QVERIFY(Person::PersonState::Retreating == defender->getCurrentState());
    QVERIFY(Person::PersonState::Attacking == attacker->getCurrentState());
}

void PersonTests::TestCase_Person_onAttackedByEnemy_Attacking_To_Retreat()
{
    std::shared_ptr<Person> attacker(new TestStub_Person);
    std::shared_ptr<Person> flanker(new TestStub_Person);

    //Fake Ui Item
    std::unique_ptr<QQuickItem> flankerUiItem(new QQuickItem);
    std::unique_ptr<QQuickItem> attackerUiItem(new QQuickItem);

    const QPoint flankerPos(100, 100); //person position in global coordinates
    const QPoint attackerPos(100, 110);
    //person range depends on his size and the size of his currently held weapon
    const QSize personSize(10, 10);
    const QPoint personArmPosition(8, 8); // arm position in person coordinates system
    const QSize personArmSize(2, 4); //arm holding the weapon has a separate sprite which is subsprite of person Sprite
    const QSize weaponSize(2, 6);
    // in person's arm local coordinates system - its centered so that it fits evenly
    QPoint weaponPersonAnchor(static_cast<int>(personArmSize.width() / 2) -
                              static_cast<int>(weaponSize.width() / 2),
                              personArmSize.height());
    //transform it to person coordinates system
    weaponPersonAnchor.setX(weaponPersonAnchor.x() + personArmPosition.x());
    weaponPersonAnchor.setY(weaponPersonAnchor.y() + personArmPosition.y());

    std::unique_ptr<Weapon> flankerWeapon(new Weapon);
    std::unique_ptr<Weapon> attackerWeapon(new Weapon);

    flankerWeapon->setSize(weaponSize);
    flanker->addWeapon(flankerWeapon);
    attackerWeapon->setSize(weaponSize);
    attacker->addWeapon(attackerWeapon);

    flankerUiItem->setSize(personSize);
    flankerUiItem->setPosition(flankerPos);
    attackerUiItem->setSize(personSize);
    attackerUiItem->setPosition(attackerPos);

    flanker->setUiItem(flankerUiItem);
    attacker->setUiItem(attackerUiItem);
    //Set weapon achors for tests manually, normaly read from qml property
    static_cast<TestStub_Person*>(flanker.get())->
        tst_setWeaponAchorPoint(weaponPersonAnchor);
    static_cast<TestStub_Person*>(attacker.get())->
        tst_setWeaponAchorPoint(weaponPersonAnchor);

    //Connect flanker to attacker
    QObject::connect(flanker.get(), &TestStub_Person::attackedEnemy,
                     attacker.get(), &TestStub_Person::onAttackedByEnemy);

    QSignalSpy attackedSpy(flanker.get(), &TestStub_Person::attackedEnemy);
    QSignalSpy attackerStateUpdateSpy(attacker.get(),
                                      &TestStub_Person::personStateUpdate);

    //Initialize
    static_cast<TestStub_Person*>(attacker.get())->tst_setPersonState(
        Person::PersonState::Attacking);
    static_cast<TestStub_Person*>(flanker.get())->tst_setPersonState(
        Person::PersonState::MovingToAttack);

    //stub morale check - flee
    static_cast<TestStub_Person*>(attacker.get())->tst_set_moraleCheck_UseStub(true);
    static_cast<TestStub_Person*>(attacker.get())->tst_set_moraleCheck_Return(false);

    flanker->attack(attacker);

    QCOMPARE(attackedSpy.count(), 1u);
    QCOMPARE(attackerStateUpdateSpy.count(), 1u);
    QVERIFY(Person::PersonState::Attacking == flanker->getCurrentState());
    QVERIFY(Person::PersonState::Retreating == attacker->getCurrentState());
}

void PersonTests::TestCase_Person_onAttackedByEnemy_Death()
{
    std::shared_ptr<Person> defender(new TestStub_Person);
    std::shared_ptr<Person> attacker(new TestStub_Person);

    //Fake Ui Item
    std::unique_ptr<QQuickItem> defenderUiItem(new QQuickItem);
    std::unique_ptr<QQuickItem> attackerUiItem(new QQuickItem);

    const QPoint defenderPos(100, 110); //person position in global coordinates
    const QPoint attackerPos(100, 100);
    //person range depends on his size and the size of his currently held weapon
    const QSize personSize(10, 10);
    const QPoint personArmPosition(8, 8); // arm position in person coordinates system
    const QSize personArmSize(2, 4); //arm holding the weapon has a separate sprite which is subsprite of person Sprite
    const QSize weaponSize(2, 6);
    // in person's arm local coordinates system - its centered so that it fits evenly
    QPoint weaponPersonAnchor(static_cast<int>(personArmSize.width() / 2) -
                              static_cast<int>(weaponSize.width() / 2),
                              personArmSize.height());
    //transform it to person coordinates system
    weaponPersonAnchor.setX(weaponPersonAnchor.x() + personArmPosition.x());
    weaponPersonAnchor.setY(weaponPersonAnchor.y() + personArmPosition.y());

    std::unique_ptr<Weapon> attackerWeapon(new Weapon);
    std::unique_ptr<Weapon> defenderWeapon(new Weapon);

    attackerWeapon->setSize(weaponSize);
    attacker->addWeapon(attackerWeapon);
    defenderWeapon->setSize(weaponSize);
    defender->addWeapon(defenderWeapon);

    defenderUiItem->setSize(personSize);
    defenderUiItem->setPosition(defenderPos);
    attackerUiItem->setSize(personSize);
    attackerUiItem->setPosition(attackerPos);

    defender->setUiItem(defenderUiItem);
    attacker->setUiItem(attackerUiItem);
    //Set weapon achors for tests manually, normaly read from qml property
    static_cast<TestStub_Person*>(defender.get())->
        tst_setWeaponAchorPoint(weaponPersonAnchor);
    static_cast<TestStub_Person*>(attacker.get())->
        tst_setWeaponAchorPoint(weaponPersonAnchor);

    QSignalSpy attackedSpy(attacker.get(), &TestStub_Person::attackedEnemy);
    QSignalSpy attackerStateUpdateSpy(attacker.get(),
                                      &TestStub_Person::personStateUpdate);
    QSignalSpy defenderStateUpdateSpy(defender.get(),
                                      &TestStub_Person::personStateUpdate);
    QSignalSpy defenderDiedSpy(defender.get(), &TestStub_Person::personDied);

    static_cast<TestStub_Person*>(attacker.get())->tst_setPersonState(
        Person::PersonState::MovingToAttack);
    static_cast<TestStub_Person*>(defender.get())->tst_setPersonState(
        Person::PersonState::Defending);

    //stub morale check - defended
    static_cast<TestStub_Person*>(defender.get())->tst_set_moraleCheck_UseStub(true);
    static_cast<TestStub_Person*>(defender.get())->tst_set_moraleCheck_Return(true);
    static_cast<TestStub_Person*>(defender.get())->tst_set_calculateDamageResults_UseStub(true);
    static_cast<TestStub_Person*>(defender.get())->tst_set_calculateDamageResults_Return(false);

    attacker->attack(defender);

    QCOMPARE(attackedSpy.count(), 1u);
    QCOMPARE(defenderStateUpdateSpy.count(), 1u);
    QCOMPARE(attackerStateUpdateSpy.count(), 1u);
    QCOMPARE(defenderDiedSpy.count(), 1u);
    QVERIFY(Person::PersonState::Dead == defender->getCurrentState());
    QVERIFY(Person::PersonState::Idle == attacker->getCurrentState());
}

//Write a separate qml app that tests the collision mechanisms, draw areas
// of every unit and show when clicked its coordinates system and view points
// additionally visuallize collision tests
//Interceptions during movement
void PersonTests::TestCase_Person_onAttackedByEnemy_FrontIntercept_Moving_To_Defending()
{
    std::shared_ptr<Person> defender(new TestStub_Person);
    std::shared_ptr<Person> attacker(new TestStub_Person);

    //Fake Ui Item
    std::unique_ptr<QQuickItem> defenderUiItem(new QQuickItem);
    std::unique_ptr<QQuickItem> attackerUiItem(new QQuickItem);

    const QSize personSize(10, 10);
    const QPointF defenderPos(100, 100); //person position in global coordinates
    qreal dx = -(personSize.width() / 2) - 4;
    qreal dy = personSize.height();
    const QPointF attackerPos = defenderPos + QPointF(dx, dy);
    //person range depends on his size and the size of his currently held weapon

    const QPointF personArmPosition(0.25 * personSize.width(), personSize.height() * 0.4); // arm position in person coordinates system
    const QSizeF personArmSize(0.1 * personSize.width(), 0.4 * personSize.height()); //arm holding the weapon has a separate sprite which is subsprite of person Sprite
    const QSizeF weaponSize(0.1 * personSize.width(), personSize.height());
    const qreal attackerRotation = 200.0;
    const qreal defenderRotation = 0.0;
    // in person's arm local coordinates system - its centered so that it fits evenly
    QPointF weaponPersonAnchor(static_cast<int>(personArmSize.width() / 2) -
                              static_cast<int>(weaponSize.width() / 2),
                              personArmSize.height());
    //transform it to person coordinates system
    weaponPersonAnchor.setX(weaponPersonAnchor.x() + personArmPosition.x());
    weaponPersonAnchor.setY(weaponPersonAnchor.y() + personArmPosition.y());

    std::unique_ptr<Weapon> attackerWeapon(new Weapon);
    std::unique_ptr<Weapon> defenderWeapon(new Weapon);

    attackerWeapon->setSize(weaponSize.toSize());
    attacker->addWeapon(attackerWeapon);
    defenderWeapon->setSize(weaponSize.toSize());
    defender->addWeapon(defenderWeapon);

    defenderUiItem->setSize(personSize);
    defenderUiItem->setPosition(defenderPos);
    defenderUiItem->setRotation(defenderRotation);
    attackerUiItem->setSize(personSize);
    attackerUiItem->setPosition(attackerPos);
    attackerUiItem->setRotation(attackerRotation);

    defender->setUiItem(defenderUiItem);
    attacker->setUiItem(attackerUiItem);
    //Set weapon achors for tests manually, normaly read from qml property
    static_cast<TestStub_Person*>(defender.get())->
        tst_setWeaponAchorPoint(weaponPersonAnchor.toPoint());
    static_cast<TestStub_Person*>(attacker.get())->
        tst_setWeaponAchorPoint(weaponPersonAnchor.toPoint());

    QObject::connect(static_cast<TestStub_Person*>(attacker.get()),
                     &TestStub_Person::attackedEnemy,
                     static_cast<TestStub_Person*>(attacker.get()),
                     &TestStub_Person::onSentAttackEnemy);

    QSignalSpy attackedSpy(attacker.get(), &TestStub_Person::attackedEnemy);
    QSignalSpy attackerStateUpdateSpy(attacker.get(),
                                      &TestStub_Person::personStateUpdate);
    QSignalSpy defenderStateUpdateSpy(defender.get(),
                                      &TestStub_Person::personStateUpdate);

    static_cast<TestStub_Person*>(attacker.get())->tst_setPersonState(
        Person::PersonState::MovingToAttack);
    static_cast<TestStub_Person*>(defender.get())->tst_setPersonState(
        Person::PersonState::Moving);

    //stub morale check - defended
    static_cast<TestStub_Person*>(defender.get())->tst_set_moraleCheck_UseStub(true);
    static_cast<TestStub_Person*>(defender.get())->tst_set_moraleCheck_Return(true);
    static_cast<TestStub_Person*>(attacker.get())->tst_set_checkIfEnemyInWeaponRange_UseStub(true);

    attacker->attack(defender);

    QCOMPARE(attackedSpy.count(), 1u);
    QCOMPARE(defenderStateUpdateSpy.count(), 1u);
    QCOMPARE(attackerStateUpdateSpy.count(), 1u);
    QVERIFY(Person::PersonState::Defending == defender->getCurrentState());
    QVERIFY(Person::PersonState::Attacking == attacker->getCurrentState());
    QCOMPARE(static_cast<TestStub_Person*>(attacker.get())->
        tst_get_sentAttack_Orienation(), Person::AttackOrientation::Frontal);
}

void PersonTests::TestCase_Person_onAttackedByEnemy_FlankIntercept_Moving_To_Defending()
{
    std::shared_ptr<Person> defender(new TestStub_Person);
    std::shared_ptr<Person> attacker(new TestStub_Person);

    //Fake Ui Item
    std::unique_ptr<QQuickItem> defenderUiItem(new QQuickItem);
    std::unique_ptr<QQuickItem> attackerUiItem(new QQuickItem);

    const QSize personSize(10, 10);
    const QPointF defenderPos(100, 100); //person position in global coordinates
    qreal dx = -(personSize.width() / 2) - 5;
    qreal dy = -(personSize.height() / 2) - 2;
    const QPointF attackerPos = defenderPos + QPointF(dx, dy);
    //person range depends on his size and the size of his currently held weapon

    const QPointF personArmPosition(0.25 * personSize.width(), personSize.height() * 0.4); // arm position in person coordinates system
    const QSizeF personArmSize(0.1 * personSize.width(), 0.4 * personSize.height()); //arm holding the weapon has a separate sprite which is subsprite of person Sprite
    const QSizeF weaponSize(0.1 * personSize.width(), 0.7 * personSize.height());
    const qreal attackerRotation = -45.0;
    const qreal defenderRotation = 0.0;
    // in person's arm local coordinates system - its centered so that it fits evenly
    QPointF weaponPersonAnchor(static_cast<int>(personArmSize.width() / 2) -
                              static_cast<int>(weaponSize.width() / 2),
                              personArmSize.height());
    //transform it to person coordinates system
    weaponPersonAnchor.setX(weaponPersonAnchor.x() + personArmPosition.x());
    weaponPersonAnchor.setY(weaponPersonAnchor.y() + personArmPosition.y());

    std::unique_ptr<Weapon> attackerWeapon(new Weapon);
    std::unique_ptr<Weapon> defenderWeapon(new Weapon);

    attackerWeapon->setSize(weaponSize.toSize());
    attacker->addWeapon(attackerWeapon);
    defenderWeapon->setSize(weaponSize.toSize());
    defender->addWeapon(defenderWeapon);

    defenderUiItem->setSize(personSize);
    defenderUiItem->setPosition(defenderPos);
    defenderUiItem->setRotation(defenderRotation);
    attackerUiItem->setSize(personSize);
    attackerUiItem->setPosition(attackerPos);
    attackerUiItem->setRotation(attackerRotation);

    defender->setUiItem(defenderUiItem);
    attacker->setUiItem(attackerUiItem);

    //Set weapon achors for tests manually, normaly read from qml property
    static_cast<TestStub_Person*>(defender.get())->
        tst_setWeaponAchorPoint(weaponPersonAnchor.toPoint());
    static_cast<TestStub_Person*>(attacker.get())->
        tst_setWeaponAchorPoint(weaponPersonAnchor.toPoint());

    QObject::connect(static_cast<TestStub_Person*>(attacker.get()),
                     &TestStub_Person::attackedEnemy,
                     static_cast<TestStub_Person*>(attacker.get()),
                     &TestStub_Person::onSentAttackEnemy);

    QSignalSpy attackedSpy(attacker.get(), &TestStub_Person::attackedEnemy);
    QSignalSpy attackerStateUpdateSpy(attacker.get(),
                                      &TestStub_Person::personStateUpdate);
    QSignalSpy defenderStateUpdateSpy(defender.get(),
                                      &TestStub_Person::personStateUpdate);

    static_cast<TestStub_Person*>(attacker.get())->tst_setPersonState(
        Person::PersonState::MovingToAttack);
    static_cast<TestStub_Person*>(defender.get())->tst_setPersonState(
        Person::PersonState::Moving);

    //stub morale check - defended
    static_cast<TestStub_Person*>(defender.get())->tst_set_moraleCheck_UseStub(true);
    static_cast<TestStub_Person*>(defender.get())->tst_set_moraleCheck_Return(true);
    static_cast<TestStub_Person*>(attacker.get())->tst_set_checkIfEnemyInWeaponRange_UseStub(true);

    attacker->attack(defender);

    QCOMPARE(attackedSpy.count(), 1u);
    QCOMPARE(defenderStateUpdateSpy.count(), 1u);
    QCOMPARE(attackerStateUpdateSpy.count(), 1u);
    QVERIFY(Person::PersonState::Defending == defender->getCurrentState());
    QVERIFY(Person::PersonState::Attacking == attacker->getCurrentState());
    QCOMPARE(static_cast<TestStub_Person*>(attacker.get())->
        tst_get_sentAttack_Orienation(), Person::AttackOrientation::Flank);
}

void PersonTests::TestCase_Person_onAttackedByEnemy_RearIntercept_Moving_To_Defending()
{
    std::shared_ptr<Person> defender(new TestStub_Person);
    std::shared_ptr<Person> attacker(new TestStub_Person);

    //Fake Ui Item
    std::unique_ptr<QQuickItem> defenderUiItem(new QQuickItem);
    std::unique_ptr<QQuickItem> attackerUiItem(new QQuickItem);

    const QSize personSize(10, 10);
    const QPointF defenderPos(100, 100); //person position in global coordinates
    qreal dx = personSize.width();
    qreal dy = -personSize.height();
    const QPointF attackerPos = defenderPos + QPointF(dx, dy);
    //person range depends on his size and the size of his currently held weapon

    const QPointF personArmPosition(0.25 * personSize.width(), personSize.height() * 0.4); // arm position in person coordinates system
    const QSizeF personArmSize(0.1 * personSize.width(), 0.4 * personSize.height()); //arm holding the weapon has a separate sprite which is subsprite of person Sprite
    const QSizeF weaponSize(0.1 * personSize.width(), personSize.height());
    const qreal attackerRotation = 45.0;
    const qreal defenderRotation = 0.0;
    // in person's arm local coordinates system - its centered so that it fits evenly
    QPointF weaponPersonAnchor(static_cast<int>(personArmSize.width() / 2) -
                              static_cast<int>(weaponSize.width() / 2),
                              personArmSize.height());
    //transform it to person coordinates system
    weaponPersonAnchor.setX(weaponPersonAnchor.x() + personArmPosition.x());
    weaponPersonAnchor.setY(weaponPersonAnchor.y() + personArmPosition.y());

    std::unique_ptr<Weapon> attackerWeapon(new Weapon);
    std::unique_ptr<Weapon> defenderWeapon(new Weapon);

    attackerWeapon->setSize(weaponSize.toSize());
    attacker->addWeapon(attackerWeapon);
    defenderWeapon->setSize(weaponSize.toSize());
    defender->addWeapon(defenderWeapon);

    defenderUiItem->setSize(personSize);
    defenderUiItem->setPosition(defenderPos);
    defenderUiItem->setRotation(defenderRotation);
    attackerUiItem->setSize(personSize);
    attackerUiItem->setPosition(attackerPos);
    attackerUiItem->setRotation(attackerRotation);

    defender->setUiItem(defenderUiItem);
    attacker->setUiItem(attackerUiItem);

    //Set weapon achors for tests manually, normaly read from qml property
    static_cast<TestStub_Person*>(defender.get())->
        tst_setWeaponAchorPoint(weaponPersonAnchor.toPoint());
    static_cast<TestStub_Person*>(attacker.get())->
        tst_setWeaponAchorPoint(weaponPersonAnchor.toPoint());

    QObject::connect(static_cast<TestStub_Person*>(attacker.get()),
                     &TestStub_Person::attackedEnemy,
                     static_cast<TestStub_Person*>(attacker.get()),
                     &TestStub_Person::onSentAttackEnemy);

    QSignalSpy attackedSpy(attacker.get(), &TestStub_Person::attackedEnemy);
    QSignalSpy attackerStateUpdateSpy(attacker.get(),
                                      &TestStub_Person::personStateUpdate);
    QSignalSpy defenderStateUpdateSpy(defender.get(),
                                      &TestStub_Person::personStateUpdate);

    static_cast<TestStub_Person*>(attacker.get())->tst_setPersonState(
        Person::PersonState::MovingToAttack);
    static_cast<TestStub_Person*>(defender.get())->tst_setPersonState(
        Person::PersonState::Moving);

    //stub morale check - defended
    static_cast<TestStub_Person*>(defender.get())->tst_set_moraleCheck_UseStub(true);
    static_cast<TestStub_Person*>(defender.get())->tst_set_moraleCheck_Return(true);
    static_cast<TestStub_Person*>(attacker.get())->tst_set_checkIfEnemyInWeaponRange_UseStub(true);

    attacker->attack(defender);

    QCOMPARE(attackedSpy.count(), 1u);
    QCOMPARE(defenderStateUpdateSpy.count(), 1u);
    QCOMPARE(attackerStateUpdateSpy.count(), 1u);
    QVERIFY(Person::PersonState::Defending == defender->getCurrentState());
    QVERIFY(Person::PersonState::Attacking == attacker->getCurrentState());
    QCOMPARE(static_cast<TestStub_Person*>(attacker.get())->
        tst_get_sentAttack_Orienation(), Person::AttackOrientation::Rear);
}

void PersonTests::TestCase_Person_defender_calculateDamageResults_Frontal_Melee_Attack()
{

}

void PersonTests::TestCase_Person_defender_calculateDamageResults_Flanking_Melee_Attack()
{

}

void PersonTests::TestCase_Person_defender_calculateDamageResults_Rear_Melee_Attack()
{

}

void PersonTests::TestCase_Person_defender_calculateDamageResults_Frontal_Ranged_Attack()
{

}

void PersonTests::TestCase_Person_defender_calculateDamageResults_Flanking_Ranged_Attack()
{

}

void PersonTests::TestCase_Person_defender_calculateDamageResults_Rear_Ranged_Attack()
{

}

void PersonTests::TestCase_Person_attacker_calculateAttackDamage_Frontal_Attack()
{

}

void PersonTests::TestCase_Person_attacker_calculateAttackDamage_Flanking_Attack()
{

}

void PersonTests::TestCase_Person_attacker_calculateAttackDamage_Rear_Attack()
{

}

void PersonTests::TestCase_Person_onAttackedByEnemy_Flanked_During_Attack()
{

}

void PersonTests::TestCase_Person_onAttackedByEnemy_Reared_During_Attack()
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
