#include "PreEntity.hpp"

#include "../ECS/ECS.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/AttackComponent.hpp"
#include "../Components/CircleColliderComponent.hpp"
#include "../Components/DropComponent.hpp"
#include "../Components/EnemyComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/SoundComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/BossComponent.hpp"
#include "../Components/ScriptComponent.hpp"

PreEntity::PreEntity(int groupNumber, int groupLeft, int spawnWait) {
    this->groupNumber = groupNumber;
    this->groupLeft = groupLeft;
    this->spawnWait = spawnWait;
    this->hasAttack = false;
    this->hasAnimation = false;
    this->hasSound = false;
    this->spawnedAmount = 0;
    this->lastSpawnTick = 0;
    this->spawnMax = groupLeft;
    this->isBoss = false;
}

void PreEntity::SetAnimation(int numFrames, int frameRate, bool isLoop) {
    this->numFrames = numFrames;
    this->frameSpeedRate = frameRate;
    this->isLoop = isLoop;
    this->hasAnimation = true;
}

void PreEntity::SetAttack(int damage, int radius, int width, int height,
    const std::string& textureId, int srcX, int srcY, glm::vec2 velVec,
    std::string soundFile, std::string hitSoundFilePath, int maxShots, bool left,
    glm::vec2 scale, int shotQuantity, sol::function update, int numFrames, 
    int frameSpeedRate, bool isLoop) {

    this->attackDamage = damage;
    this->attackRadius = radius;
    this->attackWidth = width;
    this->attackHeight = height;
    this->attackTextureId = textureId;
    this->attackSrcRect = {srcX, srcY, width, height};
    this->attackVelocity = velVec;
    this->shootSoundFilePath = soundFile;
    this->hitSoundFilePath = hitSoundFilePath;
    this->maxShots = maxShots;
    this->left = left;
    this->shotQuantity = shotQuantity;
    this->attackScale = scale;
    this->hasAttack = true;
    this->attackUpdate = update;
    this->attackNumFrames = numFrames;
    this->attackFrameSpeedRate = frameSpeedRate;
    this->isAttackLoop = isLoop;
}

void PreEntity::SetCollider(int radius, int width, int height) {
    this->radius = radius;
    this->width = width;
    this->height = height;
}

void PreEntity::SetEnemy(sol::function update) {
    this->update = update;
}

void PreEntity::SetHealth(int health, int damage) {
    this->health = health;
    this->damage = damage;
}

void PreEntity::SetBody(glm::vec2 velocity) {
    this->velocity = velocity;
}

void PreEntity::SetSound(const std::string& soundPath) {
    this->soundName = soundPath;
    this->hasSound = true;
}

void PreEntity::SetSprite(const std::string& textureId, int srcRectX,
    int srcRectY, int hitRectX, int hitRectY,
    int upX, int downX, int hitUpX, int hitDownX,
    int deathRectX, int deathRectY) {
    
    this->textureId = textureId;
    this->srcRect = {srcRectX, srcRectY, this->width, this->height};
    this->hitSrcRect = {hitRectX, hitRectY, this->width, this->height};
    this->upX = upX;
    this->downX = downX;
    this->hitUpX = hitUpX;
    this->hitDownX = hitDownX;
    this->deathRect = {deathRectX, deathRectY, this->width, this->height};
}

void PreEntity::SetTransform(glm::vec2 scale, double rotation) {
    this->scale = scale;
    this->rotation = rotation;
}

void PreEntity::SetDrop(int increase, sol::function upgrade, int width, int height,
    double rotation, const std::string& textureId, int x, int y,
    const std::string& soundName, int radius) {

    this->increase = increase;
    this->upgradeFunction = upgrade;
    this->upgradeWidth = width;
    this->upgradeHeight = height;
    this->upgradeSrcRect = {x, y, width, height};
    this->upgradeSprite = textureId;
    this->upgradeSound = soundName;
    this->upgradeRotation = rotation;
    this->upgradeRadius = radius;
    this->hasDrop = true;

}

void PreEntity::CreateEntity(std::unique_ptr<Registry>& registry) {
    Entity newEntity = registry->CreateEntity();
    newEntity.AddComponent<CircleColliderComponent>(this->radius, this->width, this->height);
    newEntity.AddComponent<EnemyComponent>(this->update, this->groupNumber, this, this->health);
    newEntity.AddComponent<ScriptComponent>(this->update);
    newEntity.AddComponent<HealthComponent>(this->health, this->damage);
    newEntity.AddComponent<RigidBodyComponent>(this->velocity);
    newEntity.AddComponent<SpriteComponent>(this->textureId, this->width, this->height,
        this->srcRect.x, this->srcRect.y, this->hitSrcRect.x, this->hitSrcRect.y, this->upX,
        this->downX, this->hitUpX, this->hitDownX, this->deathRect.x, this->deathRect.y);
    newEntity.AddComponent<TransformComponent>(
        glm::vec2(static_cast<double>(this->spawnX), static_cast<double>(this->spawnY)),
        this->scale, this->rotation);
    if (hasDrop) {
        newEntity.AddComponent<DropComponent>(this->increase, this->upgradeFunction,
        this->upgradeWidth, this->upgradeHeight, this->upgradeRotation, this->upgradeSprite,
        this->upgradeSrcRect.x, this->upgradeSrcRect.y, this->upgradeSound, this->upgradeRadius);
    }
    if (hasSound) newEntity.AddComponent<SoundComponent>(this->soundName);
    if (hasAnimation) {
        newEntity.AddComponent<AnimationComponent>(this->numFrames, this->frameSpeedRate,
            this->isLoop);
    }
    if (hasAttack) {
        newEntity.AddComponent<AttackComponent>(this->attackDamage, this->attackRadius,
            this->attackWidth, this->attackHeight, this->attackTextureId, this->attackSrcRect.x,
            this->attackSrcRect.y, this->attackVelocity, this->shootSoundFilePath,
            this->hitSoundFilePath, this->maxShots, this->left, this->attackScale,
            this->shotQuantity, this->attackNumFrames, this->attackFrameSpeedRate,
            this->isAttackLoop, this->attackUpdate);
    }
    if (isBoss) {
        newEntity.AddComponent<BossComponent>();
    }
    registry->AddEntityToSystems(newEntity);
    this->lastSpawnTick = SDL_GetTicks();
}

void PreEntity::SetSpawn(int x, int y) {
    this->spawnX = x;
    this->spawnY = y;
}

void PreEntity::SetBoss(int x, int y) {
    this->isBoss = true;
    this->bossX = x;
    this->bossY = y;
}

//TODO(any) Crear scripts para diferentes tipos de enemigos
//TODO Crear scripts para balas