#include <iostream>
#include "mouse.h"
#include "maze.h"

// Entry point of the Micromouse simulation application
int main() {
    // Initialize the maze and mouse objects with appropriate parameters
    Maze maze(16, 16); // Example dimensions for the maze
    Mouse mouse(maze);

    // Set up the maze layout
    maze.generateMaze();

    // Initialize the mouse parameters
    mouse.setParameters(1, 5); // Example parameters: speed = 1, sensorRange = 5

    // Start the simulation loop
    int i = 0;
    while (i < 6) {
        // Create sensor data based on the mouse's current position
        Position position = mouse.getPosition();
        std::cout << "Mouse position: (" << position.x << ", " << position.y << ")" << std::endl;
        SensorData sensorData = {
            !maze.isMoveValid(position.x, position.y + 1), // Front obstacle (moving up)
            !maze.isMoveValid(position.x - 1, position.y), // Left obstacle
            !maze.isMoveValid(position.x + 1, position.y), // Right obstacle
            !maze.isMoveValid(position.x, position.y - 1)  // Back obstacle (moving down)
        };

        // Print the sensor data
        std::cout << "Sensor Data - Front: " << sensorData.frontObstacle
                  << ", Left: " << sensorData.leftObstacle
                  << ", Right: " << sensorData.rightObstacle
                  << ", Back: " << sensorData.backObstacle << std::endl;

        // Print the maze layout
        maze.printMaze(position);

        // Make a decision based on the current sensor data
        mouse.makeDecision(sensorData);

        // Log the current state of the simulation
        position = mouse.getPosition();
        std::cout << "Mouse position: (" << position.x << ", " << position.y << ")" << std::endl;
        i++;
    }

    std::cout << "Maze solved!" << std::endl;
    return 0;
}