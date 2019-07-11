#ifndef WEAPON_H
#define WEAPON_H
#include <QString>
#include <QSize>
#include <memory>

class Weapon
{
public:   
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

    QSize getSize() const;
    QString getSpriteImgSource() const;
    uint16_t getLevelCap() const;
    uint16_t getAttackBonus() const;
    uint16_t getDefenceBonus() const;
    uint16_t getStaminaDrain() const;
    uint16_t getSpeed() const;
    bool isRanged() const;

protected:
    uint8_t m_level{1};
    uint16_t m_attackBonus{0};
    uint16_t m_defenceBonus{0};
    uint16_t m_staminaDrain{0};
    uint16_t m_speed{0};
    bool m_isRanged{false};
    QString m_spriteImgSource;
    QSize m_weaponSize{0, 0};
};

#endif // WEAPON_H
