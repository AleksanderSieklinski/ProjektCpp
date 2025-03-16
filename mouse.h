#ifndef MOUSE_H
#define MOUSE_H

#include "maze.h"
#include "entity.h"
#include "logger.h"
#include <queue>
#include <set>

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
    Mouse(const Maze& maze, Logger<std::string>& logger, Maze& knownMaze);

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
     * @brief Finds the path from the current position to the target position.
     * @param start The start position.
     * @param goal The goal position.
     * @return The path as a vector of positions.
     */
    std::vector<Position> findPath(const Position& start, const Position& goal);

    /**
     * @brief Calculates the shortest path based on exploration data.
     */
    void calculateShortestPath();

    /**
     * @brief Resets the mouse to its initial state.
     */
    void reset();

    /**
     * @brief Traverses a single step in the maze.
        * @param sensorlogger The logger for logging sensor data.
        * @param visitedFields The set of visited fields.
     */
    void walkMazeStep(Logger<std::string> &sensorlogger, std::set<Position, std::less<Position>>& visitedFields);

protected:
    Position position; ///< The current position of the mouse
    const Maze& maze; ///< The maze the mouse is navigating
    Maze& knownMaze; ///< The maze layout known to the mouse
    Logger<std::string>& logger; ///< The logger for logging mouse actions
    std::vector<Position> path; ///< The shortest path found during exploration
    std::vector<SensorData> obstacles; ///< The obstacles encountered during exploration

};

#endif // MOUSE_H
