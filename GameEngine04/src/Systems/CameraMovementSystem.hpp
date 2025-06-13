#ifndef CAMERAMOVEMENTSYSTEM_HPP
#define CAMERAMOVEMENTSYSTEM_HPP

#include <SDL2/SDL.h>
#include "../ECS/ECS.hpp"
#include "../Components/CameraFollowComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Game/Game.hpp"


class CameraMovementSystem : public System {

    public:
        CameraMovementSystem() {
            RequireComponent<CameraFollowComponent>();
            RequireComponent<TransformComponent>();
        }

        void Update (SDL_Rect& camera) {
            for (auto entity : GetSystemEntities()) {
                const auto transf = entity.GetComponent<TransformComponent>();
                if (transf.position.x + (camera.w / 2) < 
                    static_cast<float>(Game::GetInstance().mapWidth)) {
                    camera.x = static_cast<int>(transf.position.x) - (camera.w / 2);
                }

                if (transf.position.y + (camera.h / 2) < 
                    static_cast<float>(Game::GetInstance().mapHeight)) {
                    camera.y = static_cast<int>(transf.position.y) - (camera.h / 2);
                }

                camera.x = camera.x < 0 ? 0 : camera.x;
                camera.y = camera.y < 0 ? 0 : camera.y;
            }
        }

};


#endif // CAMERAMOVEMENTSYSTEM_HPP