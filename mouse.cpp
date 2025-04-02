#include "mouse.h"

Mouse::Mouse(const Maze& maze, Logger<std::string>& logger, Maze& knownMaze, mazeGeneratorEmpty* emptyMazeGenerator) : position({0, 0}), maze(maze), logger(logger), knownMaze(knownMaze), emptyMazeGenerator(emptyMazeGenerator) {
    path.push_back(position);
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
}

void Mouse::makeDecision(const SensorData& data) {
    Position start = position;
    Position goal = maze.getDestination();

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

std::vector<Position> Mouse::findPath(const Position& start, const Position& goal, const bool isFinal) {
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
            {current.x, current.y + 1},
            {current.x + 1, current.y},
            {current.x, current.y - 1},
            {current.x - 1, current.y}
        };

        for (const Position& next : neighbors) {
            if (!this->canMove(next.x, next.y, knownMaze)) continue;

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
    if(isFinal) {
        this->path = path;
    }
    return path;
}

void Mouse::reset() {
    this->position = {0, 0};
    this->path.clear();
    this->emptyMazeGenerator->generate(knownMaze, true);
    path.push_back(position);
}

void Mouse::walkMazeStep(Logger<std::string> &sensorlogger, std::set<Position, std::less<Position>>& visitedFields) {
    Position position = this->getPosition();
    SensorData sensorData = {
        !this->canMove(position.x, position.y + 1, maze),
        !this->canMove(position.x - 1, position.y, maze),
        !this->canMove(position.x + 1, position.y, maze),
        !this->canMove(position.x, position.y - 1, maze)
    };
    sensorlogger.logData("Sensor Data - Down: " + std::to_string(sensorData.frontObstacle) +
                         ", Left: " + std::to_string(sensorData.leftObstacle) +
                         ", Right: " + std::to_string(sensorData.rightObstacle) +
                         ", Up: " + std::to_string(sensorData.backObstacle));
    this->makeDecision(sensorData);
    visitedFields.insert(this->getPosition());
}

bool Mouse::canMove(int x, int y, const Maze& maze) {
    int width = maze.getMazeLayout()[0].size();
    int height = maze.getMazeLayout().size();
    return (x >= 0 && x < width && y >= 0 && y < height && maze.getMazeLayout()[y][x] == 0);
}