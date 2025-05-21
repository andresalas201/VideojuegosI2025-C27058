#ifndef LUABINDING_HPP
#define LUABINDING_HPP

#include <string>
#include <iostream>
#include <glm/glm.hpp>

#include "../ECS/ECS.hpp"
#include "../AssetManager/AssetManager.hpp"
#include "../Game/Game.hpp"
#include "../Systems/AudioSystem.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/SoundComponent.hpp"
#include "../Components/AttackComponent.hpp"
#include "../Components/FatherComponent.hpp"
#include "../Components/ShotComponent.hpp"

bool IsActionActivated(const std::string& action) {
    return Game::GetInstance().controllerManager->IsActionActivated(action);
}

void SetVelocity(Entity entity, float x, float y) {
    auto& rigidBody = entity.GetComponent<RigidBodyComponent>();
    rigidBody.velocity.x = x;
    rigidBody.velocity.y = y;
}

glm::vec2 CalculatePosition(Entity e, bool left) {
    double direction;
    if (left) direction = -1.0;
    else direction = 1.0;
    glm::vec2 entityPosition = e.GetComponent<TransformComponent>().position;
    int entityWidth = e.GetComponent<SpriteComponent>().width;
    int entityHeight = e.GetComponent<SpriteComponent>().height;
    double x = (entityPosition.x + (entityWidth)) + 
        ((entityWidth) * direction);
    double y = entityPosition.y + (entityHeight / 2);
    glm::vec2 result = glm::vec2(x, y);
    return result;

}

bool CanShoot(AttackComponent* attack) {
    int ticksSinceShot = (SDL_GetTicks() - attack->lastShotTick);
    return ticksSinceShot >= MILLISECS_PER_FRAME * FPS;
}

void Shoot(Entity shooter) {
    if(!shooter.HasComponent<AttackComponent>()) return;
    AttackComponent* attack = &shooter.GetComponent<AttackComponent>();
    if (attack && attack->currentShots < attack->maxShots && CanShoot(attack)) {
        Entity shot = Game::GetInstance().registry->CreateEntity();
        shot.AddComponent<CircleColliderComponent>(attack->radius, attack->width,
            attack->height);
        shot.AddComponent<RigidBodyComponent>(attack->velocity);
        shot.AddComponent<TransformComponent>(CalculatePosition(shooter, attack->left), 
            attack->scale, attack->rotation);
        shot.AddComponent<HealthComponent>(1, attack->damage);
        shot.AddComponent<CircleColliderComponent>(attack->radius, attack->width,
            attack->height);
        shot.AddComponent<SpriteComponent>(attack->textureId, attack->width,
            attack->srcRect.x, attack->srcRect.y);
        shot.AddComponent<SoundComponent>(attack->hitSoundFilePath);
        shot.AddComponent<FatherComponent>(attack);
        shot.AddComponent<ShotComponent>(true, shooter.HasComponent<PlayerComponent>());
        attack->currentShots++;
        attack->lastShotTick = SDL_GetTicks();
        Game::GetInstance().registry->GetSystem<AudioSystem>().playSound(
            Game::GetInstance().assetManager->GetSound(attack->shootSoundFilePath)
        );
        Game::GetInstance().registry->AddEntityToSystems(shot);
    }
}

// Scenes

void GoToScene(const std::string& sceneName) {
    Game::GetInstance().sceneManager->SetNextScene(sceneName);
    Game::GetInstance().sceneManager->StopScene();
}

#endif // LUABINDING_HPP