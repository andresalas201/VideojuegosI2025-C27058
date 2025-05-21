#include "SceneLoader.hpp"

#include "../Systems/AudioSystem.hpp"

#include "../Components/CircleColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/ClickableComponent.hpp"
#include "../Components/HealthComponent.hpp"
#include "../Components/UpgradeComponent.hpp"
#include "../Components/PlayerComponent.hpp"
#include "../Components/AttackComponent.hpp"

#include <iostream>
#include <glm/glm.hpp>

SceneLoader::SceneLoader() {
    std::cout << "[SCENELOADER] Se crea el scene loader\n";
}


SceneLoader::~SceneLoader() {
    std::cout << "[SCENELOADER] Se destruye el scene loader\n";
}
void SceneLoader::LoadScene(const std::string& scenePath, sol::state& lua,
    std::unique_ptr<AssetManager>& assetManager,
    std::unique_ptr<ControllerManager>& controllerManager,
    std::unique_ptr<Registry>& registry,
    SDL_Renderer* renderer) {

    
    std::cout << "[SCENELOADER] Se carga la escena: " << scenePath << 
        std::endl;
    sol::load_result script_result = lua.load_file(scenePath);
    if (!script_result.valid()) {
        sol::error err = script_result;
        
        std::string errMessage = err.what();
        std::cerr << "[SCENELOADER] " << errMessage << std::endl;
        return;
    }

    lua.script_file(scenePath);

    sol::table scene = lua["scene"];
    
    sol::table sprites = scene["sprites"];
    this->LoadSprites(renderer, sprites, assetManager);
    
    sol::table keys = scene["keys"];
    this->LoadKeys(keys, controllerManager);

    sol::optional<sol::table> hasSounds = scene["sound"];
    if (hasSounds != sol::nullopt) {
        std::cout << "sonido\n";
        sol::table sounds = scene["sound"];
        LoadSound(sounds, assetManager);
        std::cout << "sale de sonido\n";
    }

    sol::table entities = scene["entities"];
    LoadEntities(lua, entities, registry);

    sol::table fonts = scene["fonts"];
    LoadFonts(fonts, assetManager);

    sol::table buttons = scene["buttons"];
    LoadButtons(buttons, controllerManager);

    sol::table music = scene["music"];
    StartMusic(music, registry);
}

void SceneLoader::LoadSprites(SDL_Renderer* renderer, 
    const sol::table& sprites, 
    std::unique_ptr<AssetManager>& assetManager) {
    
    int index = 0;
    while (true) {
        sol::optional<sol::table> hasSprite = sprites[index];
        if (hasSprite == sol::nullopt) {
            break;
        }
        sol::table sprite = sprites[index];
        
        std::string assetId = sprite["assetId"];
        std::string filePath = sprite["filePath"];

        assetManager->AddTexture(renderer, assetId, filePath);
        index++;
    }
}

void SceneLoader::LoadFonts(const sol::table& fonts,
    std::unique_ptr<AssetManager>& assetManager) {

    int index = 0;
    while(true) {
        sol::optional<sol::table> hasFont = fonts[index];
        if(hasFont == sol::nullopt) break;
        
        sol::table font = fonts[index];
        std::string fontId = font["fontId"];
        std::string filePath = font["filePath"];
        int size = font["fontSize"];

        assetManager->AddFont(fontId, filePath, size);

        index++;
    }
}


void SceneLoader::LoadKeys(const sol::table& keys,
    std::unique_ptr<ControllerManager>& controllerManager) {

    int index = 0;
    while (true) {
        sol::optional<sol::table> hasKey = keys[index];
        if (hasKey == sol::nullopt) break;
        
        sol::table key = keys[index];

        std::string name = key["name"];
        int keyCode = key["key"];

        controllerManager->AddActionKey(name, keyCode);
        index++;
    }
}

void SceneLoader::LoadButtons(const sol::table& buttons,
    std::unique_ptr<ControllerManager>& controllerManager) {

    int index = 0;
    while (true) {
        sol::optional<sol::table> hasButton = buttons[index];
        if (hasButton == sol::nullopt) break;
        
        sol::table button = buttons[index];

        std::string name = button["name"];
        int buttonCode = button["button"];

        controllerManager->AddMouseButton(name, buttonCode);
        index++;
    }
    
}

void SceneLoader::LoadSound(const sol::table& sounds, std::unique_ptr<AssetManager>& assetManager) {
    int index = 0;
    while (true) {
        sol::optional<sol::table> hasSound = sounds[index];
        if (hasSound == sol::nullopt) break;
        
        sol::table sound = sounds[index];

        std::string name = sound["name"];
        std::string filePath = sound["file_path"];

        assetManager->AddSound(name, filePath);
        index++;
    }
}


