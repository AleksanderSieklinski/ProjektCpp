#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include "maze.h"

/**
 * @class mazeGenerator
 * @brief Abstract base class for maze generation algorithms.
 * This class defines the interface for generating mazes.
 */
class mazeGenerator {
public:
    /**
     * @brief Destructor for mazeGenerator.
     */
    virtual ~mazeGenerator() = default;
    /**
     * @brief Generates a maze layout.
     * @param maze The maze to be generated.
     */
    virtual void generate(Maze& maze, bool isRefresh = false) = 0;
};

#endif // MAZEGENERATOR_H
