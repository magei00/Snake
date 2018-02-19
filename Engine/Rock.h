#pragma once
#include "Location.h"
#include "Graphics.h"
#include "Board.h"

class Rock
{
public:
    void Spawn(Location& loc_in);
    Location GetLocation() const;
    void makeVulnerable(bool isVulnerable);
    bool IsVulnerable();
    void Delete();
    void Draw(Board& brd_in,bool blink, float time) const;
private:
    Location loc = {0,0};
    bool isActive = false;
    bool vulnerable = false;

    static constexpr Color c = { 128, 128, 128 };
    static constexpr Color cVuln = { 157, 0, 230 };

};