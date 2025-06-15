#include "SceneLoader.hpp"

#include "../Components/CircleColliderComponent.hpp"
#include "../Components/TransformComponent.hpp"
#include "../Components/SpriteComponent.hpp"
#include "../Components/RigidBodyComponent.hpp"
#include "../Components/AnimationComponent.hpp"
#include "../Components/ScriptComponent.hpp"
#include "../Components/TextComponent.hpp"
#include "../Components/ClickableComponent.hpp"
#include "../Components/CameraFollowComponent.hpp"
#include "../Components/BoxColliderComponent.hpp"
#include "../Components/TagComponent.hpp"
#include "../Game/Game.hpp"

#include <iostream>
#include <sstream>
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
    std::unique_ptr<AnimationManager>& animationManager,
    SDL_Renderer* renderer) {

    std::cout << "[SCENELOADER] Se carga la escena " << scenePath << std::endl;

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

    sol::table animations = scene["animations"];
    this->LoadAnimations(animations, animationManager);
    
    sol::table keys = scene["keys"];
    this->LoadKeys(keys, controllerManager);

    sol::table maps = scene["maps"];
    this->LoadMap(maps, registry);

    sol::table entities = scene["entities"];
    LoadEntities(lua, entities, registry);

    sol::table fonts = scene["fonts"];
    LoadFonts(fonts, assetManager);

    sol::table buttons = scene["buttons"];
    LoadButtons(buttons, controllerManager);
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

void SceneLoader::LoadAnimations(const sol::table& animations, 
    std::unique_ptr<AnimationManager>& animationManager) {
    
    int index = 0;
    while (true) {
        sol::optional<sol::table> hasAnimation = animations[index];
        if (hasAnimation == sol::nullopt) {
            break;
        }

        sol::table animation = animations[index];
        std::string animationId = animation["animation_id"];
        std::string textureId = animation["texture_id"];
        int w = animation["w"];
        int h = animation["h"];
        int numFrames = animation["num_frames"];
        int speedRate = animation["speed_rate"];
        bool isLoop = animation["is_loop"];
        animationManager->AddAnimation(animationId, textureId, w, h, 
            numFrames, speedRate, isLoop);
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

void SceneLoader::LoadMap(const sol::table map, std::unique_ptr<Registry>& registry) {
    sol::optional<int> hasWidth = map["width"];
    if (hasWidth != sol::nullopt) {
        Game::GetInstance().mapWidth = map["width"];
    }

    sol::optional<int> hasHeight = map["height"];
    if (hasHeight != sol::nullopt) {
        Game::GetInstance().mapHeight = map["height"];
    }

    sol::optional<std::string> hasPath = map["map_path"];
    if (hasPath != sol::nullopt) {
        std::string mapPath = map["map_path"];
        std::string tileName = map ["tile_name"];

        // Se carga el xml
        tinyxml2::XMLDocument xmlMap;
        xmlMap.LoadFile(mapPath.c_str());

        // Extraer la raiz del documento xml
        tinyxml2::XMLElement* xmlRoot = xmlMap.RootElement();

        // Extraer dimensiones
        int tWidth, tHeight, mWidth, mHeight;
        xmlRoot->QueryIntAttribute("tilewidth", &tWidth);
        xmlRoot->QueryIntAttribute("tileheight", &tHeight);
        xmlRoot->QueryIntAttribute("width", &mWidth);
        xmlRoot->QueryIntAttribute("height", &mHeight);

        // Calcular width y height del mapa
        Game::GetInstance().mapWidth = mWidth * tWidth;
        Game::GetInstance().mapHeight = mHeight * tHeight;

        // Se carga el documento con el tileset
        std::string tilePath = map["tile_path"];
        
        tinyxml2::XMLDocument xmlTileSet;
        xmlTileSet.LoadFile(tilePath.c_str());

        // Se obtiene el root del tileset
        tinyxml2::XMLElement* xmlTileRoot = xmlTileSet.RootElement();
        
        // Extraer cant de columnas
        int columns;
        xmlTileRoot->QueryIntAttribute("columns", &columns);

        // Se obtiene el primer elemento de tipo layer
        tinyxml2::XMLElement* xmlLayer = xmlRoot->FirstChildElement("layer");

        while(xmlLayer != nullptr) {
            LoadLayer(registry, xmlLayer, tWidth, tHeight, mWidth, tileName, columns);
            xmlLayer = xmlLayer->NextSiblingElement("layer");
        }

        // Se obtiene el primer elemento de tipo objectGroup
        tinyxml2::XMLElement* xmlObjectGroup = xmlRoot->FirstChildElement("objectgroup");

        while (xmlObjectGroup != nullptr) {
            const char* objectGroupName;
            std::string name;
            xmlObjectGroup->QueryStringAttribute("name", &objectGroupName);
            name = objectGroupName;
            if (name.compare("colliders") == 0) {
                LoadColliders(registry, xmlObjectGroup);
            }

            xmlObjectGroup = xmlObjectGroup->NextSiblingElement("objectgroup");
        }
        
    }
}
        
void SceneLoader::LoadLayer(std::unique_ptr<Registry>& registry, tinyxml2::XMLElement* layer,
    int tWidth, int tHeight, int mWidth, const std::string& tileSet, int columns) {

    tinyxml2::XMLElement* xmlData = layer->FirstChildElement("data");
    const char* data = xmlData->GetText();

    std::stringstream tmpNumber;
    int pos = 0;
    int tileNumber = 0;
    while (true) {
        if (data[pos] == '\0') {
            break;
        }
        if (isdigit(data[pos])) {
            tmpNumber << data[pos];
        } else if (!isdigit(data[pos]) && tmpNumber.str().length() != 0) {
            int tileId = std::stoi(tmpNumber.str());
            if (tileId > 0) {
                Entity tile = registry->CreateEntity();
                tile.AddComponent<TransformComponent>( 
                    glm::vec2(
                        (tileNumber % mWidth) * tWidth,
                        (tileNumber / mWidth) * tHeight
                    )
                );
                tile.AddComponent<SpriteComponent>(
                    tileSet,
                    tWidth,
                    tHeight,
                    ((tileId-1) % columns) * tWidth,
                    ((tileId-1) / columns) * tHeight
                );
                registry->AddEntityToSystems(tile);
            }
            tileNumber++;
            tmpNumber.str("");
        }
        pos++;
    }

}

void SceneLoader::LoadColliders(std::unique_ptr<Registry>& registry,
    tinyxml2::XMLElement* objectGroup) {
        
    tinyxml2::XMLElement* object = objectGroup->FirstChildElement("object");
    while (object != nullptr) {
        const char* name;
        std::string tag;
        int x, y, w, h;

        // Obtener el tag
        object->QueryStringAttribute("name", &name);
        tag = name;

        // obtener la posiciion
        object->QueryIntAttribute("x", &x);
        object->QueryIntAttribute("y", &y);

        // Obtener la dimension
        object->QueryIntAttribute("width", &w);
        object->QueryIntAttribute("height", &h);

        // Crear entidad

        Entity collider = registry->CreateEntity();
        collider.AddComponent<TagComponent>(tag);
        collider.AddComponent<TransformComponent>(glm::vec2(x, y));
        collider.AddComponent<BoxColliderComponent>(w, h);
        collider.AddComponent<RigidBodyComponent>(false, 99999999999.0f, true);
        registry->AddEntityToSystems(collider);
        object = object->NextSiblingElement("object");
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
            sol::optional<sol::table> hasAnimation = components["animation"];
            if (hasAnimation != sol::nullopt) {
                newEntity.AddComponent<AnimationComponent>(
                    components["animation"]["num_frames"],
                    components["animation"]["speed_rate"],
                    components["animation"]["is_loop"]);
            }

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
                    components["rigidBody"]["is_dynamic"],
                    components["rigidBody"]["mass"],
                    components["rigidBody"]["is_solid"]
                );
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

            //* CameraFollowComponent
            sol::optional<sol::table> hasCameraFollow = components["camera_follow"];
            if (hasCameraFollow != sol::nullopt) {
                newEntity.AddComponent<CameraFollowComponent>();
            }

            //* BoxColliderComponent
            sol::optional<sol::table> hasBoxCollider = components["box_collider"];
            if (hasBoxCollider != sol::nullopt) {
                newEntity.AddComponent<BoxColliderComponent>(
                    components["box_collider"]["width"],
                    components["box_collider"]["height"],
                    glm::vec2(components["box_collider"]["offset"]["x"],
                        components["box_collider"]["offset"]["y"])
                );
            }

            //* TagComponent
            sol::optional<sol::table> hasTag = components["tag"];
            if (hasTag != sol::nullopt) {
                std::string tag = components["tag"]["tag"];
                newEntity.AddComponent<TagComponent>(tag);
            }   


            //* ClickableComponent
            sol::optional<sol::table> hasClickable = components["clickable"];
            if (hasClickable != sol::nullopt) {
                newEntity.AddComponent<ClickableComponent>();
            }

            //* ScriptComponent
            sol::optional<sol::table> hasScript = components["script"];
            if (hasScript != sol::nullopt) {
                lua["on_collision"] = sol::nil;
                lua["update"] = sol::nil;
                lua["on_click"] = sol::nil;
                lua["on_awake"] = sol::nil;
                std::string path = components["script"]["path"];
                lua.script_file(path);

                sol::optional<sol::function> hasOnAwake = lua["on_awake"];
                if (hasOnAwake != sol::nullopt) {
                    lua["this"] = newEntity;
                    sol::function OnAwake = lua["on_awake"];
                    OnAwake();
                }

                sol::optional<sol::function> hasOnCollision = lua["on_collision"];
                sol::function onCollision = sol::nil;
                if (hasOnCollision != sol::nullopt) {
                    onCollision = lua["on_collision"];
                }

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

                newEntity.AddComponent<ScriptComponent>(onCollision, update, onClick);
            }
        }

        registry->AddEntityToSystems(newEntity);
        index++;
    }
}


