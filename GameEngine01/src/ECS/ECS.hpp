#ifndef ECS_HPP
#define ECS_HPP

#include <memory>
#include <bitset>
#include <vector>

#include "../Utils/Pool.hpp"

const unsigned int MAX_COMPONENTS = 64;

// Signature

typedef std::bitset<MAX_COMPONENTS> Signature;

struct IComponent {
    protected:
        static int nextId;
};

template <typename TComponent>
class Component : public IComponent {
    public:
        static int GetId() {
            static int id = nextId++;
            return id;
        }
};

class Entity {
    private:
        int id;

    public:
        Entity(int id): id(id){}
        int GetId() const;
        bool operator==(const Entity& other) const { return id == other.id;}
        bool operator!=(const Entity& other) const { return id != other.id;}
        bool operator<(const Entity& other) const { return id < other.id;}
};

class System {
    private:
        Signature componentSignature;
        std::vector<Entity> entities;
    public:
        System() = default;
        ~System() = default;

        void AddEntityToSystem(Entity entity);
        void RemoveEntityFromSystem(Entity entity);
        std::vector<Entity> GetSystemEntities() const;
        const Signature& GetComponentSignature() const;

        template<typename TComponent>
        void RequireComponent();
};

class Registry {
    private:
        int numEntity = 0;
        std::vector<std::shared_ptr<IPool>> componentsPool;
    public:
};

template <typename TComponent>
void System::RequireComponent() {
    const auto componentID = Component<TComponent::GetId();
}



#endif // ECS_HPP