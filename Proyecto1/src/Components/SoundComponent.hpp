#ifndef SOUNDCOMPONENT_HPP
#define SOUNDCOMPONENT_HPP

#include <string>

struct SoundComponent {
    
    std::string soundName;

    SoundComponent(const std::string& soundPath = "none") : soundName(soundPath) {}

};

#endif // SOUNDCOMPONENT_HPP