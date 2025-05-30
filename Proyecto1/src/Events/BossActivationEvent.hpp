#ifndef BOSSACTIVATIONEVENT_HPP
#define BOSSACTIVATIONEVENT_HPP
#include "../EventManager/Event.hpp"

/**
 * @brief Event triggered when a boss enemy is activated or deactivated.
 * 
 * BossActivationEvent is emitted when a boss encounter begins or ends
 * in the game. This event allows systems to respond to boss state changes,
 * such as starting boss music, changing UI elements, adjusting game mechanics,
 * or triggering cinematic effects. By default, the event indicates boss activation.
 * 
 * Example usage:
 * @code
 * // Subscribe to boss activation events
 * eventManager.SubscribeToEvent<BossActivationEvent>(this, &GameSystem::OnBossActivation);
 * 
 * // Emit a boss activation event
 * eventManager.EmitEvent<BossActivationEvent>();
 * 
 * // Handle the event
 * void GameSystem::OnBossActivation(BossActivationEvent& event) {
 *     if (event.isActive) {
 *         // Boss fight started
 *         StartBossMusic();
 *         ShowBossHealthBar();
 *     } else {
 *         // Boss defeated
 *         StopBossMusic();
 *         HideBossHealthBar();
 *     }
 * }
 * @endcode
 */
class BossActivationEvent : public Event {
public:
    /** 
     * @brief Flag indicating whether the boss is being activated or deactivated
     * 
     * When true, indicates the boss encounter is starting or the boss is active.
     * When false, indicates the boss encounter has ended or the boss is inactive.
     */
    bool isActive;
    
    /**
     * @brief Default constructor that creates a boss activation event.
     * 
     * Initializes the event with isActive set to true, indicating that
     * the boss is being activated by default. This constructor is typically
     * used when triggering a boss encounter.
     */
    BossActivationEvent(){
        this->isActive = true;
    };
};

#endif // BOSSACTIVATIONEVENT_HPP