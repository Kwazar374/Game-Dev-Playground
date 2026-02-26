#include <fstream>
#include <random>
#include <cassert>
#include "grid_ops.hpp"
#include "Position.hpp"

void grid_ops::FillBorders(Grid& grid)
{
    for (int32_t x = 0; x < grid.Width(); ++x)
    {
        grid.SetWall(x, 0, true);
        grid.SetWall(x, grid.Height() - 1, true);
    }

    for (int32_t y = 1; y < grid.Height() - 1; ++y)
    {
        grid.SetWall(0, y, true);
        grid.SetWall(grid.Width() - 1, y, true);
    }
}

void grid_ops::ExportToTextFile(const Grid& grid, const std::string& file_path, Position start, Position goal)
{
    std::ofstream out(file_path);
    if (!out)
    {
        return;
    }

    out << grid.Width() << " " << grid.Height() << "\n";
    for (int32_t y = 0; y < grid.Height(); ++y)
    {
        for (int32_t x = 0; x < grid.Width(); ++x)
        {
            out << (grid.IsWall(x, y) ? '#' : '.');
        }
        out << "\n";
    }
}

void grid_ops::ExportToTextFile(const Grid& grid, const std::string& file_path, Position start, Position goal, const std::string& debug_file_path, const std::vector<uint8_t>& closed, const std::vector<uint8_t>& path)
{
    assert((int32_t)closed.size() == grid.Width() * grid.Height());
    assert((int32_t)path.size() == grid.Width() * grid.Height());

    grid_ops::ExportToTextFile(grid, file_path, start, goal);
    
    std::ofstream out(debug_file_path);
    if (!out)
    {
        return;
    }

    out << grid.Width() << " " << grid.Height() << " ";
    out << start.x << " " << start.y << " " << goal.x << " " << goal.y << "\n";

    for (auto x : closed)
    {
        out << int(x) << " ";
    }
    out << "\n";

    for (auto x : path)
    {
        out << int(x) << " ";
    }
    out << "\n";
}


void grid_ops::FillRandom(Grid& grid, float density, uint32_t seed)
{
    assert(density >= 0.0f && density <= 1.0f);
    std::mt19937 rng(seed);
    std::bernoulli_distribution wall_distribution(density);

    for (int32_t y = 0; y < grid.Height(); ++y)
    {
        for (int32_t x = 0; x < grid.Width(); ++x)
        {
            grid.SetWall(x, y, wall_distribution(rng));
        }
    }
}