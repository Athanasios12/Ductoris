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
    struct Stats
    {
        uint16_t m_health{0};
        uint16_t m_morale{0};
        uint16_t m_attack{0};
        uint16_t m_defence{0};
        uint16_t m_stamina{0};
        uint16_t m_speed{0};

        void addBonus(SkillTree::LevelBonus bonus)
        {
            m_health += bonus.m_healthBonus;
            m_defence += bonus.m_defenceBonus;
            m_attack += bonus.m_attackBonus;
            m_morale += bonus.m_moraleBonus;
            m_speed += bonus.m_speedBonus;
            m_stamina += bonus.m_stamina;
        }
    };
    enum PersonState
    {
        Idle = 0,
        Moving,
        MovingToAttack,
        Attacking,
        Defending,
        Retreating
    };

    Person();
    Person(const Person &other);
    Person& operator=(const Person &other);
    Person(Person &&other);
    Person& operator=(Person &&other);
    virtual ~Person();

    bool setUiItem(std::unique_ptr<QQuickItem> &uiItem);    

    QPoint getPosition() const;
    quint16 getWidth() const;
    quint16 getHeight() const;
    int getRotation() const;
    uint32_t getExp() const;
    uint8_t getLevel() const;
    PersonState getCurrentState() const;
    DuctorisTypes::ArmyType getPersonArmyType() const;
    bool isConnectedToUi() const;

    virtual bool addExp(uint16_t exp);
    virtual void changeArmor(Armor &armor);
    virtual void addWeapon(std::unique_ptr<Weapon> &weapon);

    virtual void move(int newX, int newY);
    virtual void attack(std::shared_ptr<Person> &enemyUnit); //attack and lock on enemy
protected:
    bool checkIfEnemyInWeaponRange(const QQuickItem &enemy) const;
public slots:
    void onPositionChanged(int x, int y, int rotation);
signals:
    //sets the source and parameters of specific person sprite - roman swordsman, macedon spearman, etc...
    void setSpriteData(int spriteType, const QString &spriteImgSource, int frameCount,
                       int frameWidth, int frameHeight, int frameRate);
    void setPrimaryWeaponSprite();
    void setSecondaryWeaponSprite();
    void setArmorSprite();
    void updatePersonMovementStats(QVariant speed, QVariant rotationSpeed);
    void updatePersonMovementData(QVariant newX, QVariant newY, QVariant time, QVariant rotationAngle);
    void personStateUpdate(); // indicates movement, attack, decrease in stamina, etc.. - switch between attack,move animation
protected:
    //Type
    DuctorisTypes::ArmyType m_type;
    std::unique_ptr<SkillTree> m_skillTree{nullptr};
    //Person Stats
    Stats m_stats;
    uint32_t m_exp{0};
    uint8_t m_level{0};
    PersonState m_currentState{Idle};
    //equipment
    Armor m_armor;
    std::vector<std::unique_ptr<Weapon>> m_weapons;
    uint8_t m_currentWeaponIdx{0};
    //location
    QPoint m_destination{0, 0};
    std::weak_ptr<Person> m_lockedOnEnemy;
    //qml uiItem data    
    std::unique_ptr<QQuickItem> m_uiItem{nullptr};
    QPoint m_weaponAnchorPoint{0, 0}; // defined in sprite design, weapon is a subitem of person sprite anchors to its hand sprite subitem
    // has defined a static anchor point in person coordinates system
    bool m_connectedToUi{false};
};

#endif // PERSON_H
