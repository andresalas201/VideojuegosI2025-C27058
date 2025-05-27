#ifndef CLEANENEMIESSYSTEM_HPP
#define CLEANENEMIESSYSTEM_HPP

#include "../ECS/ECS.hpp"
#include "../Components/EnemyComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"

class CleanEnemiesSystem : public System {
    private:
        int height;
        int width;

        void CleanEnemyGroups(std::unique_ptr<Registry>& registry) {
            bool clean;
            for (long unsigned int i = 0; i < registry->enemiesToSpawn.size();
                i++) {
                
                clean = false;
                for (auto& entity : GetSystemEntities()) {
                    if(entity.GetComponent<EnemyComponent>().group ==
                        registry->enemiesToSpawn[i].groupNumber) {
                            clean = true;
                            break;
                        }
                }
                if (!clean) {
                    std::cout << "[CLEANENEMIESSYSTEM] Se elimina el grupo " <<
                        registry->enemiesToSpawn[i].groupNumber << std::endl;
                    registry->enemiesToSpawn.erase(registry->enemiesToSpawn.begin() + i);
                    i--;
                }
            }
        }

        void CleanHiddenEnemies() {
            for (auto entity : GetSystemEntities()) {
                Entity& a = entity;
                auto sprite = a.GetComponent<SpriteComponent>();
                auto transform = a.GetComponent<TransformComponent>();
                if ((transform.position.x + (sprite.width * transform.scale.x)) < 0 ||
                    (transform.position.y + (sprite.height * transform.scale.y)) < 0 ||
                    (transform.position.y + (sprite.height * transform.scale.y)) > height) {
                    std::cout << "[CLEANENEMIESSYSTEM] Se elimina la entidad " << a.GetId()
                        << " debido a que sale de pantalla\n";
                    a.Kill();
                }
            }
        }

    public:
        CleanEnemiesSystem() {
            RequireComponent<EnemyComponent>();
            RequireComponent<TransformComponent>();
            RequireComponent<SpriteComponent>();
        }

        void SetParameter(int height, int width) {
            this->height = height;
            this->width = width;
        }

        void Update(std::unique_ptr<Registry>& registry) {
            CleanHiddenEnemies();
            CleanEnemyGroups(registry);
        }
};

#endif // CLEANENEMIESSYSTEM_HPP