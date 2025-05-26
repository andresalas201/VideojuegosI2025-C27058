#ifndef PREENTITY_HPP
#define PREENTITY_HPP

#include <string>
#include <memory>
#include <glm/glm.hpp>
#include <sol/sol.hpp>
#include <SDL2/SDL.h>

class Registry;

class PreEntity {
    private:    
        int numFrames;
        int currentFrame;
        int frameSpeedRate;
        bool isLoop;
        int startTime;
        int attackDamage;
        int attackRadius;
        int attackWidth;
        int attackHeight;
        std::string attackTextureId;
        int radius;
        int width;
        int height;
        SDL_Rect attackSrcRect;
        glm::vec2 attackVelocity;
        glm::vec2 velocity;
        std::string shootSoundFilePath;
        std::string hitSoundFilePath;
        glm::vec2 attackScale;
        int maxShots;
        int currentShots;
        bool left;
        int attackNumFrames;
        int attackFrameSpeedRate;
        bool isAttackLoop;
        sol::function attackUpdate;
        glm::vec2 scale;
        int lastShotTick;
        int shotQuantity;
        bool isDead;
        int health;
        std::string soundName;
        int damage;
        SDL_Rect srcRect;
        std::string textureId;
        SDL_Rect hitSrcRect;
        int upX;
        int downX;
        int hitUpX;
        int hitDownX;
        SDL_Rect deathRect;
        double rotation;
        int increase;
        std::string upgradeSprite;
        SDL_Rect upgradeSrcRect;
        int upgradeWidth;
        int upgradeHeight;
        int upgradeRotation;
        std::string upgradePath;
        std::string upgradeSound;

        bool hasAttack;
        bool hasAnimation;
        bool hasDrop;
        bool hasSound;

        int spawnX;
        int spawnY;
    public:

        int groupNumber;
        int groupLeft;
        int spawnMax;
        int spawnWait;
        int spawnedAmount;
        sol::function update;
        int lastSpawnTick;

        PreEntity(int groupNumber, int groupLeft = 1, int spawnWait = 1);
        void SetAnimation(int numFrames = 1, int frameRate = 1, bool isLoop = true);
        void SetAttack(int damage = 1, int radius = 0, int width = 0, int height = 0,
            const std::string& textureId = "none", int srcX = 0, int srcY = 0,
            glm::vec2 velVec = glm::vec2(0.0, 0.0), std::string soundFile = "",
            std::string hitSoundFilePath = "none", int maxShots = 0, bool left = false,
            glm::vec2 scale = glm::vec2(1.0, 1.0), int shotQuantity = 1,
            sol::function update = sol::lua_nil, int numFrames = 1,
            int frameSpeedRate = 1, bool isLoop = true);
        void SetCollider(int radius = 0, int width = 0, int height = 0);
        void SetEnemy(sol::function update = sol::lua_nil);
        void SetHealth(int health = 1, int damage = 1);
        void SetBody(glm::vec2 velocity = glm::vec2(0.0, 0.0));
        void SetSound(const std::string& soundPath = "none");
        void SetSprite(const std::string& textureId = "none", int srcRectX = 0,
            int srcRectY = 0, int hitRectX = 0, int hitRectY = 0,
            int upX = 0, int downX = 0, int hitUpX = 0, int hitDownX = 0,
            int deathRectX = 0, int deathRectY = 0);
        void SetTransform(glm::vec2 scale = glm::vec2(1.0, 1.0), double rotation = 0.0);
        void SetDrop(int increase = 1, const std::string& path = "none", int width = 0,
            int height = 0, double rotation = 0, const std::string& textureId = "none",
            int x = 0, int y = 0, const std::string& soundName = "none");
        void CreateEntity(std::unique_ptr<Registry>& registry);
        void SetSpawn(int x, int y);


};

#endif // PREENTITY_HPP