#ifndef HEALTHBARSYSTEM_HPP
#define HEALTHBARSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/HealthBarComponent.hpp"
#include "../Components/TextComponent.hpp"

class HealthBarSystem : public System {
    public:
        HealthBarSystem() {
            RequireComponent<HealthBarComponent>();
            RequireComponent<TextComponent>();
        }

        void Update() {
            int index = 1;
            for (auto entity : GetSystemEntities()) {
                auto& text = entity.GetComponent<TextComponent>();
                auto healthBar = entity.GetComponent<HealthBarComponent>();
                if (healthBar.health <= 0) text.text = "P" + std::to_string(index) +" Is Dead";
                else text.text = "P" + std::to_string(index) +" Health: " + std::to_string(healthBar.health);
                index++;
            }
        }

        void SetHealth(int health, int player) {
            std::vector<Entity> entities = GetSystemEntities();
            if(player < static_cast<int>(entities.size())) {
                auto& healthBar = entities[player].GetComponent<HealthBarComponent>();
                healthBar.health = health;
            }
        }
};

#endif // HEALTHBARSYSTEM_HPP