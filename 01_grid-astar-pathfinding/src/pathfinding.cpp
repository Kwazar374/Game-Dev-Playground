#include <utility>
#include <vector>
#include <limits>
#include <queue>
#include <array>
#include "pathfinding.hpp"
#include "Grid.hpp"

// Heuristic function for A* algorithm - Manhattan distance is a good choice for grid-based pathfinding without diagonal movement
int32_t pathfinding::ManhattanDistance(Position start, Position goal) noexcept
{
    int32_t dx = start.x > goal.x ? start.x - goal.x : goal.x - start.x;
    int32_t dy = start.y > goal.y ? start.y - goal.y : goal.y - start.y;

    return dx + dy;
}

// A* pathfinding algorithm implementation
pathfinding::AStarResult pathfinding::FindPath(const Grid& grid, Position start, Position goal)
{
    // Helper struct for priority queue
    struct Node
    {
        int32_t index;
        int32_t g;  // cost from start
        int32_t f;  // total estimated cost
    };
    // H which is the heuristic cost from the current node to the goal is not stored in the Node struct
    // Because it can be easily calculated when we need to push a new node to the open set (priority queue)
    // Also, storying it would require additional, but unnecessary, memory usage for each node in the open set

    // Functor for priority queue - we want the node with the lowest f to be on top
    struct Compare
    {
        bool operator()(const Node& a, const Node& b) const
        {
            return a.f > b.f;
        }
    };

    // Grid dimensions and total number of cells
    const int32_t W = grid.Width();
    const int32_t H = grid.Height();
    const int32_t N = W * H;

    // Result struct initialization
    AStarResult result;
    result.found = false;
    result.closed.resize(N, 0);
    result.path.resize(N, 0);

    // Pathfinding data structures
    // Vector to track the state of each cell
    std::vector<pathfinding::NodeState> state(N, pathfinding::NodeState::Unseen); 
    // Vector to track the g score (cost from the start) for each cell, initialized to max int to represent infinity
    std::vector<int32_t> gScore(N, std::numeric_limits<int32_t>::max());
    // Vector to track the parent of each cell for path reconstruction, initialized to -1 to indicate no parent
    std::vector<int32_t> parent(N, -1);

    // Array of neighbour offsets for the four directions (up, down, left, right) the algorithm will consider when exploring the grid
    // For code optimization the static constexpr is used to ensure that the array is only initialized once at compile time
    constexpr int32_t NeigboursCount {4};
    static constexpr std::array<Position, NeigboursCount> neighboursOffsets {
        Position(-1, 0),
        Position(0, -1),
        Position(0, 1),
        Position(1, 0),
    };

    // Priority queue is a good choice for the open set because we need to efficiently get the node with the lowest f score
    std::priority_queue<Node, std::vector<Node>, Compare> openSet;
    
    // Check if start and goal positions are valid (within bounds and not walls)
    if (!(grid.InBounds(start.x, start.y) && grid.InBounds(goal.x, goal.y)))
    {
        result.found = false;
        return result;
    }

    if (grid.IsWall(start.x, start.y) || grid.IsWall(goal.x, goal.y))
    {
        result.found = false;
        return result;
    }

    // start and goal indices for easier access to the grid data structures
    int32_t startIndex = grid.Index(start.x, start.y);
    int32_t goalIndex = grid.Index(goal.x, goal.y);

    // Add the starting node to the open set with g score of 0 and f score equal to the heuristic (h) from start to goal
    int32_t h = pathfinding::ManhattanDistance(start, goal);
    state[startIndex] = pathfinding::NodeState::Open;
    gScore[startIndex] = 0;
    parent[startIndex] = startIndex;

    openSet.push(
        {
            startIndex,
            gScore[startIndex],
            gScore[startIndex] + h
    });

    // Main loop of the A* algorithm - continues until there are no more nodes to explore in the open set
    while (!openSet.empty())
    {
        // Get the node with the lowest f score from the open set
        Node current = openSet.top();
        openSet.pop();
        
        // If the g score of the current node isn't equal to the g score in the gScore vector,
        // It means that the node is outdated 
        // (it was added to the open set with a higher g score, but later a better path to it was found and its g score was updated)
        // Usually the best option is to update the priority of the node in the open set, 
        // but since C++'s priority queue doesn't support decrease-key operation, 
        // we can just skip the outdated node when we pop it from the open set
        if (current.g != gScore[current.index])
        {
            continue;
        }
        
        // Mark the current node as closed (fully explored) and add it to the closed list in the result
        state[current.index] = pathfinding::NodeState::Closed;
        result.closed[current.index] = 1;
        
        // If we have reached the goal, we can stop the search
        if (current.index == goalIndex)
        {
            result.found = true;
            break;
        }

        // Calculate the x and y coordinates of the current node from its index for easier neighbour exploration
        int32_t x = current.index % W;
        int32_t y = current.index / W;

        // For each of the four possible neighbours (up, down, left, right)
        for (int i = 0; i < NeigboursCount; ++i)
        {
            // Calculate the coordinates of the neighbour
            int32_t neighbourX = x + neighboursOffsets[i].x;
            int32_t neighbourY = y + neighboursOffsets[i].y;

            // Check if the neighbour is within the bounds of the grid
            if (!grid.InBounds(neighbourX, neighbourY))
            {
                continue;
            }

            int32_t neighbourIndex = grid.Index(neighbourX, neighbourY);

            // If the neighbour is a wall or is already closed, skip it
            if (grid.IsWall(neighbourX, neighbourY))
            {
                continue;
            }
            if (state[neighbourIndex] == pathfinding::NodeState::Closed)
            {
                continue;
            }

            // Calculate new g score for the neighbour (cost from start to the neighbour through the current node)
            int32_t G = gScore[current.index] + 1;
            // If the new g score is better than the previously recorded g score for the neighbour,
            // update its g score to the new one, parent to the current node, and state to open
            if (G < gScore[neighbourIndex])
            {
                gScore[neighbourIndex] = G;
                parent[neighbourIndex] = current.index;
                state[neighbourIndex] = pathfinding::NodeState::Open;
                int32_t H = pathfinding::ManhattanDistance(
                    Position(neighbourX, neighbourY),
                    goal
                );
                int32_t F = G + H;
                openSet.push({neighbourIndex, G, F});
            } 
        } // end of neighbour exploration loop
    } // end of main A* loop

    // Path reconstruction - if a path to the goal was found, 
    // We can reconstruct it by following the parent vector from the goal back to the start
    // We create a path mask to display it on the grid, 
    // But creating a proper path vector would be really similar, 
    // We would just need to push the positions to the vector instead of setting the path mask
    // And then reverse the vector at the end to get the path from start to goal instead of from goal to start
    if (result.found)
    {
        // If the parent of the goal index is -1, it means that the goal was never reached during the search
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
    } // end of path reconstruction

    return result;
} // end of FindPath function