#include "mainwindow.h"
#include "mouse.h"
#include "maze.h"
#include "logger.h"
#include <QApplication>
#include <QTimer>
#include <set>

Maze maze(7, 7);
Maze emptyMaze(7, 7);
Logger<std::string> logger("../micromouse.log");
Logger<std::string> sensorlogger("../micromousesensor.log");
Mouse mouse(maze, logger, emptyMaze);

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w(nullptr, maze, emptyMaze, logger, &mouse);
    w.show();

    emptyMaze.generateEmptyMaze();
    std::vector<std::vector<int>> mazeLayout = maze.getMazeLayout();
    w.drawMaze(mazeLayout, mouse.getPosition(), maze.getDestination());
    w.updatePositionLabel(mouse.getPosition());
    w.updateStatusLabel(SimulationState::NotStarted);

    QTimer *explorationTimer = new QTimer(&w);
    QTimer *returningTimer = new QTimer(&w);
    QTimer *runningTimer = new QTimer(&w);
    std::set<Position, std::less<Position>> visitedFields;
    Position originalDestination;
    size_t pathIndex = 0;
    int moveCount = 0;

    QObject::connect(w.getStartButton(), &QPushButton::clicked, [&]() {
        w.getStartButton()->setEnabled(false);
        w.getGenerateButton()->setEnabled(false);
        w.getStopButton()->setEnabled(true);
        pathIndex = 0;
        originalDestination = maze.getDestination();
        visitedFields.insert(mouse.getPosition());
        visitedFields.clear();
        explorationTimer->start(1000);
    });

    QObject::connect(w.getStopButton(), &QPushButton::clicked, [&]() {
        w.getStartButton()->setEnabled(true);
        w.getGenerateButton()->setEnabled(true);
        explorationTimer->stop();
        returningTimer->stop();
        runningTimer->stop();
        visitedFields.clear();
        pathIndex = 0;
    });

    QObject::connect(w.getGenerateButton(), &QPushButton::clicked, [&]() {
        visitedFields.clear();
        pathIndex = 0;
    });

    QObject::connect(explorationTimer, &QTimer::timeout, [&, moveCount]() mutable {
        if (!w.isExploring() || maze.isMazeSolved(mouse.getPosition()) || moveCount >= 300) {
            explorationTimer->stop();
            logger.logData("Exploration phase completed.");
            w.updateStatusLabel(SimulationState::Returning);
            returningTimer->start(1000);
            return;
        }
        Position position = mouse.getPosition();
        visitedFields.insert(mouse.getPosition());
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
        w.drawMaze(maze.getMazeLayout(), mouse.getPosition(), maze.getDestination());
        w.updatePositionLabel(mouse.getPosition());
        w.updateVisitedLabel(visitedFields.size());
        moveCount++;
    });

    QObject::connect(returningTimer, &QTimer::timeout, [&]() {
        maze.setDestination(0, 0);
        if (!w.isExploring() || maze.isMazeSolved(mouse.getPosition())) {
            returningTimer->stop();
            logger.logData("Mouse returned to start position.");
            w.updateStatusLabel(SimulationState::Running);
            maze.setDestination(originalDestination.x, originalDestination.y);
            mouse.calculateShortestPath();
            runningTimer->start(1000);
            return;
        }
        Position position = mouse.getPosition();
        visitedFields.insert(mouse.getPosition());
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
        w.drawMaze(maze.getMazeLayout(), mouse.getPosition(), maze.getDestination());
        w.updatePositionLabel(mouse.getPosition());
        w.updateVisitedLabel(visitedFields.size());
    });

    QObject::connect(runningTimer, &QTimer::timeout, [&]() {
        std::vector<Position> shortestPath = mouse.getPath();
        Position currentPos = mouse.getPosition();
        if (!w.isExploring() || pathIndex >= shortestPath.size() || maze.isMazeSolved(mouse.getPosition())) {
            runningTimer->stop();
            logger.logData("Maze solved!");
            w.updateStatusLabel(SimulationState::Finished);
            w.getStartButton()->setEnabled(true);
            w.getGenerateButton()->setEnabled(true);
            w.getStopButton()->setEnabled(false);
            return;
        }
        Direction dir = mouse.getDirection(currentPos, shortestPath[pathIndex]);
        mouse.move(dir);
        currentPos = shortestPath[pathIndex];
        pathIndex++;
        w.drawMaze(maze.getMazeLayout(), mouse.getPosition(), maze.getDestination());
        w.updatePositionLabel(mouse.getPosition());
        w.updateVisitedLabel(visitedFields.size());
    });

    return a.exec();
}
