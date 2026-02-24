#include "Grid.hpp"

bool Grid::IsWall(size_t x, size_t y) const
{
    if (InBounds(x, y))
    {
        return cells[Index(x, y)] != 0;
    }
    else
    {
        return true;
    }
}

void Grid::SetWall(size_t x, size_t y, bool wall)
{
    if (InBounds(x, y))
    {
        cells[Index(x, y)] = wall ? 1 : 0;
    }
}