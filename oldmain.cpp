#include "mouse.h"
#define MAZE_SIZE 16

int main() {
    Maze maze(MAZE_SIZE,MAZE_SIZE);
    Maze emptyMaze(MAZE_SIZE,MAZE_SIZE);
    emptyMaze.generateEmptyMaze();
    Logger<std::string> logger("../micromouse.log");
    Logger<std::string> sensorlogger("../micromousesensor.log");
    Mouse mouse(maze, logger, emptyMaze);
    std::set<Position, std::less<Position>> visitedFields;
    maze.generateMazePrim();
    maze.printMaze(mouse.getPosition());

    // Exploration phase
    int moveCount = 0;
    while (!maze.isMazeSolved(mouse.getPosition()) && moveCount < 300) {
        mouse.walkMazeStep(sensorlogger, visitedFields);
        moveCount++;
    }
    logger.logData("Exploration phase completed.");
    std::string movesMade = "Moves made: " + std::to_string(moveCount);

    // Return to start
    Position destination = maze.getDestination();
    maze.setDestination(0, 0);
    Position currentPos = mouse.getPosition();
    while (!maze.isMazeSolved(mouse.getPosition())) {
        mouse.walkMazeStep(sensorlogger, visitedFields);
    }
    logger.logData("Mouse returned to start position.");

    // Calculate the shortest path
    maze.setDestination(destination.x, destination.y);
    mouse.calculateShortestPath();
    moveCount = 0;
    // Final attempt
    currentPos = {0, 0};
    while (!maze.isMazeSolved(mouse.getPosition())) {
        mouse.walkMazeStep(sensorlogger, visitedFields);
        moveCount++;
    }
    logger.logData(movesMade);
    logger.logData("Final move count: " + std::to_string(moveCount));
    logger.logData("Maze solved!");
    return 0;
}
