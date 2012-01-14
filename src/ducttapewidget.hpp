#ifndef DUCTTAPEWIDGET_HPP
#define DUCTTAPEWIDGET_HPP

#include <Core/Root.hpp>
#include <Scene/Game.hpp>
#include <Scene/State.hpp>
#include <Graphics/DisplayManager.hpp>

#include <QtCore>
#include <QtGui>
//#include <QtDeclarative>

#ifndef Q_WS_WIN
#include <QX11Info>
#endif

class DucttapeWidget : public QWidget /*QDeclarativeView*/ {
    Q_OBJECT
public:
    DucttapeWidget(dt::Game* game, QWidget* parent = 0);
    ~DucttapeWidget();

    void Run(dt::State* state, int argc, char** argv);

public slots:

    void updateQt(double d);

protected:
    /*void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *e);
    void timerEvent(QTimerEvent *e);
    void setRootObject(QObject *obj);
    bool eventFilter(QObject *watched, QEvent *e);*/

private:
    dt::Game* mGame;
    dt::DisplayManager* mDisplay;
};

class DucttapeThread : public QThread {
public:
    DucttapeThread(DucttapeWidget* dt, int argc, char** argv);
    void run();

private:
    DucttapeWidget* mDt;
    int mArg;
    char** mArgv;
};

class DucttapeThread2 : public QThread {
public:
    void run();
};

#endif // DUCTTAPEWIDGET_HPP
