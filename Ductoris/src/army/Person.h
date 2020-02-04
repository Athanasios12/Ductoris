#ifndef PERSON_H
#define PERSON_H
#include <utility>
#include <cstdint>
#include "armor.h"
#include "weapon.h"
#include <vector>
#include <memory>
#include "skilltree.h"
#include "globaldata.h"
#include <QObject>
#include <QQuickItem>

class Person : public QObject
{
    Q_OBJECT
public:
    enum PersonState
    {
        Idle = 0,
        Moving,
        MovingToAttack,
        Attacking,
        Defending,
        Retreating,
        Dead
    };
    //Defines types of orientation when attacking
    //enemy. Proposed limits need to be tested.
    //Information needed both on attacker and defender side - calculating
    //damage modificator on attacker side
    enum AttackOrientation
    {
        Invalid = 0,
        Frontal,     // <140; 220> degrees related to orientation of target
        Flank,       // <40; 140) u (220; 320>
        Rear         // (320; 40)
    };
    Q_ENUM(AttackOrientation)

    Person();
    Person(const Person &other);
    Person& operator=(const Person &other);
    Person(Person &&other);
    Person& operator=(Person &&other);
    virtual ~Person();

    bool setUiItem(std::unique_ptr<QQuickItem> &uiItem);

    quint32 getId() const;
    QPoint getPosition() const;
    quint16 getRotation() const;
    quint16 getWidth() const;
    quint16 getHeight() const;
    quint32 getExp() const;
    quint8 getLevel() const;
    PersonState getCurrentState() const;
    DuctorisTypes::ArmyType getPersonArmyType() const;
    bool isConnectedToUi() const;

    virtual bool addExp(uint16_t exp);
    virtual void changeArmor(Armor &armor);
    virtual void addWeapon(std::unique_ptr<Weapon> &weapon);

    virtual void fightingUpdate();
    virtual void move(int newX, int newY);
    virtual void attack(std::shared_ptr<Person> enemyUnit); //attack and lock on enemy
protected:
    virtual bool checkIfEnemyInWeaponRange(const QQuickItem *enemyUiItem);
    virtual bool calculateDamageResults(quint16 damage,
                                        AttackOrientation orientation,
                                        Weapon::WeaponType weaponType);
    virtual bool moraleCheck() const;
    //for attacking and moving add later on a gradual lose of stamina
    //based on unit state - Idle - resting, increasing or not decreasing
    //other, decreasing. Stamina should be used when calculating unit morale
    //when attacked by enemy
    virtual quint16 calculateAttackDamage() const;
    virtual AttackOrientation getAttackOrientation() const;
    virtual void retreat();
public slots:
    void onPositionChanged(int x, int y, int rotation);
    void onAttackedByEnemy(quint32 person_id, quint16 damage,
                           AttackOrientation orientation,
                           Weapon::WeaponType weaponType);
    void onLockedOnEnemyDied();
signals:
    //Signals to UI
    //sets the source and parameters of specific person sprite - roman swordsman, macedon spearman, etc...
    void setPersonBodySprite(int spriteType, const QString &spriteImgSource, int frameCount,
                             int frameWidth, int frameHeight, int frameRate);
    void setPrimaryWeaponSprite(const QString &spriteImgSource, int frameCount,
                                int frameWidth, int frameHeight, int frameRate); //main weapon
    void setSecondaryWeaponSprite(const QString &spriteImgSource, int frameCount,
                                  int frameWidth, int frameHeight, int frameRate); //weapon or shield in other hand
    void setArmorSprite(const QString &spriteImgSource, int frameCount,
                        int frameWidth, int frameHeight, int frameRate);
    void updatePersonMovementStats(QVariant speed, QVariant rotationSpeed);
    void updatePersonMovementData(QVariant newX, QVariant newY, QVariant time, QVariant rotationAngle);
    void personStateUpdate(QVariant newState); // indicates movement, attack, decrease in stamina, etc.. - switch between attack,move animation

    void attackedEnemy(quint32 id, quint16 damage,
                       Person::AttackOrientation orientation,
                       Weapon::WeaponType weaponType); // inform enemy that it was attacked - change its state, calculate damage, stamina, morale loss based
    // on the attacker parameters
    void personDied();
protected:
    //Type
    quint32 m_id{0};
    static quint32 m_new_id;
    DuctorisTypes::ArmyType m_type;
    std::unique_ptr<SkillTree> m_skillTree{nullptr};
    //Person Stats
    SkillTree::UnitStats m_currentStats;
    quint32 m_exp{0};
    quint8 m_level{0};
    PersonState m_currentState{Idle};
    //equipment
    Armor m_armor;
    std::vector<std::unique_ptr<Weapon>> m_weapons;
    quint8 m_currentWeaponIdx{0};
    //location
    QPoint m_destination{0, 0};
    quint8 m_numOfOpponents{0};
    std::weak_ptr<Person> m_lockedOnEnemy;
    //qml uiItem data
    std::unique_ptr<QQuickItem> m_uiItem{nullptr};
    QPoint m_weaponAnchorPoint{0, 0}; // defined in sprite design, weapon is a subitem of person sprite anchors to its hand sprite subitem
    // has defined a static anchor point in person coordinates system from which the range of attack is calculated - most extended position in stabbing animation
    bool m_connectedToUi{false};
};

#endif // PERSON_H
