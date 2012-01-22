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

#include "ducttapewidgetgame.hpp"

class DucttapeWidget : public QWidget /*QDeclarativeView*/ {
    Q_OBJECT
public:
    DucttapeWidget(GameNonCont* game, QWidget* parent = 0);
    ~DucttapeWidget();

    void Run(dt::State* state, int argc, char** argv);

protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *e);
    void timerEvent(QTimerEvent *e);
    /*void setRootObject(QObject *obj);
    bool eventFilter(QObject *watched, QEvent *e);*/

private:
    GameNonCont* mGame;
    dt::DisplayManager* mDisplay;
    QBasicTimer mTimer;
};

#endif // DUCTTAPEWIDGET_HPP
