#include <QtTest>
#include "AbstractArmyFactoryTests.h"
#include "RomanArmyFactoryTests.h"


int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    if (engine.rootObjects().isEmpty())
//        return -1;
    AbstractArmyFactoryTests abstractArmyFactoryTestSuite;
    RomanArmyFactoryTests romanArmyFactoryTestSuite;
    return QTest::qExec(&abstractArmyFactoryTestSuite, argc, argv) |
            QTest::qExec(&romanArmyFactoryTestSuite, argc, argv);
}
