#ifndef POSITION_H
#define POSITION_H

#include <iostream>

/**
 * @class Position
 * @brief Represents a position in the maze with x and y coordinates.
 */
struct Position {
    int x; ///< The x coordinate of the position.
    int y; ///< The y coordinate of the position.

    /**
     * @brief Equality operator.
     * @param other The other position to compare with.
     * @return True if the positions are equal, false otherwise.
     */
    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }
    /**
     * @brief Inequality operator.
     * @param other The other position to compare with.
     * @return True if the positions are not equal, false otherwise.
     */
    bool operator!=(const Position& other) const {
        return !(*this == other);
    }
    /**
     * @brief Less than operator.
     * @param other The other position to compare with.
     * @return True if this position is less than the other position, false otherwise.
     */
    bool operator<(const Position& other) const {
        return std::tie(x, y) < std::tie(other.x, other.y);
    }
};

namespace std {
    template <>
    struct hash<Position> {
        /**
         * @brief Hash function for Position.
         * @param p The position to hash.
         * @return The hash value of the position.
         */
        std::size_t operator()(const Position& p) const noexcept {
            return std::hash<int>{}(p.x) ^ std::hash<int>{}(p.y);
        }
    };
}

#endif // POSITION_H