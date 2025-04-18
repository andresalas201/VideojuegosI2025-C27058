#ifndef CONTROLLERMANAGER_HPP
#define CONTROLLERMANAGER_HPP

#include <SDL2/SDL.h>

#include <map>
#include <string>

class ControllerManager {
    private:
        std::map<std::string, int> actionKeyName;
        std::map<int, bool> keyDown;

    public:
        ControllerManager();
        ~ControllerManager();

        void Clear();
        
        void AddActionKey(const std::string& action, int keyCode);
        void KeyDown(int keyCode);
        void KeyUp(int keyCode);
        bool IsActionActivated(const std::string& action);
};

#endif // CONTROLLERMANAGER_HPP