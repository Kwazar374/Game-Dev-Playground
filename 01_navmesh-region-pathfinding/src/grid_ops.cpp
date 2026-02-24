#include "grid_ops.hpp"
#include <fstream>
#include <random>
#include <cassert>

void grid_ops::FillBorders(Grid& grid)
{
    for (size_t x = 0; x < grid.Width(); ++x)
    {
        grid.SetWall(x, 0, true);
        grid.SetWall(x, grid.Height() - 1, true);
    }

    for (size_t y = 1; y < grid.Height() - 1; ++y)
    {
        grid.SetWall(0, y, true);
        grid.SetWall(grid.Width() - 1, y, true);
    }
}

void grid_ops::ExportToTextFile(const Grid& grid, const std::string& file_path, std::pair<size_t, size_t> start, std::pair<size_t, size_t> goal)
{
    std::ofstream out(file_path);
    if (!out)
    {
        return;
    }

    out << grid.Width() << " " << grid.Height() << " ";
    out << start.first << " " << start.second << " " << goal.first << " " << goal.second << "\n";
    for (size_t y = 0; y < grid.Height(); ++y)
    {
        for (size_t x = 0; x < grid.Width(); ++x)
        {
            out << (grid.IsWall(x, y) ? '#' : '.');
        }
        out << "\n";
    }
}

void grid_ops::FillRandom(Grid& grid, float density, uint32_t seed)
{
    assert(density >= 0.0f && density <= 1.0f);
    std::mt19937 rng(seed);
    std::bernoulli_distribution wall_distribution(density);

    for (size_t y = 0; y < grid.Height(); ++y)
    {
        for (size_t x = 0; x < grid.Width(); ++x)
        {
            grid.SetWall(x, y, wall_distribution(rng));
        }
    }
}