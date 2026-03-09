#pragma once

#include <cstdint>
#include <vector>
#include <cassert>

// The Grid class represents a 2D grid for pathfinding, where each cell can be either a wall or an open space
class Grid
{
public:
    // Constructor
    Grid(int32_t width, int32_t height) : 
        width{width}, height{height}, cells(width * height) 
    {
        assert(width > 0 && height > 0);
        assert(width * height <= cells.max_size());
    }

    // Function to convert 2D coordinates to a 1D index for the cells vector
    int32_t Index(int32_t x, int32_t y) const
    {
        assert(InBounds(x, y));
        return y * width + x;
    }

    // Function to check if the given coordinates are within the bounds of the grid
    bool InBounds(int32_t x, int32_t y) const
    {
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    // Functions to get and set the wall state of a cell at given coordinates
    bool IsWall(int32_t x, int32_t y) const;
    void SetWall(int32_t x, int32_t y, bool wall);

    // Getters for Width and Height of the grid
    int32_t Width() const
    {
        return width;
    }

    int32_t Height() const
    {
        return height;
    }

private:
    int32_t width;
    int32_t height;
    // I decided to use vector<uint8_t> instead of vector<bool>
    // because vector<bool> is a specialized bitset-like container
    // and it may unnecessarily complicate the code
    std::vector<uint8_t> cells;
};