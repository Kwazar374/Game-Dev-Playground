#include <iostream>
#include <utility>
#include "Grid.hpp"
#include "grid_ops.hpp"
#include "pathfinding.hpp"
#include "Position.hpp"

int main()
{
    Grid grid(100, 100);
    grid_ops::FillRandom(grid, 0.15, 42);
    grid_ops::FillBorders(grid);

    Position start {5, 5};
    Position goal {90, 80};

    grid.SetWall(start.x, start.y, false);
    grid.SetWall(goal.x, goal.y, false);

    auto result = pathfinding::FindPath(grid, start, goal);
    
    grid_ops::ExportToTextFile(grid ,"./grid.txt", start, goal,
        "./pathfinding.txt", result.closed, result.path);

    std::cout << "DONE!" << std::endl;

    std::cout << (result.found ? "PATH FOUND\n" : "NO PATH\n");
}