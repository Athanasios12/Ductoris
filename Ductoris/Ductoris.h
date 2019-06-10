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
    void onGameCanvasClicked(int x, int y, int mouseBtn);
    void onGameStarted();
    void onExitGame();
signals:
    void setPersonMovementData(int newX, int newY, int time, int rotation);
private:
    Ductoris();
    Ductoris(const Ductoris &other) = delete;
    Ductoris& operator=(const Ductoris &other) = delete;

    void initilize();
    // this will be moved to person class - when canvas clicked, check if person selected , if true this person calculates its new
    //position, rotation and time of movement based on its stats
    void movePerson(int x, int y);
    //if not selected check if player clicked on a person and select it for later movement
    Person *checkIfSelectedAPerson(int x, int y) const;
    void attack(); // attack button pressed - perform attack if selected a person

    static Ductoris *m_ductorisGame;
    bool m_initialized{false};
    bool m_personSelected{false};
    std::weak_ptr<Person> m_selectedPerson{nullptr};
    std::vector<std::shared_ptr<Person>> m_allUnits;
    std::unique_ptr<QQmlApplicationEngine> m_engine{nullptr};

};

#endif // DUCTORIS_H
