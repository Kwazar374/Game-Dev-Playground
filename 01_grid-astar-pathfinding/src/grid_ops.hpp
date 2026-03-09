#pragma once

#include <string>
#include <utility>
#include <vector>
#include "Grid.hpp"
#include "Position.hpp"

// The grid_ops namespace contains utility functions for operating on the grid
namespace grid_ops {
    // Function to fill the borders of the grid with walls
    void FillBorders(Grid& grid);

    // Function to fill the grid with random walls based on a given density and seed for reproducibility
    void FillRandom(Grid& grid, float density, uint32_t seed);

    // Function to export the grid to a text file, where walls are represented by '#' and open spaces by '.'
    void ExportToTextFile(const Grid& grid, const std::string& file_path, Position start, Position goal);

    // Overloaded function to export the grid and additional debug information about the pathfinding process (closed nodes and the final path) to a text file
    void ExportToTextFile(const Grid& grid, const std::string& file_path, Position start, Position goal, const std::string& debug_file_path, const std::vector<uint8_t>& closed, const std::vector<uint8_t>& path);
}