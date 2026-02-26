#include "pathfinding.hpp"
#include "Grid.hpp"
#include <utility>
#include <vector>
#include <limits>
#include <queue>

int32_t pathfinding::ManhattanDistance(std::pair<int32_t, int32_t> start, std::pair<int32_t, int32_t> goal) noexcept
{
    int32_t dx = start.first > goal.first ? start.first - goal.first : goal.first - start.first;
    int32_t dy = start.second > goal.second ? start.second - goal.second : goal.second - start.second;

    return dx + dy;
}

pathfinding::AStarResult pathfinding::FindPath(const Grid& grid, std::pair<int32_t, int32_t> start, std::pair<int32_t, int32_t> goal)
{
    struct Node
    {
        int32_t index;
        int32_t g;  // cost from start
        int32_t f;  // total estimated cost
    };

    struct Compare
    {
        bool operator()(const Node& a, const Node& b) const
        {
            return a.f > b.f;
        }
    };

    // grid
    const int32_t W = grid.Width();
    const int32_t H = grid.Height();
    const int32_t N = W * H;

    // result
    AStarResult result;
    result.found = false;
    result.closed.resize(N, 0);
    result.path.resize(N, 0);

    // pathfinding
    std::vector<uint8_t> state(N, 0); // 0 unseen, 1 open, 2 closed
    std::vector<int32_t> gScore(N, std::numeric_limits<int32_t>::max());
    std::vector<int32_t> parent(N, -1);
    std::vector<std::pair<int32_t, int32_t>> neighboursOffsets {
        std::pair<int32_t, int32_t>(-1, 0),
        std::pair<int32_t, int32_t>(0, -1),
        std::pair<int32_t, int32_t>(0, 1),
        std::pair<int32_t, int32_t>(1, 0),
    };

    std::priority_queue<Node, std::vector<Node>, Compare> openSet;

    int32_t startIndex = grid.Index(start.first, start.second);
    int32_t goalIndex = grid.Index(goal.first, goal.second);

    int32_t h = pathfinding::ManhattanDistance(start, goal);
    state[startIndex] = 1;
    gScore[startIndex] = 0;
    parent[startIndex] = static_cast<int32_t>(startIndex);
    
    // add the start node to open
    openSet.push(
        {
            startIndex,
            gScore[startIndex],
            gScore[startIndex] + static_cast<int32_t>(h)
    });

    while (!openSet.empty())
    {
        Node current = openSet.top();
        openSet.pop();
        
        if (current.g != gScore[current.index])
        {
            continue;
        }
        
        state[current.index] = 2;
        result.closed[current.index] = 1;
        
        if (current.index == goalIndex)
        {
            result.found = true;
            break;
        }

        int32_t x = current.index % W;
        int32_t y = current.index / W;

        // for each neighbour
        for (int i = 0; i < 4; ++i)
        {
            int32_t neighbourX = x + neighboursOffsets[i].first;
            int32_t neighbourY = y + neighboursOffsets[i].second;
            if (!grid.InBounds(neighbourX, neighbourY))
            {
                continue;
            }

            int32_t neighbourIndex = grid.Index(neighbourX, neighbourY);

            if (grid.IsWall(neighbourX, neighbourY))
            {
                continue;
            }
            if (state[neighbourIndex] == 2)
            {
                continue;
            }

            int32_t G = gScore[current.index] + 1;
            if (G < gScore[neighbourIndex])
            {
                gScore[neighbourIndex] = G;
                parent[neighbourIndex] = static_cast<int32_t>(current.index);
                state[neighbourIndex] = 1; // open
                int32_t H = static_cast<int32_t>(pathfinding::ManhattanDistance(
                    std::pair<int32_t, int32_t>(neighbourX, neighbourY),
                    goal
                ));
                int32_t F = G + H;
                openSet.push({neighbourIndex, G, F});
            } 
        }
    }

    if (result.found)
    {
        if (parent[goalIndex] < 0)
        {
            result.found = false;
        }
        else
        {

            int32_t index = goalIndex;
            int32_t stepCounter = 0;
            while (index != startIndex && stepCounter < N)
            {
                result.path[index] = 1;
                if (parent[index] < 0)
                {
                    result.found = false;
                    break;
                }
                index = parent[index];
                ++stepCounter;
            }
            if (index == startIndex)
            {
                result.path[startIndex] = 1;
            }
            else
            {
                result.found = false;
            }
        }
    }

    return result;
}