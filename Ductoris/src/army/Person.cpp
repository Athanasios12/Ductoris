#include "Person.h"
#include "armyfactory.h"
#include <algorithm>
#include <cstdlib>
#include <QQmlProperty>
#include <cmath>
#include <iostream>

quint32 Person::m_new_id = 1;

Person::Person():
    m_id{m_new_id}
{
    ++m_new_id;
}

Person::Person(const Person &other):
    m_id{m_new_id},
    m_type(other.m_type),
    m_currentStats(other.m_currentStats),
    m_exp(other.m_exp),
    m_level(other.m_level),
    m_armor(other.m_armor)
{
    ++m_new_id;
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
        m_id = m_new_id;
        ++m_new_id;
        m_type = other.m_type;
        m_currentStats = other.m_currentStats;
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
    m_id{other.m_id},
    m_type(other.m_type),
    m_currentStats(other.m_currentStats),
    m_exp(other.m_exp),
    m_level(other.m_level)
{
    other.m_currentStats = SkillTree::UnitStats();
    other.m_exp = 0;
    other.m_level = 0;
    other.m_id = 0;
    m_armor = std::move(other.m_armor);
    m_weapons = std::move(other.m_weapons);
}

Person &Person::operator=(Person &&other)
{
    if (this != &other)
    {
        m_id = other.m_id;
        m_type = other.m_type;
        m_currentStats = other.m_currentStats;
        m_exp = other.m_exp;
        m_level = other.m_level;
        other.m_id = 0;
        other.m_currentStats = SkillTree::UnitStats();
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

quint32 Person::getId() const
{
    return m_id;
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

quint16 Person::getRotation() const
{
    quint16 rotation = 0;
    if (m_uiItem)
    {
        rotation = static_cast<quint16>(m_uiItem->rotation()) % 360u;
    }
    return rotation;
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

quint32 Person::getExp() const
{
    return m_exp;
}

quint8 Person::getLevel() const
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

bool Person::addExp(quint16 exp)
{
    bool levelUp = false;
    //later on add perk check for
    if (m_skillTree)
    {
        if (m_level < m_skillTree->getMaxLevel())
        {
            m_exp += exp;
            if (m_skillTree->checkIfLevelThresholdReached(m_exp))
            {
                //leveled up - max stats increased, new skills, perks unlocked
                //Select skills and perks
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

void Person::fightingUpdate()
{
    //If moving then do nothing, the command is ongoing
    //when completed this object will be signalled by ui

    //If the unit is fighting - attacking or defending this function needs
    //to be called cyclicly to send damage info to its oponent
    if (m_uiItem)
    {
        if ((PersonState::Attacking == m_currentState ||
            PersonState::Defending == m_currentState) && !m_lockedOnEnemy.expired())
        {
            //TODO - handle being attacked by multiple oponents,
            //when new opponent attacks this unit and its already engaged
            //it subscribes to its damage receive signal. The defender needs to
            //know how many oponents its has to calculate how much damage is sent
            //to each of them
            auto enemyUnit = m_lockedOnEnemy.lock();
            //check if locked on enemy is still alive
            if (PersonState::Dead != enemyUnit->getCurrentState())
            {
                if (checkIfEnemyInWeaponRange(enemyUnit->m_uiItem.get()))
                {
                    //do attacking stuff - damage, animation and so on
                    quint16 damage = calculateAttackDamage();
                    //Signal target about received damage
                    AttackOrientation orientation = getAttackOrientation();
                    emit attackedEnemy(m_id, damage, orientation,
                        m_weapons[m_currentWeaponIdx]->getWeaponType());
                }
                else
                {
                    move(enemyUnit->getPosition().x(),
                         enemyUnit->getPosition().y());
                    m_currentState = PersonState::MovingToAttack;
                    emit personStateUpdate(m_currentState);
                }
            }
        }
    }
}

void Person::move(int newX, int newY)
{
    if (PersonState::Dead != m_currentState &&
        PersonState::Retreating != m_currentState)
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
                + pow(abs(newY - y), 2)) * m_currentStats.m_speed);
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
            emit personStateUpdate(m_currentState);
            emit updatePersonMovementData(newX, newY, time, rotationAngle);
        }
    }
}

void Person::attack(std::shared_ptr<Person> enemyUnit)
{
    if (m_connectedToUi && enemyUnit)
    {
        bool validEnemy = false;
        //can try attacking only if is not retreating
        if (m_currentState != PersonState::Retreating &&
            m_currentState != PersonState::Dead)
        {
            if ((m_lockedOnEnemy.use_count() == 0) ||
                (enemyUnit.get() != m_lockedOnEnemy.lock().get()))
            {
                //Unit is not engaged or new enemy unit and is not attacking,
                // or defending
                if (m_currentState != PersonState::Attacking &&
                    m_currentState != PersonState::Defending)
                {
                    m_lockedOnEnemy = enemyUnit;
                    connect(this, &Person::attackedEnemy,
                            m_lockedOnEnemy.lock().get(), &Person::onAttackedByEnemy);
                    connect(m_lockedOnEnemy.lock().get(), &Person::personDied,
                            this, &Person::onLockedOnEnemyDied);
                    validEnemy = true;
                }
            }
            else
            {
                //attacking currently locked on enemy
                validEnemy = true;                
            }
            if (validEnemy)
            {                
                if (checkIfEnemyInWeaponRange(enemyUnit->m_uiItem.get()))
                {
                    //Inform Ui if state changed
                    m_currentState = PersonState::Attacking;
                    //do attacking stuff - damage, animation and so on
                    quint16 damage = calculateAttackDamage();
                    //Signal target about received damage
                    AttackOrientation orientation = getAttackOrientation();
                    emit attackedEnemy(m_id, damage, orientation,
                        m_weapons[m_currentWeaponIdx]->getWeaponType());
                    emit personStateUpdate(m_currentState);
                }
                else
                {
                    move(enemyUnit->getPosition().x(),
                         enemyUnit->getPosition().y());
                    m_currentState = PersonState::MovingToAttack;
                    //do moving towards the enemy, and check every position update
                    //if he didnt move and call move again
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
                m_weaponAnchorPoint = QQmlProperty::read(
                            qobject_cast<QObject*>(m_uiItem.get()),
                            "PrimaryWeaponAnchorPoint").toPoint();
                //Weapon achor is in persons coordinates system,
                //the anchor point is weapons bottom left corner
                for(int x_weapon = m_weaponAnchorPoint.x();
                    x_weapon <= weaponWidth + m_weaponAnchorPoint.x(); x_weapon++)
                {
                    for(int y_weapon = m_weaponAnchorPoint.y();
                        y_weapon <= weaponHeight + m_weaponAnchorPoint.y(); y_weapon++)
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

bool Person::calculateDamageResults(quint16 damage,
                                    Person::AttackOrientation orientation,
                                    Weapon::WeaponType weaponType)
{
    return true;
}

bool Person::moraleCheck() const
{
    if (m_skillTree)
    {
        if (m_currentStats.m_morale < m_skillTree->
            getMoraleRetreatThreshold(m_level))
        {
            return false;
        }
    }
    return true;
}

quint16 Person::calculateAttackDamage() const
{
    //TODO
    //Take into account possible multiple opponents - damage reduce because of multiple targets
    //return (m_currentStats.m_attack * m_skillTree->staminaAttackCoeff(m_currentStats.m_stamina)) +
    //m_skillTree->stanceAttackModifier(m_currentState) + m_skillTree->skillModifier() +
    //m_skillTree->perkModifier() + defenderOrientetionModifier();
    return 0;
}

Person::AttackOrientation Person::getAttackOrientation() const
{
    AttackOrientation orientation = AttackOrientation::Frontal;
    if (!m_lockedOnEnemy.expired())
    {
        quint16 rotation = m_lockedOnEnemy.lock()->getRotation();
        if (rotation)
        {

        }
    }
    return orientation;
}

void Person::retreat()
{
    //TODO
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
            //Inform Ui
            emit personStateUpdate(m_currentState);
        }
        break;
    case MovingToAttack:
        if (!m_lockedOnEnemy.expired())
        {
            auto enemyUnit = m_lockedOnEnemy.lock();
            if (checkIfEnemyInWeaponRange(enemyUnit->m_uiItem.get()))
            {
                m_currentState = PersonState::Attacking;
                //Inform Ui
                emit personStateUpdate(m_currentState);
                //do attacking stuff - damage, animation and so on
                attack(enemyUnit);
            }
            else
            {
                if (m_destination.x() != enemyUnit->getPosition().x() ||
                    m_destination.y() != enemyUnit->getPosition().y())
                {
                    move(enemyUnit->getPosition().x(), enemyUnit->getPosition().y());
                    //do moving towards the enemy, and check every position update
                    //if he didnt move and call move again
                }
            }
        }
        else
        {
            //locked on enemy died or run away
            m_currentState = PersonState::Idle;
            //Inform Ui
            emit personStateUpdate(m_currentState);
        }
        break;
    case Attacking:
        if (m_lockedOnEnemy.expired())
        {
            //locked on enemy died or run away
            m_currentState = PersonState::Idle;
            //Inform Ui
            emit personStateUpdate(m_currentState);
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

void Person::onAttackedByEnemy(quint32 person_id, quint16 damage,
                               AttackOrientation orientation,
                               Weapon::WeaponType weaponType)
{
    //calculate received damage
    bool stillAlive = calculateDamageResults(damage, orientation, weaponType); //damage modificators -
    //are already calculated on attacker side - takes into accoutn their parameters
    //target state, orientation(target is attacked from side rear or front
    if (stillAlive)
    {
        //update unit state
        if (!moraleCheck())
        {
            if (Retreating != m_currentState)
            {
                //unit morale too low, flee
                m_currentState = Retreating;                
                retreat();
                emit personStateUpdate(Retreating);
            }
        }
        else
        {
            if (Attacking != m_currentState)
            {
                //Depending on attack type - ranged or melee the move to
                //defending state will be dependent on unit skills and
                //unit will still move to locked on target while being under
                //enemy fire
                m_currentState = Defending;
                emit personStateUpdate(Defending);
            }
            else
            {
                //if is in attacking state then check if attacked
                //by another not engaged oponent
                if (person_id != m_lockedOnEnemy.lock()->getId())
                {
                    //new enemy - encircled, flanked reared, handle new enemy
                }
                else
                {
                    //blow exchange with current enemy no special behaviour
                }
            }
        }
    }
    else
    {
        //Unit died after attacked
        //send signal to ui - animte death, show corpse sprite,
        //signal the owner of this unit to destroy it to free memory
        //If unit is part of squadm inform squad members od its death,
        //lower the morale
        m_currentState = Dead;
        emit personDied();
        emit personStateUpdate(Dead);
    }
}

void Person::onLockedOnEnemyDied()
{
    if (!m_lockedOnEnemy.expired())
    {
        disconnect(this, nullptr, m_lockedOnEnemy.lock().get(), nullptr);
        m_currentState = Idle;
    }
}
