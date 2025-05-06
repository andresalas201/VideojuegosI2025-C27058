#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>
#include <iostream>
#include <glm/glm.hpp>

#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"
#include "../Components/RigidBodyComponent.hpp"

bool IsActionActivated(const std::string& action) {
    return Game::GetInstance().controllerManager->IsActionActivated(action);
}

void SetVelocity(Entity entity, float x, float y) {
    auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
    rigidBody.velocity.x = x;
    rigidBody.velocity.y = y;
}

// Scenes

void GoToScene(const std::string& sceneName) {
    Game::GetInstance().sceneManager->SetNextScene(sceneName);
    Game::GetInstance().sceneManager->StopScene();
}

#endif // LUABINDING_HPP