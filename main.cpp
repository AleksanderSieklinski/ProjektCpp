#include "mainwindow.h"
#include "mouse.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    Maze maze(16, 16);
    Maze emptyMaze(16, 16);
    emptyMaze.generateEmptyMaze();
    Logger<std::string> logger("../micromouse.log");
    Logger<std::string> sensorlogger("../micromousesensor.log");
    Mouse mouse(maze, logger, emptyMaze);

    std::vector<std::vector<int>> mazee = maze.getMazeLayout();
    w.drawMaze(mazee);

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
        w.drawMaze(maze.getMazeLayout());
        QApplication::processEvents(); // Update the UI
    }
    logger.logData("Exploration phase completed.");

    // Return to start
    Position destination = maze.getDestination();
    maze.setDestination(0, 0);
    Position currentPos = mouse.getPosition();
    while (currentPos.x != 0 || currentPos.y != 0) {
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
        currentPos = mouse.getPosition();
        w.drawMaze(maze.getMazeLayout());
        QApplication::processEvents(); // Update the UI
    }
    logger.logData("Mouse returned to start position.");

    // Calculate the shortest path
    maze.setDestination(destination.x, destination.y);
    mouse.calculateShortestPath();
    std::vector<Position> shortestPath = mouse.getPath();
    currentPos = {0, 0};
    moveCount = 0;
    if (!shortestPath.empty()) {
        for (const Position& pos : shortestPath) {
            Direction dir = mouse.getDirection(currentPos, pos);
            mouse.move(dir);
            currentPos = pos;
            moveCount++;
            if (maze.isMazeSolved(mouse.getPosition())) {
                break;
            }
            w.drawMaze(maze.getMazeLayout());
            QApplication::processEvents(); // Update the UI
        }
    } else {
        std::cout << "No shortest path found." << std::endl;
    }
    logger.logData("Maze solved!");

    return a.exec();
}
