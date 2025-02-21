#include "maze.h"
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <stack>
#include <algorithm>
#include <random>

// Constructor for the Maze class
Maze::Maze(int width, int height) : width(width), height(height) {
    // Initialize the maze layout with walls
    mazeLayout.resize(height, std::vector<int>(width, 1)); // 1 represents a wall
    generateMaze(); // Generate the maze structure
}

// Method to generate a random maze using a Randomized Depth-First Search algorithm
void Maze::generateMaze() {
    // Seed the random number generator
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Start from the bottom left corner
    int startX = 0;
    int startY = height - 1;

    std::stack<std::pair<int, int>> stack;
    stack.push(std::make_pair(startX, startY));
    mazeLayout[startY][startX] = 0; // 0 represents a path

    std::random_device rd;
    std::mt19937 g(rd());

    while (!stack.empty()) {
        auto [x, y] = stack.top();
        stack.pop();

        std::vector<std::pair<int, int>> neighbors;
        if (x > 1 && mazeLayout[y][x - 2] == 1) neighbors.push_back(std::make_pair(x - 2, y));
        if (x < width - 2 && mazeLayout[y][x + 2] == 1) neighbors.push_back(std::make_pair(x + 2, y));
        if (y > 1 && mazeLayout[y - 2][x] == 1) neighbors.push_back(std::make_pair(x, y - 2));
        if (y < height - 2 && mazeLayout[y + 2][x] == 1) neighbors.push_back(std::make_pair(x, y + 2));

        if (!neighbors.empty()) {
            stack.push(std::make_pair(x, y));
            std::shuffle(neighbors.begin(), neighbors.end(), g);
            auto [nx, ny] = neighbors.back();
            neighbors.pop_back();

            mazeLayout[ny][nx] = 0;
            mazeLayout[(y + ny) / 2][(x + nx) / 2] = 0; // Remove the wall between the current cell and the chosen cell
            stack.push(std::make_pair(nx, ny));
        }
    }

    // Ensure there is a path from the start to the center
    int centerX = width / 2;
    int centerY = height / 2;

    // Find the closest empty space near the center to mark as the destination
    for (int radius = 0; radius < std::max(width, height); ++radius) {
        for (int dx = -radius; dx <= radius; ++dx) {
            for (int dy = -radius; dy <= radius; ++dy) {
                int x = centerX + dx;
                int y = centerY + dy;
                if (x >= 0 && x < width && y >= 0 && y < height && mazeLayout[y][x] == 0) {
                    destination = std::make_pair(x, y);
                    return;
                }
            }
        }
    }
}

// Method to check if a move is valid
bool Maze::isMoveValid(int x, int y) const {
    // Check boundaries and if the cell is a wall
    return (x >= 0 && x < width && y >= 0 && y < height && mazeLayout[y][x] == 0);
}

// Method to print the maze layout
void Maze::printMaze(const Position& mousePosition) const {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (std::make_pair(j, i) == destination) {
                std::cout << "Y"; // Print 'Y' for the destination
            } else if (std::make_pair(j, i) == std::make_pair(0, height - 1)) {
                std::cout << "S"; // Print 'S' for the start
            } else if (std::make_pair(j, i) == std::make_pair(mousePosition.x, mousePosition.y)) {
                std::cout << "M"; // Print 'M' for the mouse's current position
            } else {
                std::cout << (mazeLayout[i][j] == 1 ? "X" : " "); // Print 'X' for walls and empty space for paths
            }
        }
        std::cout << std::endl;
    }
}

// Method to get the maze layout
const std::vector<std::vector<int>>& Maze::getMazeLayout() const {
    return mazeLayout;
}

// Method to check if the maze is solved (placeholder implementation)
bool Maze::isMazeSolved() const {
    // Placeholder logic for checking if the maze is solved
    // This should be replaced with actual logic to determine if the maze is solved
    return false;
}