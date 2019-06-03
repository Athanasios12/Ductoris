#ifndef DUCTORIS_H
#define DUCTORIS_H
#include <QObject>

class Ductoris : public QObject
{
    Q_OBJECT
public:
    ~Ductoris();

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
};

#endif // DUCTORIS_H
