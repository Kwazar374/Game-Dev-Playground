#pragma once

#include "Grid.hpp"
#include <string>
#include <utility>

namespace grid_ops {
    void FillBorders(Grid& grid);
    void FillRandom(Grid& grid, float density, uint32_t seed);
    void ExportToTextFile(const Grid& grid, const std::string& file_path, std::pair<size_t, size_t> start, std::pair<size_t, size_t> goal);
}