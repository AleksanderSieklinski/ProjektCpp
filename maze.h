#ifndef MAZE_H
#define MAZE_H

#include "position.h"
#include <random>
#include <stack>

/**
 * @class Maze
 * @brief Represents a maze with a layout and destination.
 */
class Maze {
public:
    /**
     * @brief Constructor for Maze.
     * @param width The width of the maze.
     * @param height The height of the maze.
     */
    Maze(int width, int height);

    /**
     * @brief Generates the maze layout using the prim algorithm.
     */
    void generateMazePrim();

    /**
    * @brief Generates the maze layout using the dfs algorithm.
    */
    void generateMazeDfs();

    /**
    *  @brief Generates an empty maze layout.
    */
    void generateEmptyMaze();

    /**
    *  @brief Adds a wall to the maze layout.
    *  @param x The x coordinate of the wall.
    *  @param y The y coordinate of the wall.
    */
    void addWall(int x, int y);

    /**
     * @brief Checks if a move is valid.
     * @param x The x coordinate of the move.
     * @param y The y coordinate of the move.
     * @return True if the move is valid, false otherwise.
     */
    bool isMoveValid(int x, int y) const;

    /**
     * @brief Prints the maze layout.
     * @param mousePosition The current position of the mouse.
     */
    void printMaze(const Position& mousePosition) const;

    /**
     * @brief Gets the maze layout.
     * @return A reference to the maze layout.
     */
    const std::vector<std::vector<int>>& getMazeLayout() const;

    /**
     * @brief Checks if the maze is solved.
     * @param mousePosition The current position of the mouse.
     * @return True if the maze is solved, false otherwise.
     */
    bool isMazeSolved(const Position& mousePosition) const;

    /**
     * @brief Gets the destination position in the maze.
     * @return The destination position.
     */
    Position getDestination() const;

    /**
     * @brief Uploads a custom maze layout.
     * @param customLayout The custom maze layout.
     * @return True if the upload was successful, false otherwise.
     */
    bool uploadMazeLayout(const std::vector<std::vector<int>>& customLayout);
    /**
     * @brief Change the destination of the maze.
     * @param x The x coordinate of the destination.
     * @param y The y coordinate of the destination.
     */
    void setDestination(int x, int y);

protected:
    int width; ///< The width of the maze
    int height; ///< The height of the maze
    std::vector<std::vector<int>> mazeLayout; ///< The layout of the maze
    Position destination; ///< The destination position in the maze
};

#endif // MAZE_H
