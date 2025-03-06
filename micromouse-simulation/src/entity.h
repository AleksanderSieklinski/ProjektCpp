#ifndef ENTITY_H
#define ENTITY_H

#include "position.h"

/**
 * @enum Direction
 * @brief Represents the direction an entity can move.
 */
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

/**
 * @struct SensorData
 * @brief Represents sensor data for the mouse.
 */
struct SensorData {
    bool frontObstacle;
    bool leftObstacle;
    bool rightObstacle;
    bool backObstacle;
};
/**
 * @class Entity
 * @brief Base class for all entities in the maze.
 */
class Entity {
public:
    /**
     * @brief Virtual destructor for Entity.
     */
    virtual ~Entity() = default;

    /**
     * @brief Gets the current position of the entity.
     * @return The current position of the entity.
     */
    virtual Position getPosition() const = 0;

    /**
     * @brief Moves the entity in a specified direction.
     * @param dir The direction to move.
     */
    virtual void move(const Direction dir) = 0;
};

#endif // ENTITY_H