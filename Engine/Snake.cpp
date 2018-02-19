#include "Snake.h"

Snake::Snake()
{
    segments[0].InitHead(startLoc);
}

void Snake::MoveBy(const Location & delta_loc)
{
    for (int i = nSegments; i > 0; i--)
    {
        segments[i].Follow(segments[i - 1]);
    }
    segments[0].MoveBy(delta_loc);
}

void Snake::Grow()
{
    Location tailLocation = segments[nSegments-1].GetLocation();

    if (nSegments % 8 == 2 || nSegments % 8 == 3)
    {
        segments[nSegments].InitBody(bodyColor4, tailLocation);
    }
    else if (nSegments % 8 == 4 || nSegments % 8 == 1)
    {
        segments[nSegments].InitBody(bodyColor3, tailLocation);
    }
    else if (nSegments % 8 == 5 ||nSegments % 8 == 0)
    {
        segments[nSegments].InitBody(bodyColor2, tailLocation);
    }
    else if (nSegments % 8 == 6 || nSegments % 8 == 7)
    {
        segments[nSegments].InitBody(bodyColor1, tailLocation);
    }
    nSegments++;
}

void Snake::Reset()
{
    nSegments = 1;
    segments[0].InitHead(startLoc);
}

void Snake::Draw(Board & brd_in) const
{
    for (int i = 0; i < nSegments; i++) {
        segments[i].Draw(brd_in);
    }
}

Location Snake::GetLocationOfHead()
{
    return segments[0].GetLocation();
}

bool Snake::IsPartOfSnake(Location& loc_in) const
{
    for (int i = 0; i < nSegments; i++)
    {
        if (segments[i].GetLocation() == loc_in)
        {
            return true;
        }
    }
    return false;
}

bool Snake::IsPartOfSnakeExceptTail(Location & loc_in) const
{
    for (int i = 0; i < nSegments-1; i++)
    {
        if (segments[i].GetLocation() == loc_in)
        {
            return true;
        }
    }
    return false;
}

void Snake::Segment::InitHead(const Location & loc_in)
{
    loc = loc_in;
    c = headColor;
}

void Snake::Segment::InitBody(const Color c_in, Location loc_in)
{
    c = c_in;
    loc = loc_in;
    
}

void Snake::Segment::Follow(const Segment & next)
{
    loc = next.loc;
}

void Snake::Segment::MoveBy(const Location & delta_loc)
{
    assert(abs(delta_loc.x) + abs(delta_loc.y) == 1 || abs(delta_loc.x) + abs(delta_loc.y) == 0);

    loc.Add(delta_loc);
}

void Snake::Segment::Draw(Board & brd_in) const
{
    brd_in.DrawCell(loc, c);
}

Location Snake::Segment::GetLocation() const
{
    return loc;
}
