#include "State.hpp"
#include <Core/ResourceManager.hpp>

void EditorState::OnInitialize() {
    dt::Scene* scene = AddScene(new dt::Scene("editorScene"));

    dt::ResourceManager::Get()->AddResourceLocation("", "FileSystem", true);
    Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    Ogre::FontManager::getSingleton().load("DejaVuSans", "General");

    dt::Node* camnode = scene->AddChildNode(new dt::Node("camnode"));
    camnode->SetPosition(Ogre::Vector3(0, 0, 10));
    camnode->AddComponent(new dt::CameraComponent("cam"))->LookAt(Ogre::Vector3(0, 0, 0));

    dt::Node* textnode = scene->AddChildNode(new dt::Node("textnode"));
    dt::TextComponent* textcomp = textnode->AddComponent(new dt::TextComponent("Hello World", "textnode"));
    textcomp->SetBackgroundMaterial("TextOverlayBackground");
    textcomp->SetColor(Ogre::ColourValue::White);
    textcomp->SetFont("DejaVuSans");
    textcomp->SetFontSize(24);
    textcomp->SetPadding(Ogre::Vector2(20, 20));
}

void EditorState::UpdateStateFrame(double simulation_frame_time) {
}