void SceneLoader::LoadEntities(sol::state& lua, const sol::table& entities,
    std::unique_ptr<Registry>& registry) {
    
    int index = 0;
    while (true) {
        sol::optional<sol::table> hasEntity = entities[index];
        if (hasEntity == sol::nullopt) break;

        sol::table entity = entities[index];

        Entity newEntity = registry->CreateEntity();

        sol::optional<sol::table> components = entity["components"];
        if (components != sol::nullopt) {
            sol::table components = entity["components"];

            //* AnimationComponent

            //* CircleColliderComponent
            sol::optional<sol::table> hasCircleCollider = components["circle_collider"];
            if (hasCircleCollider != sol::nullopt) {
                newEntity.AddComponent<CircleColliderComponent>(
                    components["circle_collider"]["radius"],
                    components["circle_collider"]["width"],
                    components["circle_collider"]["height"]
                );
            }

            //* RigidBodyComponent
            sol::optional<sol::table> hasRigidBody = components["rigidBody"];
            if (hasRigidBody != sol::nullopt) {
                
                newEntity.AddComponent<RigidBodyComponent>(
                    glm::vec2{
                        components["rigidBody"]["velocity"]["x"],
                        components["rigidBody"]["velocity"]["y"]
                    }
                );
            }

            //* ScriptComponent
            sol::optional<sol::table> hasScript = components["script"];
            if (hasScript != sol::nullopt) {
                lua["update"] = sol::nil;
                lua["onClick"] = sol::nil;
                std::string path = components["script"]["path"];
                lua.script_file(path);

                
                sol::optional<sol::function> hasOnClick = lua["on_click"];
                sol::function onClick = sol::nil;
                if (hasOnClick != sol::nullopt) {
                    onClick = lua["on_click"];
                }
                
                sol::optional<sol::function> hasUpdate = lua["update"];
                sol::function update = sol::nil;
                if (hasUpdate != sol::nullopt) {
                    update = lua["update"];
                }

                newEntity.AddComponent<ScriptComponent>(update, onClick);
            }

            //* SpriteComponent
            sol::optional<sol::table> hasSprite = components["sprite"];
            if (hasSprite != sol::nullopt) {
                newEntity.AddComponent<SpriteComponent>(
                    components["sprite"]["assetId"],
                    components["sprite"]["width"],
                    components["sprite"]["height"],
                    components["sprite"]["src_rect"]["x"],
                    components["sprite"]["src_rect"]["y"]
                );
            }

            //* TextComponent
            sol::optional<sol::table> hasText = components["text"];
            if (hasText != sol::nullopt) {
                newEntity.AddComponent<TextComponent>(
                    components["text"]["text"],
                    components["text"]["fontId"],
                    components["text"]["r"],
                    components["text"]["g"],
                    components["text"]["b"],
                    components["text"]["a"]
                );
            }

            //* TransformComponent
            sol::optional<sol::table> hasTransform = components["transform"];
            if (hasTransform != sol::nullopt) {
                newEntity.AddComponent<TransformComponent>(
                    glm::vec2 {
                        components["transform"]["position"]["x"],
                        components["transform"]["position"]["y"],
                    },
                    glm::vec2 {
                        components["transform"]["scale"]["x"],
                        components["transform"]["scale"]["y"],
                    },
                    components["transform"]["rotation"]
                );
            }

            //* ClickableComponent
            sol::optional<sol::table> hasClickable = components["clickable"];
            if (hasClickable != sol::nullopt) {
                newEntity.AddComponent<ClickableComponent>();
            }

            //* HealthComponent
            sol::optional<sol::table> hasHealth = components["health"];
            if (hasHealth != sol::nullopt) {
                newEntity.AddComponent<HealthComponent>(components["health"]["max_health"],
                    components["health"]["damage"]);
            }

            //* UpgradeComponent
            sol::optional<sol::table> hasUpgrade = components["upgrade"];
            if(hasUpgrade != sol::nullopt) {
                int inc = components["upgrade"]["increase"];
                newEntity.AddComponent<UpgradeComponent>(inc);
            }


            //* PlayerComponent
            sol::optional<sol::table> hasPlayer = components["player"];
            if(hasPlayer != sol::nullopt) {
                int num = components["player"]["number"];
                newEntity.AddComponent<PlayerComponent>(num);
            }


            //* AttackComponent
            sol::optional<sol::table> hasAttack = components["attack"];
            if (hasAttack != sol::nullopt) {
                    newEntity.AddComponent<AttackComponent>(components["attack"]["damage"],
                    components["attack"]["radius"], components["attack"]["width"],
                    components["attack"]["height"], components["attack"]["texture_id"],
                    components["attack"]["src_x"], components["attack"]["src_y"],
                    glm::vec2(components["attack"]["vel_x"], components["attack"]["vel_y"]),
                    components["attack"]["sound_path"], components["attack"]["hit_path"],
                    components["attack"]["max_shots"], components["attack"]["left"],
                    glm::vec2(components["attack"]["scale"]["x"], components["attack"]["scale"]["y"]),
                    components["attack"]["rotation"]);
            }

            //* SoundComponent
            sol::optional<sol::table> hasSound = components["sound"];
            if (hasSound != sol::nullopt) {
                std::string soundPath = components["sound"]["sound_path"];
                newEntity.AddComponent<SoundComponent>(soundPath);
            }
            
        }

        registry->AddEntityToSystems(newEntity);
        index++;
    }
}

void SceneLoader::StartMusic(const sol::table& music, std::unique_ptr<Registry>& registry) {
    std::string musicPath = music["filePath"];
    registry->GetSystem<AudioSystem>().playMusic(musicPath);

}


