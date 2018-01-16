#include "Rock.h"



void Rock::Spawn(Location& loc_in)
{
    loc = loc_in;
    isActive = true;
}

Location Rock::GetLocation() const
{
    return loc;
}

void Rock::Draw(Board & brd_in) const
{
    if (isActive)
    {
        brd_in.DrawCell(loc, c);
    }
    
}
