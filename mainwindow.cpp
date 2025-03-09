#include "mainwindow.h"
#include <QGraphicsRectItem>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent, Maze &maze, Maze &emptyMaze, Logger<std::string> &logger, Mouse *mouse)
    : QMainWindow(parent), elapsedTime(0), moveCount(0), exploring(false), maze(maze), emptyMaze(emptyMaze), logger(logger), mouse(mouse) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    QVBoxLayout *visualizationLayout = new QVBoxLayout();
    QVBoxLayout *controlLayout = new QVBoxLayout();

    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    view->setScene(scene);
    scene->setSceneRect(0, 0, 400, 400);
    visualizationLayout->addWidget(view);

    startButton = new QPushButton("Start", this);
    stopButton = new QPushButton("Stop", this);
    generateButton = new QPushButton("Generuj nowy labirynt", this);
    controlLayout->addWidget(startButton);
    controlLayout->addWidget(stopButton);
    controlLayout->addWidget(generateButton);

    statusLabel = new QLabel("Etap: Oczekiwanie", this);
    positionLabel = new QLabel("Pozycja: (0,0)", this);
    visitedLabel = new QLabel("Liczba odwiedzonych pól: 0", this);
    timeLabel = new QLabel("Czas: 0s", this);
    controlLayout->addWidget(statusLabel);
    controlLayout->addWidget(positionLabel);
    controlLayout->addWidget(visitedLabel);
    controlLayout->addWidget(timeLabel);

    mainLayout->addLayout(visualizationLayout);
    mainLayout->addLayout(controlLayout);

    resize(1000, 900);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startSimulation);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::stopSimulation);
    connect(generateButton, &QPushButton::clicked, this, &MainWindow::updateMaze);
}

QPushButton* MainWindow::getStartButton() {
    return startButton;
}

QPushButton* MainWindow::getStopButton() {
    return stopButton;
}

QPushButton* MainWindow::getGenerateButton() {
    return generateButton;
}

void MainWindow::drawMaze(const std::vector<std::vector<int>> &maze, const Position &mousePosition, const Position &destinationPosition) {
    scene->clear();
    int rows = maze.size();
    int cols = maze[0].size();
    int viewWidth = view->viewport()->width();
    int viewHeight = view->viewport()->height();
    int cellSize = std::min(viewWidth / cols, viewHeight / rows);

    for (size_t i = 0; i < maze.size(); ++i) {
        for (size_t j = 0; j < maze[i].size(); ++j) {
            if (maze[i][j] == 1) {
                scene->addRect(j * cellSize, i * cellSize, cellSize, cellSize, QPen(Qt::white), QBrush(Qt::white));
            }
        }
    }

    scene->addEllipse(mousePosition.x * cellSize, mousePosition.y * cellSize, cellSize, cellSize, QPen(Qt::red), QBrush(Qt::red));

    scene->addEllipse(destinationPosition.x * cellSize, destinationPosition.y * cellSize, cellSize, cellSize, QPen(Qt::green), QBrush(Qt::green));

    scene->addRect(0, 0, cols * cellSize, rows * cellSize, QPen(Qt::white, 2));

    scene->setSceneRect(0, 0, cols * cellSize, rows * cellSize);
}

void MainWindow::updatePositionLabel(const Position &mousePosition) {
    positionLabel->setText("Pozycja: (" + QString::number(mousePosition.x) + "," + QString::number(mousePosition.y) + ")");
}

void MainWindow::updateVisitedLabel(int visitedFields) {
    visitedLabel->setText("Liczba odwiedzonych pól: " + QString::number(visitedFields));
}

void MainWindow::updateStatusLabel(SimulationState state) {
    switch (state) {
        case SimulationState::NotStarted:
            statusLabel->setText("Etap: Oczekiwanie");
            exploring = false;
            break;
        case SimulationState::Exploring:
            statusLabel->setText("Etap: Eksploracja");
            exploring = true;
            break;
        case SimulationState::Returning:
            statusLabel->setText("Etap: Powrót");
            break;
        case SimulationState::Running:
            statusLabel->setText("Etap: Uruchomienie");
            break;
        case SimulationState::Finished:
            statusLabel->setText("Etap: Zakończony");
            exploring = false;
            break;
    }
}

void MainWindow::startSimulation() {
    updateStatusLabel(SimulationState::Exploring);
    resetData();
    timer->start(1000);
}

void MainWindow::stopSimulation() {
    timer->stop();
    updateStatusLabel(SimulationState::NotStarted);
    resetData();
}

void MainWindow::updateMaze() {
    Maze newMaze = Maze(maze.getMazeLayout().size(), maze.getMazeLayout()[0].size());
    maze.uploadMazeLayout(newMaze.getMazeLayout());
    maze.generateMaze();
    mouse->reset(maze, logger, emptyMaze);
    drawMaze(maze.getMazeLayout(), mouse->getPosition(), maze.getDestination());
}

void MainWindow::updateTimer() {
    elapsedTime++;
    timeLabel->setText("Czas: " + QString::number(elapsedTime) + "s");
}

bool MainWindow::isExploring() {
    return exploring;
}

void MainWindow::resetData() {
    elapsedTime = 0;
    moveCount = 0;
    updatePositionLabel({0, 0});
    updateVisitedLabel(0);
    timeLabel->setText("Czas: 0s");
    maze.generateMaze();
    mouse->reset(maze, logger, emptyMaze);
    drawMaze(maze.getMazeLayout(), mouse->getPosition(), maze.getDestination());
}