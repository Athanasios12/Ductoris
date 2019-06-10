#include "Ductoris.h"
#include <QString>
#include <iostream>
#include <QQmlProperty>
#include <QQuickItem>
#include <QQmlContext>

const QString MAIN_QML_SRC_FILENAME = QStringLiteral("qrc:/src/ui/main.qml");
const QString BATTLE_SCREEN = QStringLiteral("battleWindowScreen");
const QString GAME_CANVAS = QStringLiteral("gameCanvas");
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

void Ductoris::movePerson(int x, int y)
{
    //calculate the movement parameters and signal the ui
    m_selectedPerson->updatePersonMovementData();
}

Person* Ductoris::checkIfSelectedAPerson(int x, int y) const
{
    Person* selected = nullptr;
    //check if under x, y position a person is present under x, y position
    return selected;
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

bool Ductoris::addNewUnit()
{

}

void Ductoris::onGameCanvasClicked(int x, int y, int mouseBtn)
{
    std::cout << "Game canvas clicked " << std::endl;
    //for now a simple placeholder
    if(mouseBtn == Qt::LeftButton) // left button clicked - select or move
    {
        if(m_personSelected)
        {
            movePerson(x, y);
        }
        else
        {
            auto person = checkIfSelectedAPerson(x, y);
            if(person)
            {
                m_selectedPerson = person;
                m_personSelected = true;
            }
        }
    }
    else if(mouseBtn == Qt::RightButton) // right button clicked - attack
    {
        if(m_personSelected)
        {
            //attack
        }
    }
}

void Ductoris::onGameStarted()
{
    QObject* window = m_engine->rootObjects().first();
    auto bscreen = window->findChild<QObject*>(BATTLE_SCREEN);
    if(bscreen)
    {
        std::cout << "\n---Found Battle Screen!---\n" << std::endl;
        auto gameCanvas = window->findChild<QObject*>(GAME_CANVAS);
        if(gameCanvas)
        {
            std::cout << "\n---Found Game Canvas!---\n" << std::endl;
        }
    }
}

void Ductoris::onExitGame()
{

}




