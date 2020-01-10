#include "Ductoris.h"
#include <QString>
#include <iostream>
#include <QQmlProperty>
#include <QQuickItem>
#include <QQmlContext>
#include <QQmlComponent>
#include "armyfactory.h"
#include "globaldata.h"
#include "romanarmyfactory.h"

const QString MAIN_QML_SRC_FILENAME = QStringLiteral("qrc:/src/ui/main.qml");
const QString PERSON_QML_SRC_FILENAME = QStringLiteral("qrc:/src/ui/Person.qml");
const QString LEADER_CHOICE_SCREEN = QStringLiteral("chracterChoiceWindow");
const QString BATTLE_SCREEN = QStringLiteral("battleWindowScreen");
const QString GAME_CANVAS = QStringLiteral("gameCanvas");
const QString LEADER_CHOICE_BTN = QStringLiteral("btnRomanLeader");
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
    if (!engine->rootObjects().empty())
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
    qint16 idx = 0;
    for(auto && unit : m_playerUnits)
    {
        auto position = unit->getPosition();
        auto width = unit->getWidth();
        auto height = unit->getHeight();
        if ((x >= position.x() - static_cast<int>(width / 2)) && (x <= position.x() + static_cast<int>(width / 2)))
        {
            if ((y >= position.y() - static_cast<int>(height / 2)) && (y <= position.y() + static_cast<int>(height / 2)))
            {
                personIdx = idx;
                break;
            }
        }
        ++idx;
    }
    return personIdx;
}

qint16 Ductoris::checkIfEnemyClicked(int x, int y) const
{
    qint16 enemyIdx = -1;
    //check if under x, y position is a enemy unit that can be attacked
    return enemyIdx;
}

Ductoris *Ductoris::getInstance()
{
    if (!Ductoris::m_ductorisGame)
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
    std::unique_ptr<ArmyFactory> factory{nullptr};
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
    if (factory)
    {
        std::shared_ptr<Person> leader(factory->createLeader());
        m_leaderUnit = leader;
        m_playerUnits.push_back(std::move(leader));
    }

}

void Ductoris::onGameCanvasClicked(int x, int y, int mouseBtn)
{
    //for now a simple placeholder
    if (mouseBtn == Qt::LeftButton) // left button clicked - select or move
    {
        if (m_unitSelected)
        {
            //move selected unit
            if (!m_selectedUnit.expired()) // make sure not a dangling pointer
            {
                auto selectedUnit = m_selectedUnit.lock();
                selectedUnit->move(x, y);
            }
        }
        else
        {
            auto personIdx = checkIfSelectedAUnit(x, y);
            if (personIdx >= 0)
            {
                m_selectedUnit = m_playerUnits[personIdx];
                m_unitSelected = true;
            }
        }
    }
    else if (mouseBtn == Qt::RightButton) // right button clicked - attack
    {
        if (m_unitSelected && !m_selectedUnit.expired())
        {
            //attack
            auto enemyIdx = checkIfEnemyClicked(x, y);
            if (enemyIdx >= 0)
            {
                auto selectedUnit = m_selectedUnit.lock();
                selectedUnit->attack(m_enemyUnits[enemyIdx]);
            }
        }
    }
}

void Ductoris::onGameStarted()
{
    QObject* window = m_engine->rootObjects().first();
    auto gameCanvas = window->findChild<QQuickItem*>(GAME_CANVAS);
    if (gameCanvas && m_leaderUnit.lock())
    {
        QQmlComponent leaderUiComponent(m_engine.get(), QUrl(PERSON_QML_SRC_FILENAME));
        if ( leaderUiComponent.status() == QQmlComponent::Ready)
        {
            std::unique_ptr<QQuickItem> leaderUiItem(qobject_cast<QQuickItem*>(leaderUiComponent.create()));
            leaderUiItem->setParentItem(gameCanvas);
            leaderUiItem->setSize(QSize(100, 100));

            QQuickItem* personRotated_90 = qobject_cast<QQuickItem*>(leaderUiComponent.create());
            personRotated_90->setParentItem(gameCanvas);
            personRotated_90->setSize(QSize(100, 100));

            QQuickItem* personRotated_180 = qobject_cast<QQuickItem*>(leaderUiComponent.create());
            personRotated_180->setParentItem(gameCanvas);
            personRotated_180->setSize(QSize(100, 100));

            QQuickItem* personRotated_270 = qobject_cast<QQuickItem*>(leaderUiComponent.create());
            personRotated_270->setParentItem(gameCanvas);
            personRotated_270->setSize(QSize(100, 100));

            QQuickItem* personRotated_355 = qobject_cast<QQuickItem*>(leaderUiComponent.create());
            personRotated_355->setParentItem(gameCanvas);
            personRotated_355->setSize(QSize(100, 100));

            QQmlProperty::write(leaderUiItem.get(), "gameCanvasWidth", gameCanvas->width());
            QQmlProperty::write(leaderUiItem.get(), "gameCanvasHeight", gameCanvas->height());
            QQmlProperty::write(personRotated_90, "gameCanvasWidth", gameCanvas->width());
            QQmlProperty::write(personRotated_90, "gameCanvasHeight", gameCanvas->height());
            QQmlProperty::write(personRotated_180, "gameCanvasWidth", gameCanvas->width());
            QQmlProperty::write(personRotated_180, "gameCanvasHeight", gameCanvas->height());
            QQmlProperty::write(personRotated_270, "gameCanvasWidth", gameCanvas->width());
            QQmlProperty::write(personRotated_270, "gameCanvasHeight", gameCanvas->height());
            QQmlProperty::write(personRotated_355, "gameCanvasWidth", gameCanvas->width());
            QQmlProperty::write(personRotated_355, "gameCanvasHeight", gameCanvas->height());

            int x = static_cast<int>(gameCanvas->width() / 2) - static_cast<int>(leaderUiItem->width() / 2);
            int y = static_cast<int>(gameCanvas->height() / 2) - static_cast<int>(leaderUiItem->height() / 2);
            leaderUiItem->setPosition(QPoint(x, y));
            personRotated_90->setPosition((QPoint(x + 100, y)));
            personRotated_180->setPosition((QPoint(x, y + 100)));
            personRotated_270->setPosition((QPoint(x + 100, y + 100)));
            personRotated_355->setPosition((QPoint(x + 200, y)));
            personRotated_90->setRotation(90);
            personRotated_180->setRotation(180);
            personRotated_270->setRotation(270);
            personRotated_355->setRotation(355);
            auto leaderUnit = m_leaderUnit.lock();
            leaderUnit->setUiItem(leaderUiItem);
            m_selectedUnit = m_leaderUnit.lock();
            m_unitSelected = true;
        }
    }

}

void Ductoris::onExitGame()
{
    m_playerUnits.clear();
    m_enemyUnits.clear();
}




