#include "Food.h"

Food::Food(const Location & loc_in)
{
    loc = loc_in;
}

void Food::Respawn(Location & loc_in, bool isSuper)
{
    loc = loc_in;
    super = isSuper;
}

void Food::Draw(Board & brd_in, float time) const
{
    int padding = int (cos(time*pulseSpeed)*pulseMax+pulseMax);
    if (super)
    {
        brd_in.DrawCellAdvanced(loc, superColor, padding);
    }else
    {
        brd_in.DrawCellAdvanced(loc, normalColor, padding);
    }
    

}

Location Food::GetLocation() const
{
    return loc;
}

bool Food::IsSuper()
{
    return super;
}
