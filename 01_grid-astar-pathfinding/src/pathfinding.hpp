#pragma once

#include <utility>
#include <vector>
#include "Grid.hpp" 
#include "Position.hpp"

// The pathfinding namespace contains all the necessary data structures and functions for the A* pathfinding algorithm
namespace pathfinding {

    // Struct to hold the result of the A* pathfinding algorithm
    struct AStarResult
    {
        bool found;
        std::vector<uint8_t> closed;
        std::vector<uint8_t> path;
    };

    // Enum to represent the state of each node during the A* search
    // It's uint8_t to save memory, since we only need 3 states (Unseen, Open, Closed) which can be represented with 2 bits
    enum class NodeState : uint8_t
    {
        Unseen,
        Open,
        Closed
    };

    // Function declarations for the A* pathfinding algorithm and the heuristic function
    // [[nodiscard]] attribute indicates that the return value of the function should not be ignored
    [[nodiscard]] AStarResult FindPath(const Grid& grid, Position start, Position goal);
    [[nodiscard]] int32_t ManhattanDistance(Position start, Position goal) noexcept;
}
