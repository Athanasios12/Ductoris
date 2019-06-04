#include <QGuiApplication>
#include <QQuickView>
#include <QQuickItem>
#include "Person.h"
#include "Soldier.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickView view(QUrl(QStringLiteral("qrc:/src/ui/BattleScreen.qml")));
    if (!view.rootObject())
        return -1;
    view.show();
    return app.exec();
}
