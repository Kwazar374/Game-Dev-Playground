#pragma once

#include <cstdint>
#include <vector>
#include <cassert>

class Grid
{
public:
    // constructor
    Grid(int32_t width, int32_t height) : 
        width{width}, height{height}, cells(width * height) 
    {
        assert(width > 0 && height > 0);
        assert(width * height <= cells.max_size());
    }

    int32_t Index(int32_t x, int32_t y) const
    {
        return static_cast<size_t>(y) * width + x;
    }

    bool InBounds(int32_t x, int32_t y) const
    {
        return x >= 0 && x < width && y >= 0 && y < height;
    }

    bool IsWall(int32_t x, int32_t y) const;
    void SetWall(int32_t x, int32_t y, bool wall);

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