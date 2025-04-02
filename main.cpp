#include "mainwindow.h"
#define MAZE_SIZE 16

int main(int argc, char *argv[]) {
    Maze maze(MAZE_SIZE, MAZE_SIZE);
    mazeGeneratorPrim *mazeGenerator = new mazeGeneratorPrim();
    Maze emptyMaze(MAZE_SIZE, MAZE_SIZE);
    mazeGeneratorEmpty *emptyMazeGenerator = new mazeGeneratorEmpty();
    Logger<std::string> logger("../micromouse.log");
    Logger<std::string> sensorlogger("../micromousesensor.log");
    Mouse mouse(maze, logger, emptyMaze, emptyMazeGenerator);
    Controller controller(maze, &mouse, logger, mazeGenerator);
    QApplication a(argc, argv);
    MainWindow w(nullptr, &controller);
    w.show();
    mazeGenerator->generate(maze);
    emptyMazeGenerator->generate(emptyMaze);
    std::vector<std::vector<int>> mazeLayout = maze.getMazeLayout();
    w.drawMaze(mazeLayout, mouse.getPosition(), maze.getDestination());

    QTimer *explorationTimer = new QTimer(&w);
    QTimer *returningTimer = new QTimer(&w);
    QTimer *runningTimer = new QTimer(&w);
    std::set<Position, std::less<Position>> visitedFields;
    Position originalDestination;
    int moveCount = 0;

    QObject::connect(w.getStartButton(), &QPushButton::clicked, [&]() {
        w.getStartButton()->setEnabled(false);
        w.getGenerateButton()->setEnabled(false);
        w.getStopButton()->setEnabled(true);
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
    });

    QObject::connect(w.getGenerateButton(), &QPushButton::clicked, [&]() {
        visitedFields.clear();
    });

    QObject::connect(explorationTimer, &QTimer::timeout, [&]() {
        if (!controller.isExploring() || maze.isMazeSolved(mouse.getPosition()) || moveCount >= 300) {
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
        if (!controller.isExploring() || maze.isMazeSolved(mouse.getPosition())) {
            returningTimer->stop();
            logger.logData("Mouse returned to start position.");
            w.updateStatusLabel(SimulationState::Running);
            maze.setDestination(originalDestination.x, originalDestination.y);
            mouse.findPath(mouse.getPosition(), originalDestination, true);
            runningTimer->start(250);
            return;
        }
        mouse.walkMazeStep(sensorlogger, visitedFields);
        w.drawMaze(maze.getMazeLayout(), mouse.getPosition(), maze.getDestination());
        w.updatePositionLabel(mouse.getPosition());
        w.updateVisitedLabel(visitedFields.size());
    });

    QObject::connect(runningTimer, &QTimer::timeout, [&]() {
        if (!controller.isExploring() || maze.isMazeSolved(mouse.getPosition())) {
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
