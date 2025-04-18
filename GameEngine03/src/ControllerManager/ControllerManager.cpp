#include "ControllerManager.hpp"

#include <iostream>

ControllerManager::ControllerManager() {
    std::cout << "[CONTROLLERMANAGER] se ejecuta constructor\n";
}

ControllerManager::~ControllerManager() {
    std::cout << "[CONTROLLERMANAGER] se ejecuta destructor\n";
}

void ControllerManager::Clear() {
    actionKeyName.clear();
    keyDown.clear();
}

void ControllerManager::AddActionKey(const std::string& action, int keyCode) {
    actionKeyName.emplace(action, keyCode);
}

void ControllerManager::KeyDown(int keyCode) {
    auto it = keyDown.find(keyCode);
    if (it != keyDown.end()) {
        keyDown[keyCode] = true;
    }
}

void ControllerManager::KeyUp(int keyCode) {
    auto it = keyDown.find(keyCode);
    if (it != keyDown.end()) {
        keyDown[keyCode] = false;
    }
}

bool ControllerManager::IsActionActivated(const std::string& action) {
    auto it = actionKeyName.find(action);
    if (it != actionKeyName.end()) {
        return keyDown[actionKeyName[action]];
    }
    return false;
}
