#ifndef DROPSYSTEM_HPP
#define DROPSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../EventManager/EventManager.hpp"
#include "../Events/GroupDeathEvent.hpp"
#include "../Components/DropComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/UpgradeComponent.hpp"
#include "../Components/CircleColliderComponent.hpp"

class DropSystem : public System {
    public:
        DropSystem() {
            RequireComponent<DropComponent>();
        }
        void SubscribeToGroupDeathEvent(std::unique_ptr<EventManager>& eventManager) {
            eventManager->SubscribeToEvent<GroupDeathEvent, DropSystem>(this,
                &DropSystem::OnGroupDeath);
        }

        void OnGroupDeath(GroupDeathEvent& e) {
            if (e.a.HasComponent<DropComponent>()) {
                auto dropBase = e.a.GetComponent<DropComponent>();
                auto transform = e.a.GetComponent<TransformComponent>();
                std::cout << "[DROPSYSTEM] La entidad " << e.a.GetId() << " hace un drop\n";
                Entity drop = e.a.registry->CreateEntity();
                drop.AddComponent<SpriteComponent>(dropBase.textureId, dropBase.width,
                    dropBase.height, dropBase.srcRect.x, dropBase.srcRect.y);
                drop.AddComponent<UpgradeComponent>(dropBase.upgrade, dropBase.increase);
                drop.AddComponent<TransformComponent>(transform.position);
                drop.AddComponent<CircleColliderComponent>(dropBase.radius, dropBase.width,
                    dropBase.height);
                drop.AddComponent<HealthComponent>(1, 0);
                e.a.registry->AddEntityToSystems(drop);
            }
        }
};

#endif // DROPSYSTEM_HPP