#include "Person.h"
#include "armyfactory.h"
#include <algorithm>
#include <cstdlib>
#include <QQmlProperty>
#include <cmath>

Person::Person()
{

}

Person::Person(const Person &other):
    m_type(other.m_type),
    m_stats(other.m_stats),
    m_exp(other.m_exp),
    m_level(other.m_level),
    m_armor(other.m_armor)
{
    //add m_skillTree copying - skillTree factory or skill tree builder
    for(auto && weapon : other.m_weapons)
    {
        if (weapon)
        {
            std::unique_ptr<Weapon> weaponCopy(new Weapon(*(weapon.get())));
            m_weapons.push_back(std::move(weaponCopy));
        }
    }
}

Person &Person::operator=(const Person &other)
{
    if (this != &other)
    {
        m_type = other.m_type;
        m_stats = other.m_stats;
        m_exp = other.m_exp;
        m_level = other.m_level;
        m_armor = other.m_armor;
        for(auto && weapon : other.m_weapons)
        {
            if (weapon)
            {
                std::unique_ptr<Weapon> weaponCopy(new Weapon(*(weapon.get())));
                m_weapons.push_back(std::move(weaponCopy));
            }
        }
    }
    return *this;
}

Person::Person(Person &&other):
    m_type(other.m_type),
    m_stats(other.m_stats),
    m_exp(other.m_exp),
    m_level(other.m_level)
{
    other.m_stats = Stats();
    other.m_exp = 0;
    other.m_level = 0;
    m_armor = std::move(other.m_armor);
    m_weapons = std::move(other.m_weapons);
}

Person &Person::operator=(Person &&other)
{
    if (this != &other)
    {
        m_type = other.m_type;
        m_stats = other.m_stats;
        m_exp = other.m_exp;
        m_level = other.m_level;
        other.m_stats = Stats();
        other.m_exp = 0;
        other.m_level = 0;
        m_armor = std::move(other.m_armor);
        m_weapons = std::move(other.m_weapons);
    }
    return *this;
}

Person::~Person()
{

}

bool Person::setUiItem(std::unique_ptr<QQuickItem> &uiItem)
{
    bool uiSet = false;
    if (uiItem)
    {
        m_uiItem = std::move(uiItem);
        //connect to signals and slots of ui component
        connect(this, SIGNAL(updatePersonMovementData(QVariant, QVariant, QVariant, QVariant)),
                m_uiItem.get(), SLOT(onUpdateMovementData(QVariant, QVariant, QVariant, QVariant)));
        connect(this, SIGNAL(updatePersonMovementStats(QVariant,QVariant)), m_uiItem.get(),
                SLOT(onUpdateMovementStats(QVariant, QVariant)));
        connect(m_uiItem.get(), SIGNAL(positionChanged(int, int, int)), this,
                SLOT(onPositionChanged(int,int,int)));
        //get uiItem weapon anchor point
        m_weaponAnchorPoint = QQmlProperty::read(m_uiItem.get(), "PrimaryWeaponAnchorPoint").toPoint();
        m_connectedToUi = true;
        uiSet = true;
    }
    return uiSet;
}

QPoint Person::getPosition() const
{
    QPoint pos(0, 0);
    if (m_uiItem)
    {
        pos = m_uiItem->position().toPoint();
    }
    return pos;
}

quint16 Person::getWidth() const
{
    quint16 width = 0;
    if (m_uiItem)
    {
        width = static_cast<quint16>(m_uiItem->width());
    }
    return width;
}

quint16 Person::getHeight() const
{
    quint16 height = 0;
    if (m_uiItem)
    {
        height = static_cast<quint16>(m_uiItem->height());
    }
    return height;
}

int Person::getRotation() const
{
    quint16 rotation = 0;
    if (m_uiItem)
    {
        rotation = static_cast<quint16>(m_uiItem->rotation());
    }
    return rotation;
}

uint32_t Person::getExp() const
{
    return m_exp;
}

uint8_t Person::getLevel() const
{
    return m_level;
}

Person::PersonState Person::getCurrentState() const
{
    return m_currentState;
}

DuctorisTypes::ArmyType Person::getPersonArmyType() const
{
    return m_type;
}

bool Person::isConnectedToUi() const
{
    return m_connectedToUi;
}

bool Person::addExp(uint16_t exp)
{
    bool levelUp = false;
    //later on add perk check for
    if (m_skillTree)
    {
        if (m_level < m_skillTree->getMaxLevel())
        {
            m_exp += exp;
            if (m_skillTree->checkIfThresholdReached(m_exp))
            {
                m_stats.addBonus(m_skillTree->getLevelBonus(++m_level));
                levelUp = true;
            }
        }
    }
    return levelUp;
}

void Person::changeArmor(Armor &armor)
{
    m_armor = std::move(armor);
}

void Person::addWeapon(std::unique_ptr<Weapon> &weapon)
{
    m_weapons.push_back(std::move(weapon));
}

