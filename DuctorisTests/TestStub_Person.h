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

    //set stub return
    void tst_set_moraleCheck_Return(bool moraleCheckReturn);
    void tst_set_calculateDamageResults_Return(bool calculateDamageResultsReturn);
    void tst_set_calculateAttackDamage_Return(uint16_t calculateDamageResultsReturn);
    void tst_set_getAttackOrientation_Return(AttackOrientation attackOrientationReturn);    

    //disable, enable stubbed method
    void tst_set_moraleCheck_UseStub(bool useStub);
    void tst_set_calculateDamageResults_UseStub(bool useStub);
    void tst_set_calculateAttackDamage_UseStub(bool useStub);
    void tst_set_getAttackOrientation_UseStub(bool useStub);
    void tst_set_retreat_UseStub(bool useStub);

    //method stubs
    bool moraleCheck() const override;
    bool calculateDamageResults(quint16 damage,
                                AttackOrientation orientation,
                                Weapon::WeaponType weaponType) override;
    quint16 calculateAttackDamage() const override;
    AttackOrientation getAttackOrientation() const override;
    void retreat() override;

    //fakes - not stubs but a override to remove Ui dependency
    bool checkIfEnemyInWeaponRange(const QQuickItem *enemyUiItem) override;

    //test slots data getters
    AttackOrientation tst_get_sentAttack_Orienation() const;
    quint16 tst_get_sentAttack_Damage() const;
public slots:
    void onSentAttackEnemy(quint32 person_id, quint16 damage,
                           AttackOrientation orientation,
                           Weapon::WeaponType weaponType);
private:    
    quint16 m_tst_sentAttack_Damage{0};
    quint16 m_tst_calculateAttackDamage_ReturnVal{0};
    AttackOrientation m_tst_getAttackOrientation_ReturnVal{Invalid};
    AttackOrientation m_tst_sentAttack_Orientation;
    bool m_tst_moraleCheck_ReturnVal{false};
    bool m_tst_calculateDamageResults_ReturnVal{false};
    bool m_tst_useStub_moraleCheck{false};
    bool m_tst_useStub_calculateDamageResults{false};
    bool m_tst_useStub_calculateAttackDamage{false};
    bool m_tst_useStub_getAttackOrientation{false};
    bool m_tst_useStub_retreat{false};
};

#endif // TESTSTUB_PERSON_H
