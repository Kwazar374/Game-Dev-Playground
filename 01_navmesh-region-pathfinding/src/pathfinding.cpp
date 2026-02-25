#include "pathfinding.hpp"
#include "Grid.hpp"
#include <utility>
#include <vector>
#include <limits>
#include <queue>

size_t pathfinding::ManhattanDistance(std::pair<size_t, size_t> start, std::pair<size_t, size_t> goal)
{
    size_t dx = start.first > goal.first ? start.first - goal.first : goal.first - start.first;
    size_t dy = start.second > goal.second ? start.second - goal.second : goal.second - start.second;

    return dx + dy;
}

pathfinding::AStarResult pathfinding::FindPath(const Grid& grid, std::pair<size_t, size_t> start, std::pair<size_t, size_t> goal)
{
    struct Node
    {
        size_t index;
        int32_t f;
        int32_t g;
    };

    const size_t W = grid.Width();
    const size_t H = grid.Height();
    const size_t N = W * H;

    AStarResult result;
    result.found = false;
    result.closed.resize(N, 0);
    result.path.resize(N, 0);

    std::vector<uint8_t> state(N, 0); // 0 unseen, 1 open, 2 closed
    std::vector<int32_t> gScore(N, std::numeric_limits<int32_t>::max());
    std::vector<int32_t> parent(N, -1);
}