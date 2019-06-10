#ifndef DUCTORIS_H
#define DUCTORIS_H
#include <QObject>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <memory>

class Ductoris : public QObject
{
    Q_OBJECT
public:
    ~Ductoris();
    static Ductoris *getInstance();
public slots:
    void onGameCanvasClicked(int x, int y, int mouseBtn);
private:
    Ductoris();
    Ductoris(const Ductoris &other) = delete;
    Ductoris& operator=(const Ductoris &other) = delete;

    void initilize();

    static Ductoris *m_ductorisGame;
    bool m_initialized{false};
    std::unique_ptr<QQmlApplicationEngine> m_engine{nullptr};

};

#endif // DUCTORIS_H
