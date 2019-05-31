#ifndef ABSTRACTARMYFACTORYTESTS_H
#define ABSTRACTARMYFACTORYTESTS_H
#include <QTest>

class AbstractArmyFactoryTests : public QObject
{
    Q_OBJECT
private slots:
    void TestCase_RomanArmyFactoryCreation();
    void TestCase_MacedonArmyFactoryCreation();
    void TestCase_GallicArmyFactoryCreation();
};

#endif // ABSTRACTARMYFACTORYTESTS_H
