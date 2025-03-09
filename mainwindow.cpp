#include "mainwindow.h"
#include <QGraphicsRectItem>
#include <QTimer>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), exploring(false) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    QVBoxLayout *visualizationLayout = new QVBoxLayout();
    QVBoxLayout *controlLayout = new QVBoxLayout();

    // Obszar wizualizacji
    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    view->setScene(scene);
    scene->setSceneRect(0, 0, 400, 400);
    visualizationLayout->addWidget(view);

    // Przyciski sterujące
    startButton = new QPushButton("Start", this);
    controlLayout->addWidget(startButton);

    // Panel informacji
    statusLabel = new QLabel("Etap: Oczekiwanie", this);
    controlLayout->addWidget(statusLabel);

    // Układ główny
    mainLayout->addLayout(visualizationLayout);
    mainLayout->addLayout(controlLayout);

    resize(600, 500);
    setMinimumSize(800, 800);

    timer = new QTimer(this);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::startSimulation);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateSimulation);
}

void MainWindow::drawMaze(const std::vector<std::vector<int>> &maze) {
    scene->clear();
    int rows = maze.size();
    int cols = maze[0].size();
    int viewWidth = view->viewport()->width();
    int viewHeight = view->viewport()->height();
    int cellSize = std::min(viewWidth / cols, viewHeight / rows);

    for (size_t i = 0; i < maze.size(); ++i) {
        for (size_t j = 0; j < maze[i].size(); ++j) {
            if (maze[i][j] == 1) {
                scene->addRect(j * cellSize, i * cellSize, cellSize, cellSize, QPen(Qt::black), QBrush(Qt::black));
            }
        }
    }
    scene->setSceneRect(0, 0, cols * cellSize, rows * cellSize);
}

void MainWindow::startSimulation() {
    exploring = true;
    statusLabel->setText("Etap: Symulacja");
    timer->start(1000); // Start the timer with a 1-second interval
}

void MainWindow::updateSimulation() {
    if (!exploring) return;

    // Update the simulation logic here
    // For example, move the mouse and redraw the maze

    // If the simulation is complete, stop the timer
    // timer->stop();
}