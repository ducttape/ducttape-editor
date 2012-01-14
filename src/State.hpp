#ifndef STATE_HPP
#define STATE_HPP

#include <Config.hpp>

#include <Core/Root.hpp>
#include <Graphics/TextComponent.hpp>
#include <Graphics/CameraComponent.hpp>
#include <Scene/Scene.hpp>
#include <Scene/StateManager.hpp>

#include <OgreFontManager.h>

class EditorState: public dt::State {
    Q_OBJECT
public:
    void OnInitialize();
    void UpdateStateFrame(double simulation_frame_time);
};

#endif // STATE_HPP
