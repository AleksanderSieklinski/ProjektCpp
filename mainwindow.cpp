#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent, Controller *controller)
    : QMainWindow(parent), controller(controller) {
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    QVBoxLayout *visualizationLayout = new QVBoxLayout();
    QVBoxLayout *controlLayout = new QVBoxLayout();

    view = new QGraphicsView(this);
    scene = new QGraphicsScene(this);
    view->setScene(scene);
    scene->setSceneRect(0, 0, 700, 1800);
    visualizationLayout->addWidget(view);

    startButton = new QPushButton("Start", this);
    stopButton = new QPushButton("Stop", this);
    generateButton = new QPushButton("Generuj nowy labirynt", this);
    controlLayout->addWidget(startButton);
    controlLayout->addWidget(stopButton);
    controlLayout->addWidget(generateButton);

    QString buttonStyle = R"(
        QPushButton {
            background-color: #ffc0cb;
            color: white;
            border: none;
            padding: 10px 20px;
            text-align: center;
            text-decoration: none;
            font-size: 16px;
            margin: 4px 2px;
        }
        QPushButton:hover {
            background-color: white;
            color: black;
            border: 2px solid #f0768b;
        }
    )";

    startButton->setStyleSheet(buttonStyle);
    stopButton->setStyleSheet(buttonStyle);
    generateButton->setStyleSheet(buttonStyle);

    QFont labelFont("Montserrat", 12);
    QPalette labelPalette;
    labelPalette.setColor(QPalette::WindowText, Qt::white);

    startButton->setFont(labelFont);
    stopButton->setFont(labelFont);
    generateButton->setFont(labelFont);

    statusLabel = new QLabel("Etap: Oczekiwanie", this);
    statusLabel->setFont(labelFont);
    statusLabel->setPalette(labelPalette);
    positionLabel = new QLabel("Pozycja: (0,0)", this);
    positionLabel->setFont(labelFont);
    positionLabel->setPalette(labelPalette);
    visitedLabel = new QLabel("Liczba odwiedzonych pól: 0", this);
    visitedLabel->setFont(labelFont);
    visitedLabel->setPalette(labelPalette);
    timeLabel = new QLabel("Czas: 0 ticks", this);
    timeLabel->setFont(labelFont);
    timeLabel->setPalette(labelPalette);

    controlLayout->addWidget(statusLabel);
    controlLayout->addWidget(positionLabel);
    controlLayout->addWidget(visitedLabel);
    controlLayout->addWidget(timeLabel);

    mainLayout->addLayout(visualizationLayout);
    mainLayout->addLayout(controlLayout);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateTimer);
    connect(startButton, &QPushButton::clicked, this, &MainWindow::onStart);
    connect(stopButton, &QPushButton::clicked, this, &MainWindow::onStop);
    connect(generateButton, &QPushButton::clicked, this, &MainWindow::onUpdate);
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
    QPixmap wallPixmap(":/images/wall.jpg");
    QPixmap mousePixmap(":/images/mouse.jpg");
    QPixmap cheesePixmap(":/images/cheese.jpg");
    QPixmap floorPixmap(":/images/floor.jpg");

    for (size_t i = 0; i < maze.size(); ++i) {
        for (size_t j = 0; j < maze[i].size(); ++j) {
            if (maze[i][j] == 1) {
                QGraphicsPixmapItem *wallItem = new QGraphicsPixmapItem(wallPixmap.scaled(cellSize, cellSize));
                wallItem->setPos(j * cellSize, i * cellSize);
                scene->addItem(wallItem);
            }
            else {
                QGraphicsPixmapItem *floorItem = new QGraphicsPixmapItem(floorPixmap.scaled(cellSize, cellSize));
                floorItem->setPos(j * cellSize, i * cellSize);
                scene->addItem(floorItem);
            }
        }
    }

    QGraphicsPixmapItem *mouseItem = new QGraphicsPixmapItem(mousePixmap.scaled(cellSize, cellSize));
    mouseItem->setPos(mousePosition.x * cellSize, mousePosition.y * cellSize);
    scene->addItem(mouseItem);

    QGraphicsPixmapItem *cheeseItem = new QGraphicsPixmapItem(cheesePixmap.scaled(cellSize, cellSize));
    cheeseItem->setPos(destinationPosition.x * cellSize, destinationPosition.y * cellSize);
    scene->addItem(cheeseItem);

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
    controller->changePhase(state);
    switch (state) {
        case SimulationState::NotStarted:
            statusLabel->setText("Etap: Oczekiwanie");
            break;
        case SimulationState::Exploring:
            statusLabel->setText("Etap: Eksploracja");
            break;
        case SimulationState::Returning:
            statusLabel->setText("Etap: Powrót");
            break;
        case SimulationState::Running:
            statusLabel->setText("Etap: Próba na czas");
            break;
        case SimulationState::Finished:
            statusLabel->setText("Etap: Zakończony");
            break;
    }
}

void MainWindow::onStart() {
    controller->startSimulation();
    updateStatusLabel(SimulationState::Exploring);
    timer->start(250);
}

void MainWindow::onStop() {
    controller->stopSimulation();
    timer->stop();
    updateStatusLabel(SimulationState::NotStarted);
}

void MainWindow::onUpdate() {
    controller->updateMaze();
    drawMaze(controller->getMazeLayout(), controller->getMousePosition(), controller->getMazeDestination());
}

void MainWindow::updateTimer() {
    controller->updateTimer();
    timeLabel->setText("Czas: " + QString::number(controller->getElapsedTime()) + " ticks");
}

void MainWindow::resetData() {
    controller->resetData();
    updatePositionLabel({0, 0});
    updateVisitedLabel(0);
    drawMaze(controller->getMazeLayout(), controller->getMousePosition(), controller->getMazeDestination());
}
