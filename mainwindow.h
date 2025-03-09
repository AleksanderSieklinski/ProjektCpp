#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mouse.h"
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QApplication>
#include <QGraphicsRectItem>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QFont>
#include <QPalette>

/** 
* @brief Enum class for the state of the simulation
*
* This enum class is used to represent the state of the simulation.
* The simulation can be in one of the following states: NotStarted, Exploring, Returning, Running, Finished.
*/
enum class SimulationState {
    NotStarted,
    Exploring,
    Returning,
    Running,
    Finished
};
/** 
* @brief Class for the main window of the application
* 
* This class is responsible for creating the main window of the application and handling the user interface.
* It contains the maze, the mouse, the logger and the buttons for starting, stopping and generating the maze.
* It also contains the labels for the mouse position, the number of visited fields and the status of the simulation.
* The main window is updated by the simulation class.
*/
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
    * @brief Constructor for MainWindow.
    * @param parent The parent widget.
    * @param maze The maze the mouse is navigating.
    * @param emptyMaze The empty maze for generating new mazes.
    * @param logger The logger for logging mouse actions.
    * @param mouse The mouse navigating through the maze.
    */
    MainWindow(QWidget *parent, Maze &maze, Maze &emptyMaze, Logger<std::string> &logger, Mouse *mouse);
    /**
    * @brief Draws the maze on the main window.
    * @param maze The maze to draw.
    * @param mousePosition The position of the mouse.
    * @param destinationPosition The position of the destination.
    */
    void drawMaze(const std::vector<std::vector<int>> &maze, const Position &mousePosition, const Position &destinationPosition);
    /**
    * @brief Updates the position label of the main window.
    * @param mousePosition The position of the mouse.
    */
    void updatePositionLabel(const Position &mousePosition);
    /**
    * @brief Updates the visited label of the main window.
    * @param visitedFields The number of visited fields.
    */
    void updateVisitedLabel(int visitedFields);
    /**
    * @brief Updates the status label of the main window.
    * @param state The state of the simulation.
    */
    void updateStatusLabel(SimulationState state);
    /**
    * @brief Gets the button for starting the simulation.
    * @return The button for starting the simulation.
    */
    QPushButton* getStartButton();
    /**
    * @brief Gets the button for stopping the simulation.
    * @return The button for stopping the simulation.
    */
    QPushButton* getStopButton();
    /**
    * @brief Gets the button for generating a new maze.
    * @return The button for generating a new maze.
    */
    QPushButton* getGenerateButton();

public slots:
    /**
    * @brief Starts the simulation.
    */
    void startSimulation();
    /**
    * @brief Stops the simulation.
    */
    void stopSimulation();
    /**
    * @brief Generates a new maze.
    */
    void updateMaze();
    /**
    * @brief Updates the timer for the simulation.
    */
    void updateTimer();
    /**
    * @brief Checks if the mouse is exploring the maze.
    * @return True if the mouse is exploring the maze, false otherwise.
    */
    bool isExploring();
    /**
    * @brief Resets the data of the main window and simulation.
    */
    void resetData();
    /**
    * @brief Gets the current state of the simulation.
    * @return The current state of the simulation.
    */
    SimulationState getCurrentState();

private:
    QGraphicsView *view; ///< The view for the maze.
    QGraphicsScene *scene; ///< The scene for the maze.
    QPushButton *startButton; ///< The button for starting the simulation.
    QPushButton *stopButton; ///< The button for stopping the simulation.
    QPushButton *generateButton; ///< The button for generating the maze.
    QLabel *statusLabel; ///< The label for the status of the simulation.
    QLabel *positionLabel; ///< The label for the mouse position.
    QLabel *visitedLabel; ///< The label for the number of visited fields.
    QLabel *timeLabel; ///< The label for the time elapsed.
    QTimer *timer; ///< The timer for updating the simulation.
    int elapsedTime; ///< The time elapsed since the start of the simulation.
    int moveCount; ///< The number of moves made by the mouse.
    bool exploring; ///< Flag indicating whether the mouse is moving inside the maze.
    SimulationState currentState; ///< The current state of the simulation
    Maze &maze; ///< The maze the mouse is navigating.
    Maze &emptyMaze; ///< The empty maze for generating new mazes.
    Logger<std::string> &logger; ///< The logger for logging mouse actions.
    Mouse *mouse; ///< The mouse navigating through the maze.
};

#endif // MAINWINDOW_H
