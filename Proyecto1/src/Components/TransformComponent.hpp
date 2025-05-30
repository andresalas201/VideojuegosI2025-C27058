#ifndef TRANSFORMCOMPONENT_HPP
#define TRANSFORMCOMPONENT_HPP
#include <glm/glm.hpp>

/**
 * @brief A component for storing 2D transformation properties.
 * 
 * TransformComponent encapsulates the fundamental transformation properties
 * for 2D objects including position, scale, and rotation. This component is
 * commonly used in entity-component systems for managing object placement
 * and transformation in 2D space.
 */
struct TransformComponent {
    /** @brief Position vector in 2D world coordinates (x, y) */
    glm::vec2 position;
    
    /** @brief Scale factor vector for width and height scaling (x, y) */
    glm::vec2 scale;
    
    /** @brief Rotation angle in radians around the z-axis */
    double rotation;
    
    /**
     * @brief Constructs a TransformComponent with specified transformation values.
     * 
     * Creates a TransformComponent with the given position, scale, and rotation.
     * All parameters have sensible defaults: position at origin, uniform scale
     * of 1.0, and no rotation.
     * 
     * @param position Initial position in 2D world coordinates (default: (0.0, 0.0))
     * @param scale Initial scale factors for x and y axes (default: (1.0, 1.0))
     * @param rotation Initial rotation angle in radians (default: 0.0)
     */
    TransformComponent(glm::vec2 position = glm::vec2(0.0, 0.0),
                      glm::vec2 scale = glm::vec2(1.0, 1.0),
                      double rotation = 0.0) {
        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
    }
};

#endif // TRANSFORMCOMPONENT_HPP