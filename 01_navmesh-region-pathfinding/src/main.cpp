#include "Grid.hpp"
#include "grid_ops.hpp"
#include <iostream>
#include <utility>
#include "pathfinding.hpp"

int main()
{
    Grid grid(100, 100);
    grid_ops::FillRandom(grid, 0.15, 42);
    grid_ops::FillBorders(grid);

    std::pair<int32_t, int32_t> start {5, 5};
    std::pair<int32_t, int32_t> goal {90, 95};

    grid.SetWall(start.first, start.second, false);
    grid.SetWall(goal.first, goal.second, false);

    auto result = pathfinding::FindPath(grid, start, goal);
    
    grid_ops::ExportToTextFile(grid ,"./grid.txt", start, goal,
        "./pathfinding.txt", result.closed, result.path);

    std::cout << "DONE!" << std::endl;

    std::cout << (result.found ? "PATH FOUND\n" : "NO PATH\n");
}