#ifndef WEAPONTESTS_H
#define WEAPONTESTS_H
#include <QTest>

class WeaponTests: public QObject
{
     Q_OBJECT
private slots:
    //Tests
    void TestCase_Weapon_DeafultConstructor();

};

#endif // WEAPONTESTS_H
