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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
    brd(gfx),
    rng(std::random_device()()),
    snake({5,5}),
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

        snakeMoveCounter++;
        if (snakeMoveCounter >= snakeMovePeriod) {

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
                snakeMoveCounter = 0;
            }

            


        }

        rockSpawnCounter++;
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

        if (time % snakeSpeedIncreaseInterval == 0) // increases snake speed over time
        {
            if (snakeMovePeriod <= snakeMoveMinPeriod)
            {
                snakeMovePeriod = snakeMoveMinPeriod;
            }
            else
            {
                snakeMovePeriod--;
            }
            
        }
    }
    
    time++;
}

bool Game::checkCollisionWithRocks(Location loc)
{

    for (int i=0; i < nRocks; i++)
    {
        if (loc == rocks[i].GetLocation())
        {
            return true;
        }
    }

    return false;
}

void Game::ComposeFrame()
{
    /*std::uniform_int_distribution<int> colorDist(0, 255);
    for (int i = 0; i < brd.GetWidth(); i++)
    {
        for (int j = 0; j < brd.GetHeight(); j++)
        {
            Location loc = { i,j };
            Color c(colorDist(rng), colorDist(rng), colorDist(rng));
            brd.DrawCell(loc, c);
        }
    }*/
    brd.DrawBorder();
    snake.Draw(brd);
    food.Draw(brd, time/10);

    for (int i = 0; i < nRocks; i++)
    {
        rocks[i].Draw(brd);
    }

    if (gameOver)
    {
        spr.DrawGameOver(350, 250, gfx);
    }
}
