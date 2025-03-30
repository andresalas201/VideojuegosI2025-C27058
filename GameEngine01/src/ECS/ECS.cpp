#include "ECS.hpp"
#include <algorithm>
#include <iostream>

int IComponent::nextId = 0;

int Entity::GetId() const {
    return this->id;
}

void System::AddEntityToSystem(Entity entity) {
    entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity) {
    auto it = std::remove_if(
        entities.begin(), entities.end(), 
        [&entity](Entity other) {return entity == other;});
    
    entities.erase(it, entities.end());

}

std::vector<Entity> System::GetSystemEntities() const {
    return entities;
}

const Signature& System::GetComponentSignature() const {
    return componentSignature;
}

Registry::Registry() {
    std::cout << "[Registry] se crea\n";
}

Registry::~Registry() {
    std::cout << "[Registry] se destruye\n";
}

Entity Registry::CreateEntity() {
    int entityID;

    if (freeIds.empty()) {
        entityID = numEntity++;
    } else {
        entityID = freeIds.front();
        freeIds.pop_front();
    }

    if(static_cast<long unsigned int>(entityID) >= entityComponentSignature.size()) {
        entityComponentSignature.resize(entityID + 100);
    }

    Entity entity(entityID);
    entity.registry = this;
    std::cout << "[Registry] se crea entidad\n";
    return entity;

}

void Registry::KillEntity(Entity entity) {
    entitiesToBeKilled.insert(entity);
}

void Registry::AddEntityToSystems(Entity entity) {
    const int entityId = entity.GetId();

    const Signature& entityComponentSign = this->entityComponentSignature[entityId];

    for (auto& system : systems) {
        const auto& systemComponentSignature =
            system.second->GetComponentSignature();

        bool isInterested = (entityComponentSign & systemComponentSignature)
            == systemComponentSignature;

        if (isInterested) {
            system.second->AddEntityToSystem(entity);
        }
    }
}


void Registry::RemoveEntityFromSystem(Entity entity) {
    for (auto system : systems) {
        system.second->RemoveEntityFromSystem(entity);
    }
}

void Registry::Update() {
    for (auto entity : entitiesToBeAdded) {
        AddEntityToSystems(entity);
    }
    entitiesToBeAdded.clear();

    for(auto entity: entitiesToBeKilled) {
        RemoveEntityFromSystem(entity);
        entityComponentSignature[entity.GetId()].reset();
        freeIds.push_back(entity.GetId());
    }
    entitiesToBeKilled.clear();

}

