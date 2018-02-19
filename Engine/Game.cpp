/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
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
#include "MainWindow.h"
#include "Game.h"
#include <chrono>

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
    brd(gfx),
    rng(std::random_device()()),
    food({ 10,10 }),
    superFoodPercentage(1, 7),
    mainTheme(L"mainTheme.wav", 0.0f,182.0f ),
    gameOverSound(L"gameOver.wav"),
    bite({ L"bite.wav" }),
    superBite({L"superBite.wav"})
{
    
     


}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
    const float dt = ft.Mark();

    if (!mainThemePlaying)
    {
        mainTheme.Play();
        mainThemePlaying = true;
    }

    if (!gameOver)
    {
        if (wnd.kbd.KeyIsPressed(VK_UP) && currentDir != Location {0, 1} )
        {
            delta_loc = { 0,-1 };
        }
        else if (wnd.kbd.KeyIsPressed(VK_DOWN) && currentDir != Location{ 0, -1 })
        {
            delta_loc = { 0,1 };
        }
        else if (wnd.kbd.KeyIsPressed(VK_LEFT) && currentDir != Location{ 1, 0 })
        {
            delta_loc = { -1,0 };
        }
        else if (wnd.kbd.KeyIsPressed(VK_RIGHT) && currentDir != Location{ -1, 0 })
        {
            delta_loc = { 1,0 };
        }

        snakeMoveCounter+= dt;
        if (snakeMoveCounter >= snakeSpeed) {

            Location next = snake.GetLocationOfHead();
            next.Add(delta_loc);

            if (next == food.GetLocation())
            {
                
                if (food.IsSuper())
                {
                    snake.Grow();
                    snake.Grow();
                    snake.Grow();
                    snake.Grow();
                    snake.Grow();

                    for (Rock& r : rocks) {
                        r.makeVulnerable(true);
                    }
                    powerUpCounter = 0.0f;

                    superBite.Play(rng);
                }
                else
                {
                    bite.Play(rng);
                    snake.Grow();
                }
                

                Location potLoc = brd.GetRandomLocation();

                while (snake.IsPartOfSnake(potLoc) || checkCollisionWithRocks(potLoc)) //get random locations until a free location.
                {
                    potLoc = brd.GetRandomLocation();
                }

                food.Respawn(potLoc, superFoodPercentage(rng) == 1);
                
                
            }

            
            //check for gameoverconditions
            if (!brd.IsInsideBoard(next)||
                snake.IsPartOfSnakeExceptTail(next)||
                checkCollisionWithRocks(next))
            {
                gameOver = true;
                mainTheme.StopAll();
                
                gameOverSound.Play();
            }
            else
            {
                snake.MoveBy(delta_loc);
                currentDir = delta_loc;
                snakeMoveCounter = 0.0f;
            }

            


        }

        rockSpawnCounter+=dt;
        if (rockSpawnCounter >= rockSpawnInterval) //spawns rocks in time intervals
        {

            Location potLoc = brd.GetRandomLocation();

            while (snake.IsPartOfSnake(potLoc) || potLoc == food.GetLocation()) //get random locations until a free location.
            {
                potLoc = brd.GetRandomLocation();
            }

            rocks[nRocks].Spawn(potLoc);
            nRocks++;
            rockSpawnCounter = 0;
        }

        
        if (snakeSpeed <= snakeMoveMinPeriod) //increase speed of snake over time
        {
            snakeSpeed = snakeMoveMinPeriod;
        }
        else
        {
            snakeSpeed = baseSnakeSpeed - 0.005f*(time/snakeSpeedIncreaseInterval);
        }
        
        //Keeps track of powerup time
        if (powerUpCounter <= powerUpDuration) {
            powerUpCounter += dt;
        }
        else if (powerUpCounter > powerUpDuration)
        {
            for (Rock& r : rocks) {
                r.makeVulnerable(false);
            }
        }
        
    }else 
    {
        if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
        {
            Reset();
        }
    }
    
    time+=dt;
}

bool Game::checkCollisionWithRocks(Location loc)
{

    for (int i=0; i < nRocks; i++)
    {
        if (loc == rocks[i].GetLocation())
        {
            if (rocks[i].IsVulnerable()) //if the rock is vulnerable eat it otherwise gameover
            {
                snake.Grow();
                bite.Play(rng);

                rocks[i].Delete();
            }
            else 
            {
                return true;
            }
            
        }
    }

    return false;
}

void Game::Reset()
{
    snake.Reset();
    gameOver = false;
    snakeSpeed = baseSnakeSpeed;
    snakeMoveCounter = 0.0f;
    powerUpCounter = 0.0f;
    delta_loc = { 1,0 };
    //Rock rocks[100];
    nRocks = 0;
    rockSpawnCounter = 0.0f;
    mainThemePlaying = false;
    gameOverSound.StopAll();
}

void Game::ComposeFrame()
{
    
    brd.DrawBorder();
    snake.Draw(brd);
    food.Draw(brd, time);

    for (int i = 0; i < nRocks; i++)
    {
        if (powerUpDuration - powerUpCounter <= 3.0f) //blink if powerup is about to expire
        {
            rocks[i].Draw(brd, true, time);
        }
        else
        {
            rocks[i].Draw(brd, false, time);
        }
        
    }

    if (gameOver)
    {
        spr.DrawGameOver(240, 250, gfx);
    }
}
