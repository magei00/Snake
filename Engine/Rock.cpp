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

void Rock::makeVulnerable(bool isVulnerable)
{
    vulnerable = isVulnerable;
}

bool Rock::IsVulnerable()
{
    return vulnerable;
}

void Rock::Delete()
{
    isActive = false;
    loc = { 0,0 };
}

void Rock::Draw(Board & brd_in, bool blink, float time ) const
{
    if (isActive)
    {
        if (vulnerable) {
            if (blink) 
            {
                unsigned char r = 204 + cos(time*5) * 50;
                unsigned char g = 102 + cos(time*5) * 100;
                Color cBlink = { r, g , 255 };
                brd_in.DrawCell(loc, cBlink);
            }
            else
            {
                brd_in.DrawCell(loc, cVuln);
            }
            
        }
        else {
            brd_in.DrawCell(loc, c);
        }
       
    }
    
}
