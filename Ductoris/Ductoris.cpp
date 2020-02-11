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
    return true;
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
            //sprite size will be read from config file later
            const QSize spriteSize{100, 100};
            std::unique_ptr<QQuickItem> leaderUiItem(qobject_cast<QQuickItem*>(leaderUiComponent.create()));
            leaderUiItem->setParentItem(gameCanvas);
            leaderUiItem->setSize(spriteSize);

            QQuickItem* personRotated = qobject_cast<QQuickItem*>(leaderUiComponent.create());
            personRotated->setParentItem(gameCanvas);
            personRotated->setSize(spriteSize);

            QQmlProperty::write(leaderUiItem.get(), "gameCanvasWidth", gameCanvas->width());
            QQmlProperty::write(leaderUiItem.get(), "gameCanvasHeight", gameCanvas->height());
            QQmlProperty::write(personRotated, "gameCanvasWidth", gameCanvas->width());
            QQmlProperty::write(personRotated, "gameCanvasHeight", gameCanvas->height());

            const QPointF personArmPosition(0.25 * spriteSize.width(), spriteSize.height() * 0.4); // arm position in person coordinates system
            const QSizeF personArmSize(0.1 * spriteSize.width(), 0.4 * spriteSize.height()); //arm holding the weapon has a separate sprite which is subsprite of person Sprite
            const QSizeF weaponSize(0.1 * spriteSize.width(), spriteSize.height());
            const qreal rotation = 0.0;

            // in person's arm local coordinates system - its centered so that it fits evenly
            QPointF weaponPersonAnchor(static_cast<int>(personArmSize.width() / 2) -
                                      static_cast<int>(weaponSize.width() / 2),
                                      personArmSize.height() / 2);
            //transform it to person coordinates system
            weaponPersonAnchor.setX(weaponPersonAnchor.x() + personArmPosition.x());
            weaponPersonAnchor.setY(weaponPersonAnchor.y() + personArmPosition.y());


            QQmlProperty::write(leaderUiItem.get(), "primaryWeaponAnchorPoint", weaponPersonAnchor);
            QQmlProperty::write(leaderUiItem.get(), "weaponSize", weaponSize);
            QQmlProperty::write(personRotated, "primaryWeaponAnchorPoint", weaponPersonAnchor);
            QQmlProperty::write(personRotated, "weaponSize", weaponSize);

            int x = static_cast<int>(gameCanvas->width() / 2) - static_cast<int>(leaderUiItem->width() / 2);
            int y = static_cast<int>(gameCanvas->height() / 2) - static_cast<int>(leaderUiItem->height() / 2);
            personRotated->setPosition(QPoint(x, y));
            leaderUiItem->setPosition((QPoint(x + static_cast<int>(spriteSize.width()), y - spriteSize.height())));
            leaderUiItem->setZ(1);

            personRotated->setRotation(rotation);
            leaderUiItem->setRotation(45);
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




