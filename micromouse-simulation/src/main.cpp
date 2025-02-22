#include "mouse.h"

int main() {
    Maze maze(16, 16);
    Logger<std::string> logger("../micromouse.log");
    Logger<std::string> sensorlogger("../micromousesensor.log");
    Mouse mouse(maze, logger);
    maze.generateMaze();
    maze.printMaze(mouse.getPosition());

    // Exploration phase
    int maxMoves = 300;
    int moveCount = 0;

    while (!maze.isMazeSolved(mouse.getPosition()) && moveCount < maxMoves) {
        Position position = mouse.getPosition();
        SensorData sensorData = {
            !maze.isMoveValid(position.x, position.y + 1),
            !maze.isMoveValid(position.x - 1, position.y),
            !maze.isMoveValid(position.x + 1, position.y),
            !maze.isMoveValid(position.x, position.y - 1)
        };
        sensorlogger.logData("Sensor Data - Down: " + std::to_string(sensorData.frontObstacle) +
                       ", Left: " + std::to_string(sensorData.leftObstacle) +
                       ", Right: " + std::to_string(sensorData.rightObstacle) +
                       ", Up: " + std::to_string(sensorData.backObstacle));
        mouse.makeDecision(sensorData);
        moveCount++;
    }
    logger.logData("Exploration phase completed.");
    // Calculate the shortest path based on exploration data
    mouse.calculateShortestPath();
    std::vector<Position> shortestPath = mouse.getPath();

    // Return to start
    std::vector<Position> returnPath = mouse.findPath(mouse.getPosition(), {0, 0});
    Position currentPos = mouse.getPosition();
    for (const Position& pos : returnPath) {
        Direction dir = mouse.getDirection(currentPos, pos);
        mouse.move(dir);
        currentPos = pos;
    }
    logger.logData("Mouse returned to start position.");

    // Final attempt using the shortest path
    currentPos = {0, 0};
    if (!shortestPath.empty()) {
        std::cout << "Shortest path: ";
        for (const Position& pos : shortestPath) {
            std::cout << "(" << pos.x << ", " << pos.y << ") ";
        }
        std::cout << std::endl;

        for (const Position& pos : shortestPath) {
            Direction dir = mouse.getDirection(currentPos, pos);
            mouse.move(dir);
            currentPos = pos;
            if (maze.isMazeSolved(mouse.getPosition())) {
                break;
            }
        }
    } else {
        std::cout << "No shortest path found." << std::endl;
    }
    std::cout << "Maze solved!" << std::endl;
    return 0;
}