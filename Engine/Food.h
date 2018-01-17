#pragma once
#include "Location.h"
#include "Graphics.h"
#include "Board.h"

class Food
{
public:
    Food(const Location& loc_in);
    void Respawn(Location& loc_in,bool isSuper);
    void Draw(Board& brd_in, float time) const;
    Location GetLocation()const;
    bool IsSuper();
private:
    Location loc;
    float pulseMax = 2.5f;
    float pulseSpeed = 8.0f;
    bool super=false;
    static constexpr Color normalColor = Colors::Red;
    static constexpr Color superColor = { 153, 51, 255 };
};