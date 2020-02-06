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

void TestStub_Person::tst_set_moraleCheck_Return(bool moraleCheckReturn)
{
    m_tst_moraleCheck_ReturnVal = moraleCheckReturn;
}

void TestStub_Person::tst_set_calculateDamageResults_Return(
    bool calculateDamageResultsReturn)
{
    m_tst_calculateDamageResults_ReturnVal = calculateDamageResultsReturn;
}

void TestStub_Person::tst_set_calculateAttackDamage_Return(uint16_t calculateDamageResultsReturn)
{
    m_tst_calculateAttackDamage_ReturnVal = calculateDamageResultsReturn;
}

void TestStub_Person::tst_set_getAttackOrientation_Return(Person::AttackOrientation attackOrientationReturn)
{
    m_tst_getAttackOrientation_ReturnVal = attackOrientationReturn;
}

void TestStub_Person::tst_set_moraleCheck_UseStub(bool useStub)
{
    m_tst_useStub_moraleCheck = useStub;
}

void TestStub_Person::tst_set_calculateDamageResults_UseStub(bool useStub)
{
    m_tst_useStub_calculateDamageResults = useStub;
}

void TestStub_Person::tst_set_calculateAttackDamage_UseStub(bool useStub)
{
    m_tst_useStub_calculateDamageResults = useStub;
}

void TestStub_Person::tst_set_getAttackOrientation_UseStub(bool useStub)
{
    m_tst_useStub_getAttackOrientation = useStub;
}

void TestStub_Person::tst_set_retreat_UseStub(bool useStub)
{
    m_tst_useStub_retreat = useStub;
}

bool TestStub_Person::moraleCheck() const
{
    if (m_tst_useStub_moraleCheck)
    {
        return m_tst_moraleCheck_ReturnVal;
    }
    else
    {
        return Person::moraleCheck();
    }
}

bool TestStub_Person::calculateDamageResults(quint16 damage,
                                             Person::AttackOrientation orientation,
                                             Weapon::WeaponType weaponType)
{
    if (m_tst_useStub_calculateDamageResults)
    {
        return m_tst_calculateDamageResults_ReturnVal;
    }
    else
    {
        return Person::calculateDamageResults(damage, orientation, weaponType);
    }
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
                auto weaponPosInEnemyCoords = m_uiItem->
                    mapToItem(
                        enemyUiItem,
                        QPoint{0, 0}).toPoint();
                fprintf(stderr, "\nx: %d, y: %d\n", weaponPosInEnemyCoords.x(), weaponPosInEnemyCoords.y());
            }
        }
    }
    return false;
}

Person::AttackOrientation TestStub_Person::tst_get_sentAttack_Orienation() const
{
    return m_tst_sentAttack_Orientation;
}

quint16 TestStub_Person::tst_get_sentAttack_Damage() const
{
    return m_tst_sentAttack_Damage;
}

void TestStub_Person::onSentAttackEnemy(quint32 person_id, quint16 damage,
                                        Person::AttackOrientation orientation,
                                        Weapon::WeaponType weaponType)
{
    m_tst_sentAttack_Damage = damage;
    m_tst_sentAttack_Orientation = orientation;
}

quint16 TestStub_Person::calculateAttackDamage() const
{
    if (m_tst_useStub_calculateAttackDamage)
    {
        return m_tst_calculateAttackDamage_ReturnVal;
    }
    else
    {
        return Person::calculateAttackDamage();
    }
}

Person::AttackOrientation TestStub_Person::getAttackOrientation() const
{
    if (m_tst_useStub_getAttackOrientation)
    {
        return m_tst_getAttackOrientation_ReturnVal;
    }
    return Person::getAttackOrientation();
}

void TestStub_Person::retreat()
{
    if (m_tst_useStub_retreat)
    {
        //move the unit to go out of attack range
        if (m_uiItem)
        {
            m_uiItem->setPosition(m_uiItem->position() * 2);
        }
    }
    else
    {
        Person::retreat();
    }
}
