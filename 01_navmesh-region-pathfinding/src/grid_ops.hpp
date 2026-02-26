#pragma once

#include "Grid.hpp"
#include <string>
#include <utility>
#include <vector>

namespace grid_ops {
    void FillBorders(Grid& grid);
    void FillRandom(Grid& grid, float density, uint32_t seed);
    void ExportToTextFile(const Grid& grid, const std::string& file_path, std::pair<int32_t, int32_t> start, std::pair<int32_t, int32_t> goal);
    void ExportToTextFile(const Grid& grid, const std::string& file_path, std::pair<int32_t, int32_t> start, std::pair<int32_t, int32_t> goal, const std::string& debug_file_path, const std::vector<uint8_t>& closed, const std::vector<uint8_t>& path);
}