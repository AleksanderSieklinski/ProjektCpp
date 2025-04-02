#ifndef MAZEGENERATORPRIM_H
#define MAZEGENERATORPRIM_H

#include "mazegenerator.h"

/**
 * @class mazeGeneratorPrim
 * @brief Generates a maze layout using the Prim algorithm.
 * This class inherits from the MazeGenerator class and implements the generate method to create a maze using the Prim algorithm.
 */
class mazeGeneratorPrim : public mazeGenerator
{
public:
    /**
     * @brief Constructor for mazeGeneratorPrim.
     */
    mazeGeneratorPrim();

    /**
     * @brief Generates a maze layout using the Prim algorithm.
     * @param maze The maze to be generated.
     */
    void generate(Maze& maze, bool isRefresh = false) override;
};

#endif // MAZEGENERATORPRIM_H
