#include <QtTest>
#include "AbstractArmyFactoryTests.h"
#include "RomanArmyFactoryTests.h"
#include "persontests.h"
#include "WeaponTests.h"

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    QQuickView *view = new QQuickView;

    view->setSource(QUrl(QStringLiteral("qrc:/src/ui/BattleScreen.qml")));
    view->show();

    AbstractArmyFactoryTests abstractArmyFactoryTestSuite;
    RomanArmyFactoryTests romanArmyFactoryTestSuite;
    PersonTests personInterfaceTests;
    personInterfaceTests.setQmlQuickView(view);
    WeaponTests weaponTests;
    return QTest::qExec(&abstractArmyFactoryTestSuite, argc, argv) |
            QTest::qExec(&romanArmyFactoryTestSuite, argc, argv) |
            QTest::qExec(&personInterfaceTests, argc, argv) |
            QTest::qExec(&weaponTests, argc, argv) | a.exec();
}
