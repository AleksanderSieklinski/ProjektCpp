#ifndef MOUSE_H
#define MOUSE_H

#include <utility>
#include "maze.h"

// Enum representing the possible directions the mouse can move
enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

// Struct representing the sensor data
struct SensorData {
    bool frontObstacle;
    bool leftObstacle;
    bool rightObstacle;
    bool backObstacle;
};

// Mouse class represents the Micromouse robot
class Mouse {
public:
    // Constructor to initialize the mouse with default parameters
    Mouse(const Maze& maze);

    // Method to set parameters like speed and sensor range
    void setParameters(int speed, int sensorRange);

    // Method to make decisions based on sensor data
    void makeDecision(const SensorData& data);

    // Method to move the mouse in the maze
    void move(Direction dir);

    // Method to get the current position of the mouse
    Position getPosition() const;

private:
    int speed;          // Speed of the mouse
    int sensorRange;    // Range of the mouse's sensors
    Position position;  // Position of the mouse
    const Maze& maze;   // Reference to the maze

    // Method to check if a move is valid
    bool isMoveValid(int x, int y) const;
};

#endif // MOUSE_H