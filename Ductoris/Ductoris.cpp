#include "Ductoris.h"
#include <QString>
#include <iostream>
#include <QQmlProperty>
#include <QQuickItem>
#include <QQmlContext>

const QString MAIN_QML_SRC_FILENAME = QStringLiteral("qrc:/src/ui/main.qml");

//singleton init
Ductoris *Ductoris::m_ductorisGame = nullptr;

Ductoris::Ductoris()
{

}

void Ductoris::initilize()
{
    Ductoris::m_ductorisGame = new Ductoris();
    std::unique_ptr<QQmlApplicationEngine> engine(new QQmlApplicationEngine());
    engine->load(QUrl(MAIN_QML_SRC_FILENAME));
    if(!engine->rootObjects().empty())
    {
        QObject* window = engine->rootObjects().first();
        //expose object as api to qml
        engine->rootContext()->setContextProperty("_ductorisApi", Ductoris::m_ductorisGame);
        qobject_cast<QQuickWindow*>(window)->show();
        Ductoris::m_ductorisGame->m_engine = std::move(engine);
    }
}

Ductoris::~Ductoris()
{

}

Ductoris *Ductoris::getInstance()
{
    if(!Ductoris::m_ductorisGame)
    {
        //initialize game
        Ductoris::m_ductorisGame->initilize();
    }
    return  Ductoris::m_ductorisGame;
}

void Ductoris::onGameCanvasClicked(int x, int y, int mouseBtn)
{
    std::cout << "Game canvas clicked " << std::endl;
}




