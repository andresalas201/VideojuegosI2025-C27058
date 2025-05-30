#ifndef ECS_HPP
#define ECS_HPP

#include <memory>
#include <iostream>
#include <set>
#include <typeindex>
#include <deque>
#include <bitset>
#include <vector>
#include <unordered_map>

#include "../Utils/Pool.hpp"
#include "../Components/TransformComponent.hpp"
#include "../PreEntity/PreEntity.hpp"

/** @brief Maximum number of components that can be registered in the ECS system */
const unsigned int MAX_COMPONENTS = 64;

// Signature

/** @brief Bitset representing which components an entity possesses */
typedef std::bitset<MAX_COMPONENTS> Signature;

/**
 * @brief Base interface for all components in the ECS system.
 * 
 * IComponent provides a common base for component type identification
 * and serves as the foundation for the component ID generation system.
 */
struct IComponent {
    protected:
        /** @brief Static counter for generating unique component IDs */
        static int nextId;
};

/**
 * @brief Template class for type-safe component identification.
 * 
 * Component provides a unique ID for each component type using template
 * specialization and static variables to ensure each component type
 * gets a unique identifier within the ECS system.
 * 
 * @tparam TComponent The component type to generate an ID for
 */
template <typename TComponent>
class Component : public IComponent {
    public:
        /**
         * @brief Gets the unique ID for this component type.
         * 
         * Returns a unique integer ID for the component type. The ID is
         * generated once per component type and remains constant throughout
         * the program execution.
         * 
         * @return Unique integer ID for the component type
         */
        static int GetId() {
            static int id = nextId++;
            return id;
        }
};

/**
 * @brief Represents an entity in the Entity-Component-System architecture.
 * 
 * Entity is a lightweight wrapper around an integer ID that provides
 * methods for component management. Entities serve as containers for
 * components and are managed by the Registry system.
 */
class Entity {
    private:
        /** @brief Unique identifier for this entity */
        int id;

    public:
        /**
         * @brief Constructs an Entity with the specified ID.
         * 
         * @param id Unique integer identifier for the entity
         */
        Entity(int id): id(id){}
        
        /**
         * @brief Gets the unique ID of this entity.
         * 
         * @return Integer ID of the entity
         */
        int GetId() const;
        
        /**
         * @brief Marks this entity for deletion.
         * 
         * Schedules the entity to be removed from the system during
         * the next registry update cycle.
         */
        void Kill();
        
        /**
         * @brief Equality comparison operator.
         * 
         * @param other Entity to compare with
         * @return true if entities have the same ID, false otherwise
         */
        bool operator==(const Entity& other) const { return id == other.id;}
        
        /**
         * @brief Inequality comparison operator.
         * 
         * @param other Entity to compare with
         * @return true if entities have different IDs, false otherwise
         */
        bool operator!=(const Entity& other) const { return id != other.id;}
        
        /**
         * @brief Less-than comparison operator for ordering.
         * 
         * @param other Entity to compare with
         * @return true if this entity's ID is less than the other's
         */
        bool operator<(const Entity& other) const { return id < other.id;}

        /**
         * @brief Adds a component to this entity.
         * 
         * Creates and attaches a component of the specified type to this entity
         * using the provided constructor arguments.
         * 
         * @tparam TComponent Type of component to add
         * @tparam TArgs Types of constructor arguments
         * @param args Constructor arguments for the component
         */
        template <typename TComponent, typename... TArgs>
        void AddComponent(TArgs&&... args);

        /**
         * @brief Removes a component from this entity.
         * 
         * Detaches the specified component type from this entity.
         * 
         * @tparam TComponent Type of component to remove
         */
        template <typename TComponent>
        void RemoveComponent();

        /**
         * @brief Checks if this entity has a specific component.
         * 
         * @tparam TComponent Type of component to check for
         * @return true if the entity has the component, false otherwise
         */
        template <typename TComponent>
        bool HasComponent() const;

        /**
         * @brief Gets a reference to a component attached to this entity.
         * 
         * @tparam TComponent Type of component to retrieve
         * @return Reference to the component instance
         */
        template <typename TComponent>
        TComponent& GetComponent() const;

        /** @brief Pointer to the registry that manages this entity */
        class Registry* registry;
};

/**
 * @brief Base class for systems in the ECS architecture.
 * 
 * System processes entities that have specific component combinations.
 * Each system defines which components it requires and operates on
 * entities that match its component signature.
 */
class System {
    private:
        /** @brief Bitset defining which components this system requires */
        Signature componentSignature;
        
        /** @brief Collection of entities that match this system's requirements */
        std::vector<Entity> entities;
        
    public:
        /** @brief Default constructor */
        System() = default;
        
        /** @brief Default destructor */
        ~System() = default;

