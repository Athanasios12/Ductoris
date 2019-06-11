#include "Ductoris.h"
#include <QString>
#include <iostream>
#include <QQmlProperty>
#include <QQuickItem>
#include <QQmlContext>
#include "armyfactory.h"
#include "globaldata.h"
#include "romanarmyfactory.h"

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

qint16 Ductoris::checkIfSelectedAUnit(int x, int y) const
{
    qint16 personIdx = -1;
    //check if under x, y position a person is present under x, y position
    return personIdx;
}

qint16 Ductoris::checkIfEnemyClicked(int x, int y) const
{
    qint16 enemyIdx = -1;
    //check if under x, y position is a enemy unit that can be attacked
    return enemyIdx;
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

void Ductoris::onChosenLeader(int leaderType)
{
    std::unique_ptr<ArmyFactory> factory;
    switch(static_cast<DuctorisTypes::ArmyType>(leaderType))
    {
    case DuctorisTypes::Roman:
        factory.reset(new RomanArmyFactory);
        break;
    case DuctorisTypes::Macedon:
        break;
    case DuctorisTypes::Gallic:
        break;
    default:
        break;
    }
    std::shared_ptr<Person> leader(factory->createLeader());
    m_allUnits.push_back(std::move(leader));
}

void Ductoris::onGameCanvasClicked(int x, int y, int mouseBtn)
{
    std::cout << "Game canvas clicked " << std::endl;
    //for now a simple placeholder
    if(mouseBtn == Qt::LeftButton) // left button clicked - select or move
    {
        if(m_unitSelected)
        {
            //move selected unit
            if(m_selectedUnit.lock()) // make sure not a dangling pointer
            {
                m_selectedUnit->move(x, y);
            }
        }
        else
        {
            auto personIdx = checkIfSelectedAUnit(x, y);
            if(personIdx >= 0)
            {
                m_selectedUnit = m_allUnits[personIdx];
                m_unitSelected = true;
            }
        }
    }
    else if(mouseBtn == Qt::RightButton) // right button clicked - attack
    {
        if(m_unitSelected && m_selectedUnit.lock())
        {
            //attack
            auto enemyIdx = checkIfEnemyClicked(x, y);
            if(enemyIdx >= 0)
            {
                m_selectedUnit->setActiveEnemy(m_enemyUnits[enemyIdx]);
                m_selectedUnit->attack();
            }
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




