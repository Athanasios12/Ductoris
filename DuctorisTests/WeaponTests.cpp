#include "WeaponTests.h"
#include "weapon.h"

void WeaponTests::TestCase_Weapon_DeafultContructor()
{

}

void WeaponTests::TestCase_Weapon_setUiItem_isNullPtr()
{
    std::unique_ptr<QQuickItem> weaponUiItem(nullptr);
    Weapon weapon;
    QVERIFY(!weapon.setUiItem(weaponUiItem));
}

void WeaponTests::TestCase_Weapon_setUiItem_Valid()
{
    QPoint weaponPos{120, 151};
    QSize weaponSize{5, 5};
    qreal weaponRotation = 180;

    std::unique_ptr<QQuickItem> weaponUiItem(new QQuickItem);
    weaponUiItem->setPosition(weaponPos);
    weaponUiItem->setSize(weaponSize);
    weaponUiItem->setTransformOrigin(QQuickItem::Center);
    weaponUiItem->setRotation(weaponRotation);

    Weapon weapon;
    QVERIFY(weapon.setUiItem(weaponUiItem));
}

void WeaponTests::TestCase_Weapon_checkIfOpponentInrange_InRange()
{
    QPoint enemyPos{100, 100};
    QSize enemySize{50, 50};
    qreal enemyRotation = 0;

    std::unique_ptr<QQuickItem> enemyUiItem(new QQuickItem);
    enemyUiItem->setPosition(enemyPos);
    enemyUiItem->setSize(enemySize);
    enemyUiItem->setRotation(enemyRotation);

    QPoint weaponPos{120, 151};
    QSize weaponSize{5, 5};
    qreal weaponRotation = 180;

    std::unique_ptr<QQuickItem> weaponUiItem(new QQuickItem);
    weaponUiItem->setPosition(weaponPos);
    weaponUiItem->setSize(weaponSize);
    weaponUiItem->setTransformOrigin(QQuickItem::Center);
    weaponUiItem->setRotation(weaponRotation);

    Weapon weapon;
    weapon.setUiItem(weaponUiItem);
    bool inRange = weapon.checkIfEnemyInWeaponRange(enemyUiItem.get());
    QVERIFY(!inRange);
}

void WeaponTests::TestCase_Weapon_checkIfOpponentInrange_OutOfRange()
{
    QPoint enemyPos{100, 100};
    QSize enemySize{50, 50};
    qreal enemyRotation = 0;

    std::unique_ptr<QQuickItem> enemyUiItem(new QQuickItem);
    enemyUiItem->setPosition(enemyPos);
    enemyUiItem->setSize(enemySize);
    enemyUiItem->setRotation(enemyRotation);

    QPoint weaponPos{120, 151};
    QSize weaponSize{5, 5};
    qreal weaponRotation = 180;

    std::unique_ptr<QQuickItem> weaponUiItem(new QQuickItem);
    weaponUiItem->setPosition(weaponPos);
    weaponUiItem->setSize(weaponSize);
    weaponUiItem->setTransformOrigin(QQuickItem::TopLeft);
    weaponUiItem->setRotation(weaponRotation);

    Weapon weapon;
    weapon.setUiItem(weaponUiItem);
    bool inRange = weapon.checkIfEnemyInWeaponRange(enemyUiItem.get());
    QVERIFY(inRange);
}
