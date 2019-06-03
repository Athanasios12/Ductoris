#ifndef ROMANLEADERTESTS_H
#define ROMANLEADERTESTS_H
#include <QTest>

class RomanLeaderTests : public QObject
{
    Q_OBJECT
private slots:
    void TestCase_RomanLeader_DefaultConstructor();
    void TestCase_RomanLeader_addSoldier_RSwordsman();
    void TestCase_RomanLeader_addSoldier_ROfficer();
    //expierence
    void TestCase_RomanLeader_LevelUp_NoPerk();
    void TestCase_RomanLeader_LevelUp_NewPerk();
};



#endif // ROMANLEADERTESTS_H
