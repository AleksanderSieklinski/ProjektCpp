#include "mouse.h"
#define MAZE_SIZE 16

int mainOld() {
    Maze maze(MAZE_SIZE,MAZE_SIZE);
    Maze emptyMaze(MAZE_SIZE,MAZE_SIZE);
    emptyMaze.generateEmptyMaze();
    Logger<std::string> logger("../micromouse.log");
    Logger<std::string> sensorlogger("../micromousesensor.log");
    Mouse mouse(maze, logger, emptyMaze);
    maze.generateMazePrim();
    maze.printMaze(mouse.getPosition());

    // Exploration phase
    int moveCount = mouse.walkMaze(sensorlogger, true);
    logger.logData("Exploration phase completed.");
    std::string movesMade = "Moves made: " + std::to_string(moveCount);

    /// Return to start
    Position destination = maze.getDestination();
    maze.setDestination(0, 0);
    Position currentPos = mouse.getPosition();
    mouse.walkMaze(sensorlogger);
    logger.logData("Mouse returned to start position.");

    // Calculate the shortest path
    maze.setDestination(destination.x, destination.y);
    mouse.calculateShortestPath();
    std::vector<Position> shortestPath = mouse.getPath();

    // Final attempt
    currentPos = {0, 0};
    moveCount = mouse.walkMaze(sensorlogger);
    logger.logData(movesMade);
    logger.logData("Final move count: " + std::to_string(moveCount));
    logger.logData("Maze solved!");
    return 0;
}