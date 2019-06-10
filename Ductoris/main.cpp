#include <QGuiApplication>
#include "Ductoris.h"


int main(int argc, char *argv[])
{
//    QGuiApplication app(argc, argv);
//    QQmlApplicationEngine engine;
//    engine.load(QUrl(QStringLiteral("qrc:/src/ui/main.qml")));
//    if(engine.rootObjects().empty())
//    {
//        return -1;
//    }
//    QQuickWindow *window = qobject_cast<QQuickWindow*>(engine.rootObjects().at(0));
//    window->show();
    QGuiApplication app(argc, argv);
    auto game = Ductoris::getInstance();
    if(!game)
    {
        return -1;
    }
    return app.exec();
}
