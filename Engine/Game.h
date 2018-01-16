/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Location.h"
#include "Board.h"
#include <random>
#include "Snake.h"
#include "SpriteCodex.h"
#include "Food.h"
#include "Rock.h"
#include "Sound.h"
#include "SoundEffect.h"

class Game
{
public:
	Game( class MainWindow& wnd );
	Game( const Game& ) = delete;
	Game& operator=( const Game& ) = delete;
	void Go();
private:
	void ComposeFrame();
	void UpdateModel();
	/********************************/
	/*  User Functions              */

    bool checkCollisionWithRocks(Location loc);

	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables              */
    std::mt19937_64 rng;
    Board brd;
    Snake snake;
    Location delta_loc = { 1,0 };
    SpriteCodex spr;
    std::uniform_int_distribution<int> superFoodPercentage;
    Food food;
    Location currentDir = { 1,0 };
    double fps = 120;
    int snakeMovePeriod = 10 * (fps / 120);
    int snakeMoveMinPeriod = snakeMovePeriod / 2;
    int snakeMoveCounter = 0;
    int gameOver = false;
    int time = 1;
    Rock rocks[100];
    int nRocks = 0;
    int rockSpawnInterval = 400* (fps/120);
    int rockSpawnCounter = 0;
    int snakeSpeedIncreaseInterval = 2400 * (fps / 120);
    Sound mainTheme;
    Sound gameOverSound;
    SoundEffect bite;
    SoundEffect superBite;

    bool mainThemePlaying = false;
    


	/********************************/
};