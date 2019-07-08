#include <QtTest>
#include "AbstractArmyFactoryTests.h"
#include "RomanArmyFactoryTests.h"
#include "persontests.h"
#include "WeaponTests.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    AbstractArmyFactoryTests abstractArmyFactoryTestSuite;
    RomanArmyFactoryTests romanArmyFactoryTestSuite;
    PersonTests personInterfaceTests;
    WeaponTests weaponTests;
    return QTest::qExec(&abstractArmyFactoryTestSuite, argc, argv) |
            QTest::qExec(&romanArmyFactoryTestSuite, argc, argv) |
            QTest::qExec(&personInterfaceTests, argc, argv) |
            QTest::qExec(&weaponTests, argc, argv);
}
