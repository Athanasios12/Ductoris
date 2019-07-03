#include <QtTest>
#include "AbstractArmyFactoryTests.h"
#include "RomanArmyFactoryTests.h"
#include "persontests.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    AbstractArmyFactoryTests abstractArmyFactoryTestSuite;
    RomanArmyFactoryTests romanArmyFactoryTestSuite;
    PersonTests personInterfaceTests;
    return QTest::qExec(&abstractArmyFactoryTestSuite, argc, argv) |
            QTest::qExec(&romanArmyFactoryTestSuite, argc, argv) |
            QTest::qExec(&personInterfaceTests, argc, argv);
}
