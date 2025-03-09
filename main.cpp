#include "mainwindow.h"
#define MAZE_SIZE 4
Maze maze(MAZE_SIZE, MAZE_SIZE);
Maze emptyMaze(MAZE_SIZE, MAZE_SIZE);
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
        explorationTimer->start(250);
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

    QObject::connect(explorationTimer, &QTimer::timeout, [&]() {
        if (!w.isExploring() || maze.isMazeSolved(mouse.getPosition()) || moveCount >= 300) {
            explorationTimer->stop();
            logger.logData("Exploration phase completed.");
            w.updateStatusLabel(SimulationState::Returning);
            returningTimer->start(250);
            return;
        }
        mouse.walkMazeStep(sensorlogger, visitedFields);
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
            runningTimer->start(250);
            return;
        }
        mouse.walkMazeStep(sensorlogger, visitedFields);
        w.drawMaze(maze.getMazeLayout(), mouse.getPosition(), maze.getDestination());
        w.updatePositionLabel(mouse.getPosition());
        w.updateVisitedLabel(visitedFields.size());
    });

    QObject::connect(runningTimer, &QTimer::timeout, [&]() {
        if (!w.isExploring() || maze.isMazeSolved(mouse.getPosition())) {
            runningTimer->stop();
            logger.logData("Maze solved!");
            w.updateStatusLabel(SimulationState::Finished);
            w.getStartButton()->setEnabled(true);
            w.getGenerateButton()->setEnabled(true);
            w.getStopButton()->setEnabled(false);
            return;
        }
        mouse.walkMazeStep(sensorlogger, visitedFields);
        w.drawMaze(maze.getMazeLayout(), mouse.getPosition(), maze.getDestination());
        w.updatePositionLabel(mouse.getPosition());
        w.updateVisitedLabel(visitedFields.size());
    });

    return a.exec();
}