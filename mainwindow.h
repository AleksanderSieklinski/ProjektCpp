#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "mouse.h"
#include "controller.h"
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
* @brief Class for the main window of the application
* 
* This class is responsible for creating the main window of the application and handling the user interface.
* It contains the buttons for starting, stopping and generating the maze.
* It also contains the labels for the mouse position, the number of visited fields and the status of the simulation.
* The main window is updated by the simulation class.
*/
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    /**
    * @brief Constructor for MainWindow.
    * @param parent The parent widget.
    * @param controller The controller for handling the simulation logic.
    */
    MainWindow(QWidget *parent, Controller *controller);
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
    * @brief Updates the timer for the simulation.
    */
    void updateTimer();
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
    /**
    * @brief Starts the simulation.
    */
    void onStart();
    /**
    * @brief Stops the simulation.
    */
    void onStop();
    /**
    * @brief Generates a new maze.
    */
    void onUpdate();
    /**
    * @brief Resets the data of the main window and simulation.
    */
    void resetData();

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
    Controller *controller; ///< The controller for handling the simulation logic.
};

#endif // MAINWINDOW_H
