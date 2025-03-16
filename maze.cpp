#include "maze.h"

Maze::Maze(int width, int height) : width(width), height(height) {
    mazeLayout.resize(height, std::vector<int>(width, 1));
    generateMazePrim();
}

void Maze::generateMazePrim() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    std::vector<std::pair<int, int>> walls;
    int startX = 0;
    int startY = 0;
    mazeLayout[startY][startX] = 0;

    if (startX + 1 < width) walls.push_back({startX + 1, startY});
    if (startY + 1 < height) walls.push_back({startX, startY + 1});

    while (!walls.empty()) {
        std::shuffle(walls.begin(), walls.end(), std::mt19937{std::random_device{}()});
        auto [x, y] = walls.back();
        walls.pop_back();

        int wallCount = 0;
        if (x > 0 && mazeLayout[y][x - 1] == 0) wallCount++;
        if (x < width - 1 && mazeLayout[y][x + 1] == 0) wallCount++;
        if (y > 0 && mazeLayout[y - 1][x] == 0) wallCount++;
        if (y < height - 1 && mazeLayout[y + 1][x] == 0) wallCount++;

        if (wallCount == 1) {
            mazeLayout[y][x] = 0;
            if (x + 1 < width && mazeLayout[y][x + 1] == 1) walls.push_back({x + 1, y});
            if (x - 1 >= 0 && mazeLayout[y][x - 1] == 1) walls.push_back({x - 1, y});
            if (y + 1 < height && mazeLayout[y + 1][x] == 1) walls.push_back({x, y + 1});
            if (y - 1 >= 0 && mazeLayout[y - 1][x] == 1) walls.push_back({x, y - 1});
        }
    }

    int centerX = width / 2;
    int centerY = height / 2;

    for (int radius = 0; radius < std::max(width, height); ++radius) {
        for (int dx = -radius; dx <= radius; ++dx) {
            for (int dy = -radius; dy <= radius; ++dy) {
                int x = centerX + dx;
                int y = centerY + dy;
                if (x >= 0 && x < width && y >= 0 && y < height && mazeLayout[y][x] == 0) {
                    destination = {x, y};
                    return;
                }
            }
        }
    }
} // algorytm Prima

bool Maze::isMoveValid(int x, int y) const {
    return (x >= 0 && x < width && y >= 0 && y < height && mazeLayout[y][x] == 0);
}

void Maze::printMaze(const Position& mousePosition) const {
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
    if (customLayout.size() != height || customLayout[0].size() != width) {
        std::cerr << "Error: Uploaded maze layout size does not match the expected dimensions." << std::endl;
        return false;
    }
    mazeLayout = customLayout;
    return true;
}

void Maze::generateEmptyMaze() {
    mazeLayout = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
    destination = {width / 2, height / 2};
}

void Maze::addWall(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        mazeLayout[y][x] = 1;
    }
}

void Maze::setDestination(int x, int y) {
    if (x >= 0 && x < width && y >= 0 && y < height) {
        destination = {x, y};
    }
}
