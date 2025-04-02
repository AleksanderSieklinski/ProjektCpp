#include "mazegeneratorprim.h"

mazeGeneratorPrim::mazeGeneratorPrim() {}

void mazeGeneratorPrim::generate(Maze& maze, bool isRefresh) {
    int width = maze.getMazeLayout()[0].size();
    int height = maze.getMazeLayout().size();
    std::vector<std::vector<int>> mazeLayout(height, std::vector<int>(width, 1));
    Position destination;
    if(!isRefresh) {
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
                    maze.setDestination(destination.x, destination.y);
                    maze.uploadMazeLayout(mazeLayout);
                    return;
                }
            }
        }
    }
}
