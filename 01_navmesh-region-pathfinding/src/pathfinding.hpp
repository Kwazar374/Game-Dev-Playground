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

    [[nodiscard]] AStarResult FindPath(const Grid& grid, std::pair<size_t, size_t> start, std::pair<size_t, size_t> goal);
    [[nodiscard]] size_t ManhattanDistance(std::pair<size_t, size_t> start, std::pair<size_t, size_t> goal) noexcept;
}
