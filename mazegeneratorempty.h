#ifndef MAZEGENERATOREMPTY_H
#define MAZEGENERATOREMPTY_H

#include "mazegenerator.h"

/**
 * @class mazeGeneratorEmpty
 * @brief Generates an empty maze layout.
 * This class inherits from the MazeGenerator class and implements the generate method to create an empty maze.
 */
class mazeGeneratorEmpty : public mazeGenerator
{
 public:
    /**
     * @brief Constructor for mazeGeneratorEmpty.
     */
    mazeGeneratorEmpty();
    /**
     * @brief Generator for an empty maze.
     * @param maze The maze to be generated.
     */
    void generate(Maze& maze, bool isRefresh = false) override;
};

#endif // MAZEGENERATOREMPTY_H
