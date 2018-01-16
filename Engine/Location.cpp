#include "Location.h"

void Location::Add(const Location& loc_in)
{
    x += loc_in.x;
    y += loc_in.y;
}

bool Location::operator==(Location & rhs)
{
    return x==rhs.x && y==rhs.y;
}

bool Location::operator!=(Location & rhs)
{
    return (x!=rhs.x || y!=rhs.y);
}

Location Location::operator*(int rhs)
{
    return {x*rhs,y*rhs};
}
