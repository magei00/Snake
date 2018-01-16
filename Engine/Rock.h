#pragma once
#include "Location.h"
#include "Graphics.h"
#include "Board.h"

class Rock
{
public:
    void Spawn(Location& loc_in);
    Location GetLocation() const;
    void Draw(Board& brd_in) const;
private:
    Location loc = {0,0};
    bool isActive = false;
    static constexpr Color c = { 128, 128, 128 };

};