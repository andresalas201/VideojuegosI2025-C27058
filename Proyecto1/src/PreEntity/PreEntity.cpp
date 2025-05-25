#include "PreEntity.hpp"

PreEntity::PreEntity(int groupNumber, int groupLeft, int spawnWait) {
    this->groupNumber = groupNumber;
    this->groupLeft = groupLeft;
    this->spawnWait = spawnWait;
}

void PreEntity::SetAnimation(int numFrames, int frameRate, bool isLoop) {
    this->numFrames = numFrames;
    this->frameSpeedRate = frameRate;
    this->isLoop = isLoop;
}

void PreEntity::SetAttack(int damage, int radius, int width, int height,
                        const std::string& textureId, int srcX, int srcY,
                        glm::vec2 velVec, std::string soundFile,
                        std::string hitSoundFilePath, int maxShots, bool left,
                        glm::vec2 scale, int shotQuantity) {
    this->attackDamage = damage;
    this->attackRadius = radius;
    this->attackWidth = width;
    this->attackHeight = height;
    this->attackTextureId = textureId;
    // ... rest of implementation
}

void PreEntity::SetCollider(int radius, int width, int height) {
    // implementation
}

void PreEntity::SetEnemy(sol::function update) {
    // implementation
}

void PreEntity::SetHealth(int health, int damage) {
    // implementation
}

void PreEntity::SetBody(glm::vec2 velocity) {
    // implementation
}

void PreEntity::SetSound(const std::string& soundPath) {
    // implementation
}

void PreEntity::SetSprite(const std::string& textureId, int srcRectX,
                         int srcRectY, int hitRectX, int hitRectY,
                         int upX, int downX, int hitUpX, int hitDownX,
                         int deathRectX, int deathRectY) {
    // implementation
}

void PreEntity::SetTransform(glm::vec2 position, glm::vec2 scale, double rotation) {
    // implementation
}

void PreEntity::SetDrop(int increase, const std::string& path) {
    // implementation
}

void PreEntity::CreateEntity(std::unique_ptr<Registry> registry) {
    // implementation
}