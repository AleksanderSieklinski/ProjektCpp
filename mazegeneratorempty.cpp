#include "mazegeneratorempty.h"

mazeGeneratorEmpty::mazeGeneratorEmpty() {}

void mazeGeneratorEmpty::generate(Maze& maze, bool isRefresh) {
    int width = maze.getMazeLayout()[0].size();
    int height = maze.getMazeLayout().size();
    maze.uploadMazeLayout(std::vector<std::vector<int>>(height, std::vector<int>(width, 0)));
    maze.setDestination(width / 2, height / 2);
}
