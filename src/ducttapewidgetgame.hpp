#ifndef DUCTTAPEWIDGETGAME_HPP
#define DUCTTAPEWIDGETGAME_HPP

#include <Core/Root.hpp>
#include <Scene/Game.hpp>

class GameNonCont : public dt::Game {
    Q_OBJECT
public:
    GameNonCont();

public slots:
    void Init(dt::State* state, int argc, char** argv);
    void Run();

    bool IsShutdown();
private:
    dt::Root* mRoot;

    sf::Clock mClock1;
    sf::Clock mClock2;

    double mFrameTime;
    double mAccumulator;
};

#endif // DUCTTAPEWIDGETGAME_HPP
