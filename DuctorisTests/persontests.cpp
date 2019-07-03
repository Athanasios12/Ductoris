#include "persontests.h"
#include "Person.h"
#include <QQmlProperty>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlComponent>
#include <QQmlApplicationEngine>

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

//Movement Test Cases
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
    QObject::connect(&person, SIGNAL(updatePersonMovementData(QVariant, QVariant, QVariant, QVariant)),
                     this, SLOT(onUpdateMovementData(QVariant, QVariant, QVariant, QVariant)));
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
    QObject::connect(&person, SIGNAL(updatePersonMovementData(QVariant, QVariant, QVariant, QVariant)),
                     this, SLOT(onUpdateMovementData(QVariant, QVariant, QVariant, QVariant)));
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
    QObject::connect(&person, SIGNAL(updatePersonMovementData(QVariant, QVariant, QVariant, QVariant)),
                     this, SLOT(onUpdateMovementData(QVariant, QVariant, QVariant, QVariant)));
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
    QObject::connect(&person, SIGNAL(updatePersonMovementData(QVariant, QVariant, QVariant, QVariant)),
                     this, SLOT(onUpdateMovementData(QVariant, QVariant, QVariant, QVariant)));
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
    QObject::connect(&person, SIGNAL(updatePersonMovementData(QVariant, QVariant, QVariant, QVariant)),
                     this, SLOT(onUpdateMovementData(QVariant, QVariant, QVariant, QVariant)));
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
    QObject::connect(&person, SIGNAL(updatePersonMovementData(QVariant, QVariant, QVariant, QVariant)),
                     this, SLOT(onUpdateMovementData(QVariant, QVariant, QVariant, QVariant)));
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
    QObject::connect(&person, SIGNAL(updatePersonMovementData(QVariant, QVariant, QVariant, QVariant)),
                     this, SLOT(onUpdateMovementData(QVariant, QVariant, QVariant, QVariant)));
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
    QObject::connect(&person, SIGNAL(updatePersonMovementData(QVariant, QVariant, QVariant, QVariant)),
                     this, SLOT(onUpdateMovementData(QVariant, QVariant, QVariant, QVariant)));
    person.move(newX + static_cast<int>(personSize.width() / 2), newY + static_cast<int>(personSize.height() / 2));

    QVERIFY(person.isConnectedToUi());
    QVERIFY(newX == _newPos.x());
    QVERIFY(newY == _newPos.y());
    QVERIFY((_newRotation >= newRotation - rotationTolerance) && (_newRotation <= newRotation + rotationTolerance));
}

//Weapon Test cases
void PersonTests::TestCase_Person_onWeaponChange_ChangeToMeleeWeapon()
{

}

void PersonTests::TestCase_Person_onWeaponChange_ChangeToRangedWeapon()
{

}

//Attack Test Cases
void PersonTests::TestCase_Person_onAttackPressed_NoOpponentInRange()
{

}

void PersonTests::TestCase_Person_onAttackPressed_OpponentInRange()
{

}

//Exp Tests
void PersonTests::TestCase_Person_addExp_EnemyKilled_NoLevelUp()
{

}

void PersonTests::TestCase_Person_addExp_EnemyKilled_LevelUp()
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
