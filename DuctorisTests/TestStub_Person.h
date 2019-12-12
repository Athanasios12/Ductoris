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

    void tst_setPersonMoraleCheck(bool moraleCheckReturn);
    void tst_setCalculateDamageResults(bool calculateDamageResultsReturn);

    bool moraleCheck() const override;
    bool checkIfEnemyInWeaponRange(const QQuickItem *enemyUiItem) override;
    bool calculateDamageResults(int damage) override;
private:
    bool m_tst_moraleCheckReturn{false};
    bool m_tst_calculateDamageResultsReturn{false};
};

#endif // TESTSTUB_PERSON_H
