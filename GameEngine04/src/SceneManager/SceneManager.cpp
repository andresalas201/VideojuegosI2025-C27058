#include "SceneManager.hpp"
#include "../Game/Game.hpp"

#include <iostream>

SceneManager::SceneManager() {
    std::cout << "[SCENEMANAGER] se crea el scene manager\n";
    sceneLoader = std::make_unique<SceneLoader>();
}
SceneManager::~SceneManager() {
    sceneLoader.reset();
    std::cout << "[SCENEMANAGER] se destruye el scene manager\n";
}

void SceneManager::LoadSceneFromScript(const std::string& path,
    sol::state& lua) {

    //TODO: Verificar que el codigo sea correcto
    lua.script_file(path);

    sol::table scenes = lua["scenes"];

    int index = 0;
    while (true) {
        sol::optional<sol::table> hasScene = scenes[index];
        if(hasScene == sol::nullopt) break;
        sol::table scene = scenes[index];
        this->scenes.emplace(scene["name"], scene["path"]);
        
        if (index == 0) {
            nextScene = scene["name"];
        }

        index++;

    }
}

void SceneManager::LoadScene() {
    Game& game = Game::GetInstance();
    std::string scenePath = scenes[nextScene];
    sceneLoader->LoadScene(scenePath, game.lua, 
        game.assetManager, game.controllerManager,
        game.registry, game.renderer);
}

std::string SceneManager::GetNextScene() const {
    return this->nextScene;
}

void SceneManager::SetNextScene(const std::string& nextScene) {
    this->nextScene = nextScene; 
}

bool SceneManager::IsSceneRunning() const {
    return isSceneRunning;
}

void SceneManager::StartScene() {
    isSceneRunning = true;
}

void SceneManager::StopScene() {
    isSceneRunning = false;
}