#pragma once
#include "Grid.hpp" 
#include <utility>
#include <vector>

namespace pathfinding {
    struct AStarResult
    {
        bool found;
        std::vector<uint8_t> closed;
        std::vector<uint8_t> path;
    };

    [[nodiscard]] AStarResult FindPath(const Grid& grid, std::pair<int32_t, int32_t> start, std::pair<int32_t, int32_t> goal);
    [[nodiscard]] int32_t ManhattanDistance(std::pair<int32_t, int32_t> start, std::pair<int32_t, int32_t> goal) noexcept;
}
