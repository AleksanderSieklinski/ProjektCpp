#include "maze.h"

Maze::Maze(int width, int height) {
    mazeLayout.resize(height, std::vector<int>(width, 1));
}

void Maze::printMaze(const Position& mousePosition) const {
    int width = mazeLayout[0].size();
    int height = mazeLayout.size();
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (Position{j, i} == destination) {
                std::cout << "[Y]";
            } else if (Position{j, i} == mousePosition) {
                std::cout << "[M]";
            } else {
                std::cout << (mazeLayout[i][j] == 1 ? "[*]" : "[ ]");
            }
        }
        std::cout << std::endl;
    }
}

const std::vector<std::vector<int>>& Maze::getMazeLayout() const {
    return mazeLayout;
}

bool Maze::isMazeSolved(const Position& mousePosition) const {
    return (mousePosition == destination);
}

Position Maze::getDestination() const {
    return destination;
}

bool Maze::uploadMazeLayout(const std::vector<std::vector<int>>& customLayout) {
    int width = mazeLayout[0].size();
    int height = mazeLayout.size();
    if (customLayout.size() != height || customLayout[0].size() != width) {
        std::cerr << "Error: Uploaded maze layout size does not match the expected dimensions." << std::endl;
        return false;
    }
    mazeLayout = customLayout;
    return true;
}

void Maze::addWall(int x, int y) {
    int width = mazeLayout[0].size();
    int height = mazeLayout.size();
    if (x >= 0 && x < width && y >= 0 && y < height) {
        mazeLayout[y][x] = 1;
    }
}

void Maze::setDestination(int x, int y) {
    int width = mazeLayout[0].size();
    int height = mazeLayout.size();
    if (x >= 0 && x < width && y >= 0 && y < height) {
        destination = {x, y};
    }
}
