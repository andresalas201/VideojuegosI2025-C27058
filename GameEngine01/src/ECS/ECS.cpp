#include "ECS.hpp"
#include <algorithm>

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