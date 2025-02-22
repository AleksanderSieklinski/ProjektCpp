#ifndef MOUSE_H
#define MOUSE_H

#include "maze.h"
#include "entity.h"
#include "utils/logger.h"
#include <stack>

/**
 * @class Mouse
 * @brief Represents a mouse navigating through a maze.
 */
class Mouse : public Entity {
public:
    /**
     * @brief Constructor for Mouse.
     * @param maze The maze the mouse is navigating.
     * @param logger The logger for logging mouse actions.
     */
    Mouse(const Maze& maze, Logger<std::string>& logger);

    /**
     * @brief Makes a decision based on sensor data.
     * @param data The sensor data.
     */
    void makeDecision(const SensorData& data);

    /**
     * @brief Moves the mouse in a specified direction.
     * @param dir The direction to move.
     */
    void move(const Direction dir) override;

    /**
     * @brief Gets the current position of the mouse.
     * @return The current position of the mouse.
     */
    Position getPosition() const override;

    /**
     * @brief Gets the shortest path found during exploration.
     * @return The shortest path as a vector of positions.
     */
    std::vector<Position> getPath() const;

    /**
     * @brief Finds the path from the current position to the target position.
     * @param start The start position.
     * @param goal The goal position.
     * @return The path as a vector of positions.
     */
    std::vector<Position> findPath(const Position& start, const Position& goal);

    /**
     * @brief Gets the direction from one position to another.
     * @param a The first position.
     * @param b The second position.
     * @return The direction from position a to position b.
     */
    Direction getDirection(const Position& a, const Position& b) const;

    /**
     * @brief Calculates the shortest path based on exploration data.
     */
    void calculateShortestPath();

protected:
    Position position; ///< The current position of the mouse
    const Maze& maze; ///< The maze the mouse is navigating
    Logger<std::string>& logger; ///< The logger for logging mouse actions
    std::vector<Position> path; ///< The shortest path found during exploration
    std::vector<Position> explorationPath; ///< The path taken during exploration
    std::vector<SensorData> obstacles; ///< The obstacles encountered during exploration

    /**
     * @brief Checks if a move is valid.
     * @param x The x coordinate of the move.
     * @param y The y coordinate of the move.
     * @return True if the move is valid, false otherwise.
     */
    bool isMoveValid(int x, int y) const;

    /**
     * @brief Heuristic function for pathfinding.
     * @param a The first position.
     * @param b The second position.
     * @return The heuristic value.
     */
    int heuristic(const Position& a, const Position& b) const;
};

#endif // MOUSE_H