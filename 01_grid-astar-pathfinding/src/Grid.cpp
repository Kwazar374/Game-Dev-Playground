#include "Grid.hpp"

// Function to check if the cell at given coordinates is a wall
bool Grid::IsWall(int32_t x, int32_t y) const
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

// Function to set the wall state of a cell at given coordinates
void Grid::SetWall(int32_t x, int32_t y, bool wall)
{
    if (InBounds(x, y))
    {
        cells[Index(x, y)] = wall ? 1 : 0;
    }
}