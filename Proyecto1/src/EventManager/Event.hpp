#ifndef EVENT_HPP
#define EVENT_HPP

/**
 * @brief Base class for all events in the event system.
 * 
 * Event serves as the abstract base class for all event types in the 
 * event-driven architecture. Specific event types should inherit from 
 * this class to be processed by the event management system. This class
 * provides a common interface for event handling and type identification.
 * 
 * Example usage:
 * @code
 * class CollisionEvent : public Event {
 *     // Event-specific data and methods
 * };
 * @endcode
 */
class Event {
public:
    /**
     * @brief Default constructor for Event.
     * 
     * Creates a new event instance with default initialization.
     * This constructor is typically called by derived event classes.
     */
    Event() = default;
};

#endif // EVENT_HPP