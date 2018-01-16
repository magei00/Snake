#include "Board.h"
#include <assert.h>

Board::Board(Graphics & gfx_in)
    :
    gfx(gfx_in),
    rng(std::random_device()()),
    xDist(0,width-1),
    yDist(0,height-1)

{
}

void Board::DrawCell(const Location & loc,Color c)
{
    assert(loc.x <= width &&loc.y <= height);
    gfx.DrawRectDim(loc.x * dimension + widthDisplacement+cellPadding, 
                    loc.y * dimension + heightDisplacement+cellPadding, 
                    dimension-2*cellPadding, dimension - 2 * cellPadding, c);
}

void Board::DrawCellAdvanced(const Location & loc, Color c, int padding)
{
    assert(loc.x <= width &&loc.y <= height);
    gfx.DrawRectDim(loc.x * dimension + widthDisplacement + padding,
        loc.y * dimension + heightDisplacement + padding,
        dimension - 2 * padding, dimension - 2 * padding, c);
}

int Board::GetWidth() const
{
    return width;
}

int Board::GetHeight() const
{
    return height;
}

bool Board::IsInsideBoard(const Location & loc) const
{
    return (loc.x<width  && 
            loc.x>=0     && 
            loc.y<height &&
            loc.y>=0);
}

Location Board::GetRandomLocation()
{
    return {xDist(rng),yDist(rng)};
}

void Board::DrawBorder() const
{
    gfx.DrawRectDim(0, 0, screenWidthP - 1, screenHeightP - 1, { 33, 51, 0 });

    gfx.DrawRectDim(widthDisplacement - bWidth, heightDisplacement - bWidth, dimension*width+2* bWidth, dimension*height+2* bWidth, Colors::Gray);
    gfx.DrawRectDim(widthDisplacement, heightDisplacement, dimension*width, dimension*height, { 57, 38, 19 });

}
