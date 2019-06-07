#ifndef DUCTORIS_H
#define DUCTORIS_H
#include <QObject>


class Ductoris : public QObject
{
    Q_OBJECT
public:
    ~Ductoris();
    static Ductoris *getInstance();
public slots:
    void onUnitMove(int x, int y);
    void onSelectUnit();
    void onUnitAttack();
    void onNewUnitCreate();
    void onUnitAttacked();
private:
    Ductoris();
    Ductoris(const Ductoris &other) = delete;
    Ductoris& operator=(const Ductoris &other) = delete;

    void initilize();

    static Ductoris *m_ductoriusGame;
    bool m_initialized{false};

};

#endif // DUCTORIS_H
