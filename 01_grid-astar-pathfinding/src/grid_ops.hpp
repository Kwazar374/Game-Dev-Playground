#pragma once

#include <string>
#include <utility>
#include <vector>
#include "Grid.hpp"
#include "Position.hpp"

namespace grid_ops {
    void FillBorders(Grid& grid);
    void FillRandom(Grid& grid, float density, uint32_t seed);
    void ExportToTextFile(const Grid& grid, const std::string& file_path, Position start, Position goal);
    void ExportToTextFile(const Grid& grid, const std::string& file_path, Position start, Position goal, const std::string& debug_file_path, const std::vector<uint8_t>& closed, const std::vector<uint8_t>& path);
}