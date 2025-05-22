#ifndef CLEANSHOTSYSTEM_HPP
#define CLEANSHOTSYSTEM_HPP

#include <iostream>

#include "../ECS/ECS.hpp"
#include "../Components/ShotComponent.hpp"
#include "../Components/FatherComponent.hpp"

class CleanShotSystem : public System { 
    private:
        int secondsPerShot;
    
    public:
        CleanShotSystem() {
            RequireComponent<ShotComponent>();
            RequireComponent<FatherComponent>();
            this->secondsPerShot = 0;
        }

        void setSecondsPerShot(int seconds) {
            this->secondsPerShot = seconds;
        }

        void Update(int MILLISECS_PER_FRAME, int FPS, int maxSeconds) {
            Uint32 maxTime = MILLISECS_PER_FRAME * FPS * maxSeconds;
            auto entities = GetSystemEntities();

            for (auto i = entities.begin(); i != entities.end(); i++) {
                Entity a = *i;
                auto& shot = a.GetComponent<ShotComponent>();
                if ((SDL_GetTicks() - shot.shotTime) >= maxTime) {
                    a.GetComponent<FatherComponent>().father->currentShots --;
                    std::cout << "[CLEANSHOTSYSTEM] Se borra el disparo de entidad "
                        << a.GetId() << std::endl;
                    
                    a.Kill();
                }
            }
        }

};

#endif // CLEANSHOTSYSTEM_HPP