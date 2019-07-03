#ifndef ROMANLEADERTESTS_H
#define ROMANLEADERTESTS_H
#include <QTest>

class RomanLeaderTests : public QObject
{
    Q_OBJECT
private slots:
    void TestCase_RomanLeader_DefaultConstructor();

    //Add new troops for Roman Leader
    void TestCase_RomanLeader_addSoldier_RSwordsman();
    void TestCase_RomanLeader_addSoldier_RArcher();
    void TestCase_RomanLeader_addSoldier_RSkirmisher();
    void TestCase_RomanLeader_addSoldier_RSpearman();
    void TestCase_RomanLeader_addSoldier_RHorseman();
    void TestCase_RomanLeader_addSoldier_ROfficer();

    //expierence
    void TestCase_RomanLeader_ExpIncrease_EnemyKill();
    void TestCase_RomanLeader_LevelUp_NoPerk();
    void TestCase_RomanLeader_LevelUp_NewPerk();

    //copy, move constructors and assignment operators
    void TestCase_RomanLeader_CopyConstructor();
    void TestCase_RomanLeader_CopyAssignment();
    void TestCase_RomanLeader_MoveConstructor();
    void TestCase_RomanLeader_MoveAssignment();
};



#endif // ROMANLEADERTESTS_H
