#ifndef SOUNDCOMPONENT_HPP
#define SOUNDCOMPONENT_HPP

#include <string>

struct SoundComponent {
    
    std::string soundPath;

    SoundComponent(const std::string& soundPath = "") : soundPath(soundPath) {}

};

#endif // SOUNDCOMPONENT_HPP