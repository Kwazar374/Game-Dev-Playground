#pragma once

#include <cstdint>
#include <vector>
#include <cassert>

class Grid
{
public:
    // constructor
    Grid(size_t width, size_t height) : 
        width{width}, height{height}, cells(width * height) 
    {
        assert(width > 0 && height > 0);
        assert(width * height <= cells.max_size());
    }

    size_t Index(size_t x, size_t y) const
    {
        return static_cast<size_t>(y) * width + x;
    }

    bool InBounds(size_t x, size_t y) const
    {
        // size_t can't be smaller than 0,
        // that's why there's no need to check if x and y >= 0
        return x < width && y < height;
    }

    bool IsWall(size_t x, size_t y) const;
    void SetWall(size_t x, size_t y, bool wall);

    size_t Width() const
    {
        return width;
    }

    size_t Height() const
    {
        return height;
    }

private:
    size_t width;
    size_t height;
    // I decided to use vector<uint8_t> instead of vector<bool>
    // because vector<bool> is a specialized bitset-like container
    // and it may unnecessarily complicate the code
    std::vector<uint8_t> cells;
};