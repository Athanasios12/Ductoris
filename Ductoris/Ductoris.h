#ifndef DUCTORIS_H
#define DUCTORIS_H
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <memory>
#include <vector>
#include <Person.h>

class Ductoris : public QObject
{
    Q_OBJECT
public:
    ~Ductoris();
    static Ductoris *getInstance();
    bool addNewUnit();
public slots:
    void onChosenLeader(int leaderType);
    void onGameCanvasClicked(int x, int y, int mouseBtn);
    void onGameStarted();
    void onExitGame();
private:
    Ductoris();
    Ductoris(const Ductoris &other) = delete;
    Ductoris& operator=(const Ductoris &other) = delete;

    void initilize();
    qint16 checkIfSelectedAUnit(int x, int y) const;
    qint16 checkIfEnemyClicked(int x, int y) const;
    void attack();

    static Ductoris *m_ductorisGame;
    bool m_initialized{false};
    bool m_unitSelected{false};
    std::weak_ptr<Person> m_selectedUnit;
    std::weak_ptr<Person> m_leaderUnit;
    std::vector<std::shared_ptr<Person>> m_playerUnits;
    std::vector<std::shared_ptr<Person>> m_enemyUnits;
    std::unique_ptr<QQmlApplicationEngine> m_engine{nullptr};

};

#endif // DUCTORIS_H
