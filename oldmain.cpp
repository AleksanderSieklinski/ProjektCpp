// #include "mouse.h"

// int main() {
//     Maze maze(16,16);
//     Maze emptyMaze(16,16);
//     emptyMaze.generateEmptyMaze();
//     Logger<std::string> logger("../micromouse.log");
//     Logger<std::string> sensorlogger("../micromousesensor.log");
//     Mouse mouse(maze, logger, emptyMaze);
//     //    std::vector<std::vector<int>> mazeLayout = {
//     //        {0, 0, 0, 1, 0},
//     //        {0, 1, 0, 1, 1},
//     //        {0, 1, 0, 0, 0},
//     //        {0, 1, 1, 1, 0},
//     //        {0, 0, 0, 0, 0}
//     //    };
//     //    maze.uploadMazeLayout(mazeLayout);
//     maze.generateMaze();
//     maze.printMaze(mouse.getPosition());
//     std::cout << std::endl;

//     // Exploration phase
//     int maxMoves = 300;
//     int moveCount = 0;
//     while (!maze.isMazeSolved(mouse.getPosition()) && moveCount < maxMoves) {
//         Position position = mouse.getPosition();
//         SensorData sensorData = {
//             !maze.isMoveValid(position.x, position.y + 1),
//             !maze.isMoveValid(position.x - 1, position.y),
//             !maze.isMoveValid(position.x + 1, position.y),
//             !maze.isMoveValid(position.x, position.y - 1)
//         };
//         sensorlogger.logData("Sensor Data - Down: " + std::to_string(sensorData.frontObstacle) +
//                              ", Left: " + std::to_string(sensorData.leftObstacle) +
//                              ", Right: " + std::to_string(sensorData.rightObstacle) +
//                              ", Up: " + std::to_string(sensorData.backObstacle));
//         mouse.makeDecision(sensorData);
//         std::cout << "Move count: " << moveCount << std::endl;
//         moveCount++;
//     }
//     logger.logData("Exploration phase completed.");
//     std::string movesMade = "Moves made: " + std::to_string(moveCount);

//     /// Return to start
//     Position destination = maze.getDestination();
//     maze.setDestination(0, 0);
//     Position currentPos = mouse.getPosition();
//     while (currentPos.x != 0 || currentPos.y != 0) {
//         Position position = mouse.getPosition();
//         SensorData sensorData = {
//             !maze.isMoveValid(position.x, position.y + 1),
//             !maze.isMoveValid(position.x - 1, position.y),
//             !maze.isMoveValid(position.x + 1, position.y),
//             !maze.isMoveValid(position.x, position.y - 1)
//         };
//         sensorlogger.logData("Sensor Data - Down: " + std::to_string(sensorData.frontObstacle) +
//                              ", Left: " + std::to_string(sensorData.leftObstacle) +
//                              ", Right: " + std::to_string(sensorData.rightObstacle) +
//                              ", Up: " + std::to_string(sensorData.backObstacle));
//         mouse.makeDecision(sensorData);
//         currentPos = mouse.getPosition();
//     }
//     logger.logData("Mouse returned to start position.");

//     // Calculate the shortest path
//     maze.setDestination(destination.x, destination.y);
//     mouse.calculateShortestPath();
//     std::vector<Position> shortestPath = mouse.getPath();

//     // Final attempt
//     currentPos = {0, 0};
//     moveCount = 0;
//     if (!shortestPath.empty()) {
//         std::cout << "Shortest path: ";
//         for (const Position& pos : shortestPath) {
//             std::cout << "(" << pos.x << ", " << pos.y << ") ";
//         }
//         std::cout << std::endl;

//         for (const Position& pos : shortestPath) {
//             Direction dir = mouse.getDirection(currentPos, pos);
//             mouse.move(dir);
//             currentPos = pos;
//             moveCount++;
//             if (maze.isMazeSolved(mouse.getPosition())) {
//                 break;
//             }
//         }
//     } else {
//         std::cout << "No shortest path found." << std::endl;
//     }
//     std::cout << movesMade << std::endl;
//     logger.logData(movesMade);
//     std::cout << "Final move count: " << moveCount << std::endl;
//     logger.logData("Final move count: " + std::to_string(moveCount));
//     std::cout << "Maze solved!" << std::endl;
//     logger.logData("Maze solved!");
//     return 0;
// }
