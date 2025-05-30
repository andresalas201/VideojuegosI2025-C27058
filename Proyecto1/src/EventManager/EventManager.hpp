#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP
#include <functional>
#include <list>
#include <map>
#include <memory>
#include <typeindex>
#include <iostream>
#include "Event.hpp"

/**
 * @brief Abstract base class for event callback handling.
 * 
 * IEventCallback provides a common interface for all event callback
 * implementations. It uses the template method pattern to allow
 * type-safe event handling while maintaining a uniform interface
 * for the event management system.
 */
class IEventCallback {
private:
    /**
     * @brief Pure virtual method for handling specific event types.
     * 
     * This method must be implemented by derived classes to provide
     * type-specific event handling logic.
     * 
     * @param e Reference to the event to be processed
     */
    virtual void Call(Event& e) = 0;
    
public:
    /**
     * @brief Virtual destructor for proper polymorphic destruction.
     */
    virtual ~IEventCallback() = default;
    
    /**
     * @brief Executes the event callback.
     * 
     * Public interface method that delegates to the private Call method.
     * This provides a consistent interface for event execution while
     * keeping the implementation details private.
     * 
     * @param e Reference to the event to be executed
     */
    void ExecuteEvent(Event& e) {
        Call(e);
    }
};

/**
 * @brief Template implementation of event callback for specific owner and event types.
 * 
 * EventCallback provides a type-safe wrapper around member function pointers,
 * allowing objects to register methods as event handlers. It handles the
 * type casting and method invocation for specific event types.
 * 
 * @tparam TOwner Type of the object that owns the callback method
 * @tparam TEvent Type of event that this callback handles
 */
template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
private:
    /** @brief Type alias for member function pointer */
    typedef void (TOwner::*CallbackFunction)(TEvent&);
    
    /** @brief Pointer to the object instance that owns the callback method */
    TOwner* ownerInstance;
    
    /** @brief Pointer to the member function to be called */
    CallbackFunction callbackFunction;
    
    /**
     * @brief Implementation of the abstract Call method.
     * 
     * Performs type casting of the generic Event to the specific TEvent type
     * and invokes the callback method on the owner instance.
     * 
     * @param e Reference to the event (will be cast to TEvent)
     */
    virtual void Call(Event& e) override {
        std::invoke(callbackFunction, ownerInstance, static_cast<TEvent&>(e));
    }
    
public:
    /**
     * @brief Constructs an EventCallback with the specified owner and method.
     * 
     * Creates a callback wrapper that will invoke the specified member function
     * on the given owner instance when an event is triggered.
     * 
     * @param ownerInstance Pointer to the object that owns the callback method
     * @param callbackFunction Pointer to the member function to be called
     */
    EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction) {
        this->ownerInstance = ownerInstance;
        this->callbackFunction = callbackFunction;
    }
};

/** @brief Type alias for a list of event callback handlers */
typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

/**
 * @brief Central manager for event subscription and emission in the event system.
 * 
 * EventManager implements the observer pattern, allowing objects to subscribe
 * to specific event types and automatically receive notifications when those
 * events are emitted. It provides type-safe event handling using templates
 * and manages the lifecycle of event subscriptions.
 * 
 * The manager supports:
 * - Type-safe event subscription using member function pointers
 * - Event emission with automatic callback invocation
 * - Multiple subscribers per event type
 * - Automatic memory management of callbacks
 */
class EventManager {
private:
    /** @brief Map storing lists of event handlers indexed by event type */
    std::map<std::type_index, std::unique_ptr<HandlerList>> subscribers;
    
public:
    /**
     * @brief Constructs a new EventManager instance.
     * 
     * Initializes the event management system and outputs a creation message
     * for debugging purposes.
     */
    EventManager() {
        std::cout <<"[EventManager] se crea\n";
    }
    
    /**
     * @brief Destructor for EventManager.
     * 
     * Cleans up all registered event handlers and outputs a destruction
     * message for debugging purposes.
     */
    ~EventManager() {
        std::cout <<"[EventManager] se destruye\n";
    }
    
    /**
     * @brief Clears all event subscriptions.
     * 
     * Removes all registered event handlers from all event types.
     * This effectively resets the event manager to its initial state.
     */
    void Reset() {
        subscribers.clear();
    }
    
    /**
     * @brief Subscribes an object method to a specific event type.
     * 
     * Registers a member function of an object to be called whenever
     * an event of the specified type is emitted. The callback will
     * receive the event as a parameter when triggered.
     * 
     * @tparam TEvent Type of event to subscribe to
     * @tparam TOwner Type of the object that owns the callback method
     * @param ownerInstance Pointer to the object instance
     * @param callbackFunction Pointer to the member function to be called
     * 
     * Example usage:
     * @code
     * eventManager.SubscribeToEvent<CollisionEvent>(
     *     this, &Player::OnCollision);
     * @endcode
     */
    template <typename TEvent, typename TOwner>
    void SubscribeToEvent(TOwner* ownerInstance, void (TOwner::*callbackFunction)(TEvent&)) {
        if (!subscribers[typeid(TEvent)].get()) {
            subscribers[typeid(TEvent)] = std::make_unique<HandlerList>();
        }
        auto subscriber = std::make_unique<EventCallback<TOwner, TEvent>>(
            ownerInstance, callbackFunction);
        subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
    }
    
    /**
     * @brief Emits an event to all registered subscribers.
     * 
     * Creates an event of the specified type using the provided arguments
     * and delivers it to all objects that have subscribed to this event type.
     * The event is constructed with perfect forwarding of the arguments.
     * 
     * @tparam TEvent Type of event to emit
     * @tparam TArgs Types of constructor arguments for the event
     * @param args Constructor arguments for creating the event instance
     * 
     * Example usage:
     * @code
     * eventManager.EmitEvent<CollisionEvent>(entity1, entity2, collisionPoint);
     * @endcode
     */
    template <typename TEvent, typename... TArgs>
    void EmitEvent(TArgs&&... args) {
        auto handlers = subscribers[typeid(TEvent)].get();
        if(handlers) {
            for (auto it = handlers->begin(); it != handlers->end(); it++) {
                auto handler = it->get();
                TEvent event(std::forward<TArgs>(args)...);
                handler->ExecuteEvent(event);
            }
        }
    }
};

#endif // EVENTMANAGER_HPP