#include "mouse.h"
#include "mazegeneratorprim.h"
#include "mazegeneratorempty.h"
#define MAZE_SIZE 16

int oldmain() {
    Maze maze(MAZE_SIZE,MAZE_SIZE);
    Maze emptyMaze(MAZE_SIZE,MAZE_SIZE);
    mazeGeneratorEmpty emptyMazeGenerator;
    emptyMazeGenerator.generate(emptyMaze);
    Logger<std::string> logger("../micromouse.log");
    Logger<std::string> sensorlogger("../micromousesensor.log");
    Mouse mouse(maze, logger, emptyMaze, &emptyMazeGenerator);
    std::set<Position, std::less<Position>> visitedFields;
    mazeGeneratorPrim mazeGenerator;
    mazeGenerator.generate(maze);
    maze.printMaze(mouse.getPosition());

    int moveCount = 0;
    while (!maze.isMazeSolved(mouse.getPosition()) && moveCount < 300) {
        mouse.walkMazeStep(sensorlogger, visitedFields);
        moveCount++;
    }
    logger.logData("Exploration phase completed.");
    std::string movesMade = "Moves made: " + std::to_string(moveCount);

    Position destination = maze.getDestination();
    maze.setDestination(0, 0);
    Position currentPos = mouse.getPosition();
    while (!maze.isMazeSolved(mouse.getPosition())) {
        mouse.walkMazeStep(sensorlogger, visitedFields);
    }
    logger.logData("Mouse returned to start position.");

    maze.setDestination(destination.x, destination.y);
    mouse.findPath(currentPos, destination, true);
    moveCount = 0;

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
