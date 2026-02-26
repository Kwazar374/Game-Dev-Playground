#pragma once

#include <utility>
#include <vector>
#include "Grid.hpp" 
#include "Position.hpp"

namespace pathfinding {
    struct AStarResult
    {
        bool found;
        std::vector<uint8_t> closed;
        std::vector<uint8_t> path;
    };

    [[nodiscard]] AStarResult FindPath(const Grid& grid, Position start, Position goal);
    [[nodiscard]] int32_t ManhattanDistance(Position start, Position goal) noexcept;
}
