#ifndef TESTSTUB_PERSON_H
#define TESTSTUB_PERSON_H
#include "Person.h"

class TestStub_Person : public Person
{
public:
    TestStub_Person() = default;

    void tst_setWeaponAchorPoint(const QPoint &position);
    void tst_setUiItemPosition(const QPoint& pos);
    void tst_setPersonState(const PersonState state);

    bool checkIfEnemyInWeaponRange(const QQuickItem *enemyUiItem) override;

};

#endif // TESTSTUB_PERSON_H
