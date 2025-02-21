#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <iostream>

// Struct representing the position of the mouse
struct Position {
    int x;
    int y;
};

// Class representing the Maze structure
class Maze {
public:
    // Constructor to initialize the maze with given dimensions
    Maze(int, int);

    // Method to generate a random maze layout
    void generateMaze();

    // Method to check if a move is valid
    bool isMoveValid(int, int) const;

    // Method to get the current maze layout
    const std::vector<std::vector<int>>& getMazeLayout() const;

    // Method to check if the maze is solved
    bool isMazeSolved() const;

    // Method to print the maze layout
    void printMaze(const Position&) const;

private:
    int width;  // Width of the maze
    int height; // Height of the maze
    std::vector<std::vector<int>> mazeLayout; // 2D vector representing the maze layout
    std::pair<int, int> destination; // Coordinates of the destination

    // Helper method to initialize the maze layout
    void initializeLayout();
};

#endif // MAZE_H