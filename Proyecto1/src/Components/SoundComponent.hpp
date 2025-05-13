#ifndef SOUNDCOMPONENT_HPP
#define SOUNDCOMPONENT_HPP

#include <string>

struct SoundComponent {
    
    std::string soundPath;

    SoundComponent(const std::string& soundPath = "none") : soundPath(soundPath) {}

};

#endif // SOUNDCOMPONENT_HPP