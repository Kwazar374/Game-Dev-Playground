#include "Grid.hpp"
#include "grid_ops.hpp"
#include <iostream>
#include <utility>

int main()
{
    Grid grid(100, 100);
    grid_ops::FillRandom(grid, 0.15, 42);
    grid_ops::FillBorders(grid);

    std::pair<size_t, size_t> start {5, 5};
    std::pair<size_t, size_t> goal {90, 80};

    grid.SetWall(start.first, start.second, false);
    grid.SetWall(goal.first, goal.second, false);
    
    grid_ops::ExportToTextFile(grid ,"./grid.txt", start, goal);

    std::cout << "DONE!" << std::endl;
}