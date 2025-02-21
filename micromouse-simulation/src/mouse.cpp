#include "mouse.h"
#include <iostream>

// Constructor to initialize the Mouse with default parameters
Mouse::Mouse(const Maze& maze) : speed(1), sensorRange(5), position({0, 0}), maze(maze) {}

// Method to move the mouse in a specified direction
void Mouse::move(Direction dir) {
    int newX = position.x;
    int newY = position.y;

    switch (dir) {
        case Direction::UP:
            newY += speed;
            break;
        case Direction::DOWN:
            newY -= speed;
            break;
        case Direction::LEFT:
            newX -= speed;
            break;
        case Direction::RIGHT:
            newX += speed;
            break;
    }

    if (isMoveValid(newX, newY)) {
        position.x = newX;
        position.y = newY;
        std::cout << "Mouse moved to position: (" << position.x << ", " << position.y << ")\n";
    } else {
        std::cout << "Invalid move to position: (" << newX << ", " << newY << ")\n";
    }
}

// Method to make a decision based on sensor data
void Mouse::makeDecision(const SensorData& data) {
    // Simple decision-making logic based on sensor readings
    if (!data.frontObstacle && isMoveValid(position.x, position.y + speed)) {
        move(Direction::UP);
    } else if (!data.rightObstacle && isMoveValid(position.x + speed, position.y)) {
        move(Direction::RIGHT);
    } else if (!data.leftObstacle && isMoveValid(position.x - speed, position.y)) {
        move(Direction::LEFT);
    } else if (!data.backObstacle && isMoveValid(position.x, position.y - speed)) {
        move(Direction::DOWN);
    } else {
        std::cout << "No valid moves available.\n";
    }
}

// Method to set parameters for the mouse
void Mouse::setParameters(int speed, int sensorRange) {
    this->speed = speed;
    this->sensorRange = sensorRange;
}

// Method to get the current position of the mouse
Position Mouse::getPosition() const {
    return position;
}

// Method to check if a move is valid
bool Mouse::isMoveValid(int x, int y) const {
    return maze.isMoveValid(x, y);
}