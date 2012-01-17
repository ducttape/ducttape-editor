#include "ducttapewidgetgame.hpp"

#include <Scene/StateManager.hpp>
#include <Input/InputManager.hpp>
#include <Graphics/DisplayManager.hpp>
#include <Network/NetworkManager.hpp>

GameNonCont::GameNonCont() :
    Game(),
    mFrameTime(0.001),
    mAccumulator(0.0) {}

void GameNonCont::Init(dt::State* state, int argc, char** argv) {
    mRoot = &dt::Root::GetInstance();

    mRoot->Initialize(argc, argv);
    mRoot->GetStateManager()->SetNewState(state);
    connect(mRoot->GetInputManager(), SIGNAL(WindowClosed()), SLOT(RequestShutdown()));
    //connect BeginFrames to things that need it, like State/Scenes and the PhysicsManager
    connect(this, SIGNAL(BeginFrame(double)), mRoot->GetStateManager(), SIGNAL(BeginFrame(double)), Qt::DirectConnection);
    connect(this, SIGNAL(BeginFrame(double)), (QObject*)mRoot->GetPhysicsManager(),
            SLOT(UpdateFrame(double)), Qt::DirectConnection);

    mClock1.Reset();
    mIsRunning = true;

    mClock2.Reset();
}

void GameNonCont::Run() {
    if(!mIsShutdownRequested) {
        // TIMING
        // TODO: Implement real timing instead of just getting the time difference
        double frame_time = mClock1.GetElapsedTime() / 1000.0;
        mClock1.Reset();

        // Shift states and cancel if none are left
        if(!mRoot->GetStateManager()->ShiftStates())
            return;

        // INPUT
        dt::InputManager::Get()->Capture();

        mAccumulator += frame_time;
        while(mAccumulator >= mFrameTime) {
            mClock2.Reset();
            // SIMULATION
            emit BeginFrame(mFrameTime);


            // NETWORKING
            mRoot->GetNetworkManager()->SendQueuedEvents();

            double real_simulation_time = mClock2.GetElapsedTime() / 1000.0;
            if(real_simulation_time > mFrameTime) {
                // this is bad! the simulation did not render fast enough
                // to have some time left for rendering etc.

                // skip a frame to catch up
                mAccumulator -= mFrameTime;

                mAccumulator -= real_simulation_time;
            }
            mAccumulator -= mFrameTime;
        }
        mRoot->GetDisplayManager()->Render();
    } else {
    mRoot->GetNetworkManager()->DisconnectAll();

    mIsRunning = false;
    mRoot->Deinitialize();
    }
}

bool GameNonCont::IsShutdown() {
    return mIsShutdownRequested;
}
