#include "mouse.h"

Mouse::Mouse(const Maze& maze, Logger<std::string>& logger, Maze& knownMaze) : position({0, 0}), maze(maze), logger(logger), knownMaze(knownMaze) {
    path.push_back(position);
    explorationPath.push_back(position);
}

void Mouse::move(Direction dir) {
    switch (dir) {
        case Direction::UP:
            position.y += 1;
            break;
        case Direction::DOWN:
            position.y -= 1;
            break;
        case Direction::LEFT:
            position.x -= 1;
            break;
        case Direction::RIGHT:
            position.x += 1;
            break;
    }
    logger.logData("Mouse moved to position: (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ")");
    path.push_back(position);
    explorationPath.push_back(position);
}

void Mouse::makeDecision(const SensorData& data) {
    Position start = position;
    Position goal = maze.getDestination();

    obstacles.push_back(data);
    if(data.frontObstacle) {
        knownMaze.addWall(position.x, position.y + 1);
    }
    if(data.leftObstacle) {
        knownMaze.addWall(position.x - 1, position.y);
    }
    if(data.rightObstacle) {
        knownMaze.addWall(position.x + 1, position.y);
    }
    if(data.backObstacle) {
        knownMaze.addWall(position.x, position.y - 1);
    }

    path = findPath(start, goal);

    if (!path.empty()) {
        Position next_move = path.front();
        path.erase(path.begin());
        if (next_move.x > position.x) {
            move(Direction::RIGHT);
        } else if (next_move.x < position.x) {
            move(Direction::LEFT);
        } else if (next_move.y > position.y) {
            move(Direction::UP);
        } else if (next_move.y < position.y) {
            move(Direction::DOWN);
        }
    }
}

Position Mouse::getPosition() const {
    return position;
}

std::vector<Position> Mouse::getPath() const {
    return path;
}

bool Mouse::isMoveValid(int x, int y) const {
    return knownMaze.isMoveValid(x, y);
}

std::vector<Position> Mouse::findPath(const Position& start, const Position& goal) {
    std::queue<Position> frontier;
    frontier.push(start);

    std::unordered_map<Position, Position> came_from;
    came_from[start] = start;

    while (!frontier.empty()) {
        Position current = frontier.front();
        frontier.pop();

        if (current == goal) {
            break;
        }

        std::vector<Position> neighbors = {
            {current.x, current.y + 1}, // Up
            {current.x + 1, current.y}, // Right
            {current.x, current.y - 1}, // Down
            {current.x - 1, current.y}  // Left
        };

        for (const Position& next : neighbors) {
            if (!isMoveValid(next.x, next.y)) continue;

            if (came_from.find(next) == came_from.end()) {
                frontier.push(next);
                came_from[next] = current;
            }
        }
    }

    std::vector<Position> path;
    Position current = goal;
    while (current != start) {
        path.push_back(current);
        current = came_from[current];
    }
    std::reverse(path.begin(), path.end());
    return path;
}

Direction Mouse::getDirection(const Position& from, const Position& to) const {
    if (to.x > from.x) return Direction::RIGHT;
    if (to.x < from.x) return Direction::LEFT;
    if (to.y > from.y) return Direction::UP;
    if (to.y < from.y) return Direction::DOWN;
    throw std::invalid_argument("Invalid direction");
}

void Mouse::calculateShortestPath() {
    std::queue<Position> frontier;
    frontier.push({0, 0});

    std::unordered_map<Position, Position> came_from;
    came_from[{0, 0}] = {0, 0};

    while (!frontier.empty()) {
        Position current = frontier.front();
        frontier.pop();

        if (current == maze.getDestination()) {
            break;
        }

        std::vector<Position> neighbors = {
            {current.x, current.y + 1}, // Up
            {current.x + 1, current.y}, // Right
            {current.x, current.y - 1}, // Down
            {current.x - 1, current.y}  // Left
        };

        for (const Position& next : neighbors) {
            if (!isMoveValid(next.x, next.y)) continue;

            if (came_from.find(next) == came_from.end()) {
                frontier.push(next);
                came_from[next] = current;
            }
        }
    }

    path.clear();
    Position current = maze.getDestination();
    while (current != Position{0, 0}) {
        path.push_back(current);
        current = came_from[current];
    }
    std::reverse(path.begin(), path.end());
}

void Mouse::reset() {
    this->position = {0, 0};
    this->path.clear();
    this->explorationPath.clear();
    this->obstacles.clear();
    this->knownMaze.generateEmptyMaze();
    path.push_back(position);
    explorationPath.push_back(position);
}

int Mouse::walkMaze(Logger<std::string> &sensorlogger, bool hasMaxMoves) {
    int moveCount = 0;
    while (!maze.isMazeSolved(this->getPosition()) && (hasMaxMoves ? true : (moveCount < 300))) {
        Position position = this->getPosition();
        SensorData sensorData = {
            !maze.isMoveValid(position.x, position.y + 1),
            !maze.isMoveValid(position.x - 1, position.y),
            !maze.isMoveValid(position.x + 1, position.y),
            !maze.isMoveValid(position.x, position.y - 1)
        };
        sensorlogger.logData("Sensor Data - Down: " + std::to_string(sensorData.frontObstacle) +
                             ", Left: " + std::to_string(sensorData.leftObstacle) +
                             ", Right: " + std::to_string(sensorData.rightObstacle) +
                             ", Up: " + std::to_string(sensorData.backObstacle));
        this->makeDecision(sensorData);
        moveCount++;
    }
    return moveCount;
}

void Mouse::walkMazeStep(Logger<std::string> &sensorlogger, std::set<Position, std::less<Position>>& visitedFields) {
    Position position = this->getPosition();
    SensorData sensorData = {
        !maze.isMoveValid(position.x, position.y + 1),
        !maze.isMoveValid(position.x - 1, position.y),
        !maze.isMoveValid(position.x + 1, position.y),
        !maze.isMoveValid(position.x, position.y - 1)
    };
    sensorlogger.logData("Sensor Data - Down: " + std::to_string(sensorData.frontObstacle) +
                         ", Left: " + std::to_string(sensorData.leftObstacle) +
                         ", Right: " + std::to_string(sensorData.rightObstacle) +
                         ", Up: " + std::to_string(sensorData.backObstacle));
    this->makeDecision(sensorData);
    visitedFields.insert(this->getPosition());
}