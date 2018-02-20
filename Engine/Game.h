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
#include "FrameTimer.h"

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
    void Reset();

	/********************************/
private:
	MainWindow& wnd;
	Graphics gfx;
	/********************************/
	/*  User Variables    */
    FrameTimer ft;
    std::mt19937_64 rng;
    Board brd;
    Snake snake;
    Location delta_loc = { 1,0 };
    SpriteCodex spr;
    std::uniform_int_distribution<int> superFoodPercentage;
    Food food;
    Location currentDir = { 1,0 };
    float baseSnakeSpeed = 0.1f;
    float snakeSpeed = baseSnakeSpeed;
    float snakeMoveMinPeriod = baseSnakeSpeed / 2.0f;
    float snakeMoveCounter = 0.0f;
    float powerUpCounter = 0.0f;
    float powerUpDuration = 10.0f;
    int gameOver = false;
    float time = 0.0001;
    Rock rocks[200];
    int nRocks = 0;
    float rockSpawnInterval = 2.5f;
    float rockSpawnCounter = 0.0f;
    float snakeSpeedIncreaseInterval = 15.0f;
    Sound mainTheme;
    Sound gameOverSound;
    SoundEffect bite;
    SoundEffect superBite;

    bool mainThemePlaying = false;
    


	/********************************/
};