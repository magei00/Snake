#pragma once

struct Location
{
    void Add(const Location& loc_in);
    bool operator==(Location& rhs);
    bool operator!=(Location& rhs);
    Location operator*(int rhs);

    int x;
    int y;
};