        /**
         * @brief Adds an entity to this system's processing list.
         * 
         * @param entity Entity to add to the system
         */
        void AddEntityToSystem(Entity entity);
        
        /**
         * @brief Removes an entity from this system's processing list.
         * 
         * @param entity Entity to remove from the system
         */
        void RemoveEntityFromSystem(Entity entity);
        
        /**
         * @brief Gets all entities currently managed by this system.
         * 
         * @return Vector of entities that match this system's component requirements
         */
        std::vector<Entity> GetSystemEntities() const;
        
        /**
         * @brief Gets the component signature for this system.
         * 
         * @return Reference to the bitset representing required components
         */
        const Signature& GetComponentSignature() const;

        /**
         * @brief Specifies that this system requires a specific component type.
         * 
         * Marks the specified component type as required for entities to be
         * processed by this system.
         * 
         * @tparam TComponent Type of component required by this system
         */
        template<typename TComponent>
        void RequireComponent();
};

/**
 * @brief Central registry for managing entities, components, and systems.
 * 
 * Registry serves as the core of the ECS architecture, providing entity
 * lifecycle management, component storage and retrieval, system registration,
 * and coordination between all ECS elements. It handles entity creation/destruction,
 * component attachment/detachment, and system updates.
 */
class Registry {
    private:
        /** @brief Counter for generating unique entity IDs */
        int numEntity = 0;
        
        /** @brief Storage pools for different component types */
        std::vector<std::shared_ptr<IPool>> componentsPools;
        
        /** @brief Component signatures for each entity */
        std::vector<Signature> entityComponentSignature;
        
        /** @brief Map of registered systems indexed by type */
        std::unordered_map<std::type_index, std::shared_ptr<System>> systems;
        
        /** @brief Set of entities scheduled to be added */
        std::set<Entity> entitiesToBeAdded;
        
        /** @brief Set of entities scheduled for deletion */
        std::set<Entity> entitiesToBeKilled;

        /** @brief Queue of available entity IDs for reuse */
        std::deque<int> freeIds;

    public:
        /**
         * @brief Constructs a new Registry instance.
         * 
         * Initializes the registry with empty entity and system collections.
         */
        Registry();
        
        /**
         * @brief Destructor for Registry.
         * 
         * Cleans up all managed entities, components, and systems.
         */
        ~Registry();

        /**
         * @brief Updates the registry state.
         * 
         * Processes pending entity additions and deletions, updates system
         * entity lists, and performs other maintenance tasks.
         */
        void Update();

        /** @brief Vector of enemy pre-entities for spawning */
        std::vector<PreEntity> enemyVector;
        
        /** @brief Vector of enemies scheduled to spawn */
        std::vector<PreEntity> enemiesToSpawn;
        
        /** @brief Scene identifier for victory condition */
        std::string winScene;
        
        /** @brief Scene identifier for defeat condition */
        std::string loseScene;

        // Entity management
        /**
         * @brief Creates a new entity in the registry.
         * 
         * Generates a new entity with a unique ID and registers it in the system.
         * 
         * @return Newly created Entity instance
         */
        Entity CreateEntity();
        
        /**
         * @brief Marks an entity for deletion.
         * 
         * Schedules the entity to be removed during the next update cycle.
         * 
         * @param entity Entity to be deleted
         */
        void KillEntity(Entity entity);

        // Component Management
        /**
         * @brief Adds a component to an entity.
         * 
         * Creates and attaches a component of the specified type to the given
         * entity using the provided constructor arguments.
         * 
         * @tparam TComponent Type of component to add
         * @tparam TArgs Types of constructor arguments
         * @param entity Entity to attach the component to
         * @param args Constructor arguments for the component
         */
        template <typename TComponent, typename... TArgs>
        void AddComponent(Entity entity, TArgs&&... args);

        /**
         * @brief Removes a component from an entity.
         * 
         * Detaches the specified component type from the given entity.
         * 
         * @tparam TComponent Type of component to remove
         * @param entity Entity to remove the component from
         */
        template <typename TComponent>
        void RemoveComponent(Entity entity);

        /**
         * @brief Checks if an entity has a specific component.
         * 
         * @tparam TComponent Type of component to check for
         * @param entity Entity to check
         * @return true if the entity has the component, false otherwise
         */
        template <typename TComponent>
        bool HasComponent(Entity entity) const;

        /**
         * @brief Gets a reference to a component attached to an entity.
         * 
         * @tparam TComponent Type of component to retrieve
         * @param entity Entity that owns the component
         * @return Reference to the component instance
         */
        template <typename TComponent>
        TComponent& GetComponent(Entity entity) const;

