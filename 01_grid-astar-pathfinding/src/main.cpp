#include <iostream>
#include <filesystem>
#include <utility>
#include "Grid.hpp"
#include "grid_ops.hpp"
#include "pathfinding.hpp"
#include "Position.hpp"

// Main function to demonstrate the A* pathfinding algorithm on a grid
// It's just a demonstration, so the grid is generated randomly and the start and goal positions are predefined
// The goal is to keep it simple and focused on the A* algorithm itself, rather than on input validation and error handling
// However in a real game / application every error and exception should be properly handled
int main()
{
    // Seed for random number generation to ensure reproducibility of the grid
    const int32_t seed = 42;

    // We create a grid of size 100x100, because it's a maximum size that can be easily visualized, 
    // But the algorithm can handle much larger grids as well
    Grid grid(100, 100);

    // We fill the grid with random walls, with a density of 15% and a fixed seed for reproducibility
    // 15% is a good compromise between having enough open space for the pathfinding to work and having enough walls to make it interesting
    grid_ops::FillRandom(grid, 0.15f, seed);
    grid_ops::FillBorders(grid);

    // Define start and goal positions for the pathfinding algorithm
    Position start {5, 5};
    Position goal {90, 80};

    // Ensure that the start and goal positions are not walls
    grid.SetWall(start.x, start.y, false);
    grid.SetWall(goal.x, goal.y, false);

    // Run the A* pathfinding algorithm and get the result
    auto result = pathfinding::FindPath(grid, start, goal);
    
    // Create the output directory if it doesn't exist
    std::filesystem::create_directories("../out");

    // Export the grid, start and goal positions, and the results of the pathfinding algorithm to text files for visualization
    grid_ops::ExportToTextFile(grid ,"../out/grid.txt", start, goal,
        "../out/pathfinding.txt", result.closed, result.path);

    // Print the result of the pathfinding algorithm to the console
    std::cout << (result.found ? "PATH FOUND\n" : "NO PATH\n");
}