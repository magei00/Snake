#pragma once
#include "Location.h"
#include "Graphics.h"
#include <random>

class Board
{
public:
    Board(Graphics& gfx_in);
    void DrawCell(const Location& loc, Color c);
    void DrawCellAdvanced(const Location& loc, Color c, int padding);
    int GetWidth() const;
    int GetHeight() const;
    bool IsInsideBoard(const Location& loc) const;
    Location GetRandomLocation();
    void DrawBorder() const;

private:
    static constexpr int dimension = 17;
    static constexpr int width = 40;
    static constexpr int height = 30;
    static constexpr int screenWidthP = 800;
    static constexpr int screenHeightP = 600;
    static constexpr int widthDisplacement = (screenWidthP-(width*dimension))/2;
    static constexpr int heightDisplacement = (screenHeightP - (height*dimension)) / 2;
    static constexpr int bWidth = 8;
    static constexpr int cellPadding = 1;
    Graphics& gfx;
    std::mt19937 rng;
    std::uniform_int_distribution<int> xDist;
    std::uniform_int_distribution<int> yDist;
    

};