void Person::move(int newX, int newY)
{
    if (m_uiItem && m_connectedToUi)
    {
        auto x = m_uiItem->position().toPoint().x();
        auto y = m_uiItem->position().toPoint().y();

        //get this  - person width and height from the property of ui qmlItem
        newX = newX - static_cast<int>(m_uiItem->width() / 2);
        newY = newY - static_cast<int>(m_uiItem->height() / 2);

        //replace with person member items
        auto time = static_cast<int>(sqrt(pow(abs(newX - x), 2)
            + pow(abs(newY - y), 2)) * m_stats.m_speed);
        //rotation calculation
        auto X_g = static_cast<double>(newX - x); //X in global coordinates
        auto Y_g = static_cast<double>(newY - y); //Y in global coordinates
        //transform to person coordinate system orientation
        //custom rotation angle calculation for coordinates system with
        // o------> x
        // '
        // '
        // v y
        auto Phi = static_cast<double>(m_uiItem->rotation());
        auto X_p = ((X_g * cos((Phi / 180) * M_PI)) + (Y_g * sin((Phi / 180) * M_PI))); //x in local coordinates
        auto Y_p = ((-X_g * sin((Phi / 180) * M_PI)) + (Y_g * cos((Phi / 180) * M_PI))); //y in local coordinates

        int rotationAngle = 0;
        if (X_p >= 0)
        {
            rotationAngle = static_cast<int>(180 - ((atan2(X_p, Y_p) * 180) / M_PI));
        }
        else
        {
            rotationAngle = static_cast<int>(-180 - ((atan2(X_p, Y_p) * 180) / M_PI));
        }
        //signal data change
        m_destination.setX(newX);
        m_destination.setY(newY);
        m_currentState = PersonState::Moving;
        updatePersonMovementData(newX, newY, time, rotationAngle);
    }
}

void Person::attack(std::shared_ptr<Person> &enemyUnit)
{
    if (m_connectedToUi)
    {
        bool newEnemyValid = false;
        if (m_lockedOnEnemy.use_count() == 0)
        {
            newEnemyValid = true;
        }
        else
        {
            if (enemyUnit.get() != m_lockedOnEnemy.lock().get())
            {
                newEnemyValid = true;
            }
        }
        if (newEnemyValid)
        {
            if (m_currentState != PersonState::Attacking &&
                m_currentState != PersonState::Defending &&
                m_currentState != PersonState::Retreating)
            {
                m_lockedOnEnemy = enemyUnit;
                if (checkIfEnemyInWeaponRange(enemyUnit->m_uiItem.get()))
                {
                    m_currentState = PersonState::Attacking;
                    //do attacking stuff - damage, animation and so on
                }
                else
                {
                    move(enemyUnit->getPosition().x(), enemyUnit->getPosition().y());
                    m_currentState = PersonState::MovingToAttack;                    
                    //do moving towards the enemy, and check every position update if he didnt move and call move again
                }
            }
        }
    }
}

//added melee weapon handling, add the ranged also
//add rotating weapon sprite with the person sprite, along person center
bool Person::checkIfEnemyInWeaponRange(const QQuickItem *enemyUiItem)
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
                QPointF weaponAnchorGlobal = QQmlProperty::read(
                            qobject_cast<QObject*>(m_uiItem.get()),
                            "PrimaryWeaponAnchorPoint").toPointF();
                m_weaponAnchorPoint = weaponAnchorGlobal.toPoint();
                //Assume that anchor is in weapon coordinates system
                //otherwise transform it to weapon - orientation has
                // such that increasing x and y is in weapon coordinates system
                QPoint weaponAchorLocal = m_uiItem->mapFromGlobal(
                                          weaponAnchorGlobal).toPoint();
                for(int x_weapon = weaponAchorLocal.x();
                    x_weapon <= weaponWidth + weaponAchorLocal.x(); x_weapon++)
                {
                    for(int y_weapon = weaponAchorLocal.y();
                        y_weapon <= weaponHeight + weaponAchorLocal.y(); y_weapon++)
                    {
                        auto weaponPosInEnemyCoords = m_uiItem->mapToItem(
                            enemyUiItem, QPoint{x_weapon, y_weapon}).toPoint();
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

void Person::onPositionChanged(int x, int y, int rotation)
{
    switch(m_currentState)
    {
    case Idle:
        break;
    case Moving:
        if (x == m_destination.x() && y == m_destination.y())
        {
            m_currentState = PersonState::Idle;
            //send stop to uiItem
        }
        break;
    case MovingToAttack:
        if (!m_lockedOnEnemy.expired())
        {
            auto enemyUnit = m_lockedOnEnemy.lock();
            if (checkIfEnemyInWeaponRange(enemyUnit->m_uiItem.get()))
            {
                m_currentState = PersonState::Attacking;
                //do attacking stuff - damage, animation and so on
            }
            else
            {
                if (m_destination.x() != enemyUnit->getPosition().x() || m_destination.y() != enemyUnit->getPosition().y())
                {
                    move(enemyUnit->getPosition().x(), enemyUnit->getPosition().y());
                    //do moving towards the enemy, and check every position update if he didnt move and call move again
                }
            }
        }
        else
        {
            //locked on enemy died or run away
            m_currentState = PersonState::Idle;
            //send stop to uiItem
        }
        break;
    case Attacking:
        if (m_lockedOnEnemy.expired())
        {
            //locked on enemy died or run away
            m_currentState = PersonState::Idle;
            //send stop to uiItem
        }
        else
        {
            //else still do attacking stuff
        }
        break;
    case Retreating:
        break;
    case Defending:
        break;
    default:
        break;
    }
}
