#ifndef EVENTMANAGER_HPP
#define EVENTMANAGER_HPP

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <typeindex>
#include <iostream>

#include "Event.hpp"

class IEventCallback {
    private:
        virtual void Call(Event& e) = 0;
    public:
        virtual ~IEventCallback() = default;
        void ExecuteEvent(Event& e) {
            Call(e);
        }
};

template <typename TOwner, typename TEvent>
class EventCallback : public IEventCallback {
    private:
        typedef void (TOwner::*CallbackFuncion(TEvent&));

        TOwner* ownerInstance;
        CallbackFuncion callbackFunction;

        virtual void Call(Event& e) override {
            std::invoke(callbackFunction, ownerInstance, static_Cast<TEvent&>(e))
        }
    public:
        EventCallback(TOwner* ownerInstance, CallbackFunction callbackFunction) {
            this->ownerInstance = ownerInstance;
            this->callbackFunction = callbackFunction;
        }

};

typedef std::list<std::unique_ptr<IEventCallback>> HandlerList;

class EventManager {
    private:

        std::map<std::type_index, std::unique_ptr<HandlerList> subscribers;


    public:

        EventManager() {
            std::cout <<"[EventManager] se crea\n";
        }

        ~EventManager() {
            std::cout <<"[EventManager] se destruye\n";
        }

        void Reset() {
            subscribers.clear();
        }

        template <typename TEvent, typename TOwner>
        void SubscribeToEvent(TOwner* ownerInstance, void (TOwner::*CallbackFunction)(TEvent&))) {
            if (!subscriber[typeid(TEvent)].get()) {
                subscriber[typeid(TEvent)] = std::make_unique<HandlerList>();
            }
            auto subscriber = std::make_unique<EventCalback<TOwner, TEvent>>(
                ownerInstance, callbackFunction)
            subscribers[typeid(TEvent)]->push_back(std::move(subscriber));
        }

        template <typename TEvent, typename... TArgs>
        void EmitEvent(TArgs&&... args) {
            auto handlers = subscribers[typeid(TEvent)].get();
            if(handlers) {
                for (auto it = handler->begin(); it != handlers->end(); it++) {
                    auto handler = it->get();
                    TEvent event(std::forward<TArgs>(args)...);
                    handler->Execute(event);
                }
            }
        }
};

#endif // EVENTMANAGER_HPP