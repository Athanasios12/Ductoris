#ifndef WEAPON_H
#define WEAPON_H
#include <QObject>
#include <QString>
#include <QSize>
#include <memory>

class Weapon : public QObject
{
    Q_OBJECT
public:
    //Maybe will add more variety in future - slashing(swords, axes), bashing(clubs), piercing(spears),
    //ranged normal(arroraws), ranged armor piercing(javelin)
    enum WeaponType
    {
        Melee = 0,
        Ranged
    };
    Q_ENUM(WeaponType)
    Weapon();
    Weapon(uint8_t level,
           uint16_t attackBonus,
           uint16_t defenceBonus,
           uint16_t staminaDrain,
           uint16_t speed);
    Weapon(const Weapon &other);
    Weapon(Weapon &&other);
    Weapon& operator=(const Weapon &other);
    Weapon& operator=(Weapon &&other);
    ~Weapon();

    void setSize(const QSize &size);

    QSize getSize() const;
    QString getSpriteImgSource() const;
    uint16_t getLevelCap() const;
    uint16_t getAttackBonus() const;
    uint16_t getDefenceBonus() const;
    uint16_t getStaminaDrain() const;
    uint16_t getSpeed() const;
    WeaponType getWeaponType() const;

protected:        
    QString m_spriteImgSource;
    QSize m_weaponSize{0, 0};    
    uint16_t m_attackBonus{0};
    uint16_t m_defenceBonus{0};
    uint16_t m_staminaDrain{0};
    uint16_t m_speed{0};
    WeaponType m_weaponType{Melee};
    uint8_t m_level{1};
};

#endif // WEAPON_H
