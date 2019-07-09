#ifndef WEAPON_H
#define WEAPON_H
#include <QObject>
#include <QQuickItem>
#include <memory>

class Weapon : public QObject
{
    Q_OBJECT
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

    bool setUiItem(std::unique_ptr<QQuickItem> &uiItem);
    bool checkIfEnemyInWeaponRange(const QQuickItem *enemyUiItem) const;
signals:
    void setSpriteData(int spriteType, const QString &spriteImgSource, int frameCount,
                       int frameWidth, int frameHeight, int frameRate);
private:
    uint8_t m_level{1};
    uint16_t m_attackBonus{0};
    uint16_t m_defenceBonus{0};
    uint16_t m_staminaDrain{0};
    uint16_t m_speed{0};
    std::unique_ptr<QQuickItem> m_uiItem{nullptr};
};

#endif // WEAPON_H
