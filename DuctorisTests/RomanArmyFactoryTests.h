#ifndef ROMANARMYFACTORYTESTS_H
#define ROMANARMYFACTORYTESTS_H
#include <QTest>

class RomanArmyFactoryTests : public QObject
{
    Q_OBJECT
private slots:
    void TestCase_CreateRomanLeader();
    void TestCase_CreateRomanOfficer();
    void TestCase_CreateRomanSwordsman();
    void TestCase_CreateRomanSpearman();
    void TestCase_CreateRomanArcher();
    void TestCase_CreateRomanSkirmisher();
    void TestCase_CreateRomanHorseman();
};

#endif // ROMANARMYFACTORYTESTS_H