        // System Management
        /**
         * @brief Registers a new system in the registry.
         * 
         * Creates and registers a system of the specified type using the
         * provided constructor arguments.
         * 
         * @tparam TSystem Type of system to add
         * @tparam TArgs Types of constructor arguments
         * @param args Constructor arguments for the system
         */
        template <typename TSystem, typename... TArgs>
        void AddSystem(TArgs&&... args);

        /**
         * @brief Removes a system from the registry.
         * 
         * Unregisters and destroys the system of the specified type.
         * 
         * @tparam TSystem Type of system to remove
         */
        template <typename TSystem>
        void RemoveSystem();

        /**
         * @brief Checks if a system is registered.
         * 
         * @tparam TSystem Type of system to check for
         * @return true if the system is registered, false otherwise
         */
        template <typename TSystem>
        bool HasSystem() const;
        
        /**
         * @brief Gets a reference to a registered system.
         * 
         * @tparam TSystem Type of system to retrieve
         * @return Reference to the system instance
         */
        template <typename TSystem>
        TSystem& GetSystem() const;

        // Reset Registry
        /**
         * @brief Removes all entities from the registry.
         * 
         * Clears all entities and their associated components while
         * preserving system registrations.
         */
        void ClearAllEntities();

        /**
         * @brief Adds an entity to all compatible systems.
         * 
         * Checks the entity's component signature against all registered
         * systems and adds it to those with matching requirements.
         * 
         * @param entity Entity to add to systems
         */
        void AddEntityToSystems(Entity entity);
        
        /**
         * @brief Removes an entity from all systems.
         * 
         * Removes the entity from all systems that currently manage it.
         * 
         * @param entity Entity to remove from systems
         */
        void RemoveEntityFromSystem(Entity entity);
};

template <typename TComponent>
void System::RequireComponent() {
    const auto componentID = Component<TComponent>::GetId();
    componentSignature.set(componentID);
}

template <typename TComponent, typename... TArgs>
void Registry::AddComponent(Entity entity, TArgs&&... args) {
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    if (static_cast<long unsigned int>(componentId) >= componentsPools.size()) {
        componentsPools.resize(componentId + 10, nullptr);
    }

    if (!componentsPools[componentId]) {
        std::shared_ptr<Pool<TComponent>> newComponentPool = 
            std::make_shared<Pool<TComponent>>();
        componentsPools[componentId] = newComponentPool;
    }

    std::shared_ptr<Pool<TComponent>> componentPool =
        std::static_pointer_cast<Pool<TComponent>>(componentsPools[componentId]);
    
    if (entityId >= componentPool->GetSize()) {
        componentPool->Resize(numEntity + 100);
    }

    TComponent newComponent(std::forward<TArgs>(args)...);

    componentPool->Set(entityId, newComponent);
    entityComponentSignature[entityId].set(componentId);

    std::cout << "[Registry] se agrega componente " << componentId 
        << " a la entidad " << entityId << std::endl; 
}

template <typename TComponent>
void Registry::RemoveComponent(Entity entity) {
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    entityComponentSignature[entityId].set(componentId, false);
}

template <typename TComponent>
bool Registry::HasComponent(Entity entity) const {
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    return entityComponentSignature[entityId].test(componentId);
}


template<typename TComponent>
TComponent& Registry::GetComponent(Entity entity) const {
    const int componentId = Component<TComponent>::GetId();
    const int entityId = entity.GetId();

    auto componentPool =
        std::static_pointer_cast<Pool<TComponent>>(componentsPools[componentId]);
    return componentPool->Get(entityId);
}


template <typename TSystem, typename... TArgs>
void Registry::AddSystem(TArgs&&... args) {
    std::shared_ptr<System> newSystem = 
        std::make_shared<TSystem>(std::forward<TArgs>(args)...);
    systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
}

template <typename TSystem>
void Registry::RemoveSystem() {
    auto system = systems.find(std::type_index(typeid(TSystem)));
    systems.erase(system);
}

template <typename TSystem>
bool Registry::HasSystem() const {
    return systems.find(std::type_index(typeid(TSystem))) 
        != systems.end(); 
}

template <typename TSystem>
TSystem& Registry::GetSystem() const {
 auto system = systems.find(std::type_index(typeid(TSystem)));
 return *(std::static_pointer_cast<TSystem>(system->second));
}

template <typename TComponent, typename... TArgs>
void Entity::AddComponent(TArgs&&... args) {
    registry->AddComponent<TComponent>(*this, std::forward<TArgs>(args)...);
}

template <typename TComponent>
void Entity::RemoveComponent() {
    registry->RemoveComponent<TComponent>(*this);
}

template <typename TComponent>
bool Entity::HasComponent() const {
    return registry->HasComponent<TComponent>(*this);
}

template <typename TComponent>
TComponent& Entity::GetComponent() const {
    return registry->GetComponent<TComponent>(*this);
}

#endif // ECS_HPP