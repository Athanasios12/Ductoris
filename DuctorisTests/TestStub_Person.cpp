#include "TestStub_Person.h"

void TestStub_Person::tst_setWeaponAchorPoint(const QPoint &position)
{
    m_weaponAnchorPoint = position;
}

void TestStub_Person::tst_setUiItemPosition(const QPoint &pos)
{
    if (m_uiItem)
    {
        m_uiItem->setPosition(pos);
    }
}

void TestStub_Person::tst_setPersonState(const Person::PersonState state)
{
    m_currentState = state;
}

bool TestStub_Person::checkIfEnemyInWeaponRange(const QQuickItem *enemyUiItem)
{
    if (m_uiItem && enemyUiItem)
    {
        if (!m_weapons.empty())
        {
            auto &currentWeapon = m_weapons[m_currentWeaponIdx];
            if (currentWeapon)
            {
                int weaponWidth = currentWeapon->getSize().width();
                int weaponHeight = currentWeapon->getSize().height();
                //Weapon achor point is its bottom left corner and
                //its position is in person coordinates system
                //Normally the anchor is read from QML property
                //for testing this is set manually with "setWeaponAchorPoint"
                const int x0 = m_weaponAnchorPoint.x();
                const int y0 = m_weaponAnchorPoint.y();
                for(int x_weapon = x0; x_weapon <= weaponWidth + x0; x_weapon++)
                {
                    for(int y_weapon = y0; y_weapon <= weaponHeight + y0; y_weapon++)
                    {
                        auto weaponPosInEnemyCoords = m_uiItem->
                            mapToItem(
                                enemyUiItem,
                                QPoint{x_weapon, y_weapon}).toPoint();
                        if (enemyUiItem->contains(weaponPosInEnemyCoords))
                        {
                            return true;
                        }
                    }
                }
            }
        }
    }
    return false;
}
