#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>
#include <iostream>
#include <glm/glm.hpp>

#include "../ECS/ECS.hpp"
#include "../Game/Game.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/SpriteComponent.hpp"

bool IsActionActivated(const std::string& action) {
    return Game::GetInstance().controllerManager->IsActionActivated(action);
}

void SetVelocity(Entity entity, float x, float y) {
    auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
    rigidBody.velocity.x = x;
    rigidBody.velocity.y = y;
}

std::tuple<int, int> GetVelocity(Entity entity) {
    const auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
    return {
        static_cast<int>(rigidBody.velocity.x),
        static_cast<int>(rigidBody.velocity.y)
    };
}

// TransformComponent

std::tuple<int, int> GetPosition(Entity entity) {
    const auto& transform = entity.GetComponent<TransformComponent>();
    return {
        static_cast<int>(transform.position.x),
        static_cast<int>(transform.position.y)
    };
}

void setPosition(Entity entity, int x, int y) {
    auto& transform = entity.GetComponent<TransformComponent>();
    transform.position.x = x;
    transform.position.y = y;
}

std::tuple<int, int> GetSize(Entity entity) {
    const auto& sprite = entity.GetComponent<SpriteComponent>();
    const auto& transform = entity.GetComponent<TransformComponent>();

    int width = sprite.width * transform.scale.x;
    int height = sprite.height * transform.scale.y;
    return {width, height};
}

std::string GetTag(Entity entity) {
    return entity.GetComponent<TagComponent>().tag;
}

// Scenes

void GoToScene(const std::string& sceneName) {
    Game::GetInstance().sceneManager->SetNextScene(sceneName);
    Game::GetInstance().sceneManager->StopScene();
}

//* Collisions

bool LeftCollision(Entity e, Entity other) {
    const auto& eCollider = e.GetComponent<BoxColliderComponent>();
    const auto& eTransform = e.GetComponent<TransformComponent>();
    const auto& oCollider = other.GetComponent<BoxColliderComponent>();
    const auto& oTransform = other.GetComponent<TransformComponent>();

    float eX = eTransform.previousPosition.x;
    float eY = eTransform.previousPosition.y;
    float eH = static_cast<float>(eCollider.height);

    float oX = oTransform.previousPosition.x;
    float oY = oTransform.previousPosition.y;
    float oH = static_cast<float>(oCollider.height);

    return {
        eY < eY + eH &&
        oY + oH > eY &&
        oX < eX
    };
}

bool RightCollision(Entity e, Entity other) {
    const auto& eCollider = e.GetComponent<BoxColliderComponent>();
    const auto& eTransform = e.GetComponent<TransformComponent>();
    const auto& oCollider = other.GetComponent<BoxColliderComponent>();
    const auto& oTransform = other.GetComponent<TransformComponent>();

    float eX = eTransform.previousPosition.x;
    float eY = eTransform.previousPosition.y;
    float eH = static_cast<float>(eCollider.height);

    float oX = oTransform.previousPosition.x;
    float oY = oTransform.previousPosition.y;
    float oH = static_cast<float>(oCollider.height);

    return {
        eY < eY + eH &&
        oY + oH > eY &&
        oX > eX
    };
}

#endif // LUABINDING_HPP