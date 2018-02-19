#pragma once
#include "Location.h"
#include "Board.h"
#include <assert.h>

class Snake
{
private:
    class Segment
    {
    public:
        void InitHead(const Location& loc_in);
        void InitBody(const Color c_in, Location loc_in);
        void Follow(const Segment& next);
        void MoveBy(const Location& delta_loc);
        void Draw(Board& brd_in) const;
        Location GetLocation() const;
    private:
        Location loc;
        Color c;

    };

public:
    Snake();
    void MoveBy(const Location& delta_loc);
    void Grow();
    void Reset();
    void Draw(Board& brd_in) const;
    Location GetLocationOfHead();
    bool IsPartOfSnake(Location& loc_in) const;
    bool IsPartOfSnakeExceptTail(Location& loc_in) const;

private:
    static constexpr int maxSnakeSize=100;
    Location startLoc = { 17,15 };
    Segment segments[maxSnakeSize];
    static constexpr Color headColor = Colors::Yellow;
    static constexpr Color bodyColor1 = { 0,150,0 };
    static constexpr Color bodyColor2 = { 0,170,0 };
    static constexpr Color bodyColor3 = { 0,200,0 };
    static constexpr Color bodyColor4 = { 0,220,0 };
    int nSegments = 1;
};