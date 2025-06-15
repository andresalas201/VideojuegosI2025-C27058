#ifndef ANIMATIONMANAGER_HPP
#define ANIMATIONMANAGER_HPP

#include <map>
#include <string>

struct AnimationData {
    std::string textureId;
    int width;
    int height;
    int numFrames;
    int frameSpeedRate;
    bool isLoop;

    AnimationData(const std::string& textureId = "none",
        int width = 0, int height = 0, int numFrames = 1,
        int frameSpeedRate = 1, bool isLoop = true) {
        this->textureId = textureId;
        this->width = width;
        this-> height = height;
        this->numFrames = numFrames;
        this->frameSpeedRate = frameSpeedRate;
        this->isLoop = isLoop;
    }
};

class AnimationManager {
    private:
        std::map<std::string, AnimationData> animations;
    public:
        AnimationManager();
        ~AnimationManager();
        void AddAnimation( const std::string& animationId,
            const std::string& textureId, int width, int height,
            int numFrames, int frameSpeedRate,bool isLoop);
        AnimationData GetAnimation(const std::string& animationId);

};

#endif // ANIMATIONMANAGER_HPP