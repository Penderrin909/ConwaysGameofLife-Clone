//
//  Globals.cpp
//  ConwaysGameofLife
//
//  Created by Justin Dagenhart on 7/22/13.
//  Copyright (c) 2013 Justin Dagenhart. All rights reserved.
//

#include "Render.hpp"

#include <iostream>

Render::Render()
{
    running = true;
    checkNow = true;
    lastKeyP = false;
    Surf_Display = NULL;
    speedBar = NULL;
    bg = NULL;
    aliveTile = NULL;
    Pause = NULL;
    speed = 10;
    speedRect.x = 0;
    speedRect.y = 0;
}

Render::~Render()
{
    
}

void Render::init()
{
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );
    Surf_Display = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
    
    bg = SDL_LoadBMP("images/grid.bmp"); //load background
    
    aliveTile = SDL_LoadBMP( "images/alive.bmp" ); //load live cell image
    
    Pause = SDL_LoadBMP("images/Pause.bmp"); //load pause notification
    
    speedBar = SDL_LoadBMP("images/speedBar.bmp"); //load speedbar
    
    for(int i = 0; i < (XMAX); i++) //initialize all cells to "dead"
    {
        for(int j = 0; j < (YMAX); j++)
        {
            tiles[i][j].changeState(false);
        }
    }
    
    mousePos.x = 0; mousePos.y = 0;
}

void Render::draw()
{
    //Apply image to screen
    SDL_BlitSurface(bg, NULL, Surf_Display, NULL); //background
    
    //SDL_BlitSurface(aliveTile, NULL, Surf_Display, &mousePos);
    
    for(int i = 0; i < (XMAX); i++) //draw every live cell
    {
        for(int j = 0; j < (YMAX); j++)
        {
            if(tiles[i][j].getState())
            {
                tileDraw.x = (i*SIZE);
                tileDraw.y = (j*SIZE);
                SDL_BlitSurface(aliveTile, NULL, Surf_Display, &tileDraw);
            }
        }
    }
    
    if(!checkNow) //draws pause
    {
        PausePos.x = 6;
        PausePos.y = 1;
        
        SDL_BlitSurface(Pause, NULL, Surf_Display, &PausePos);
    }
    
    /*
    speed = 1 speedRect.x = (17)*20 fastest
    speed = 2 speedRect.x = (16)*20
    speed = 3 speedRect.x = (15)*20
    speed = 4 speedRect.x = (14)*20
    speed = 5 speedRect.x = (13)*20
    speed = 6 speedRect.x = (12)*20
    speed = 7 speedRect.x = (11)*20
    speed = 8 speedRect.x = (10)*20
    speed = 9 speedRect.x = (9)*20
    speed = 10 speedRect.x = (8)*20 slowest
    */
    
    for(int i = 0; i <= 11-speed; i++)
    {
        for(int j = 1; j<= 11-speed; j++)
        {
            speedRect.x = (j+7)*20;
            SDL_BlitSurface(speedBar, NULL, Surf_Display, &speedRect);
        }
        
        
    
        //SDL_BlitSurface(speedBar, NULL, Surf_Display, &speedRect);
    }
    
    
    //Update Screen
    SDL_Flip(Surf_Display);
}

void Render::event()
{
    //SDL_PumpEvents();
    while(SDL_PollEvent(&events)) //only used for SDL_QUIT...
    {
    
    Uint8 *keyboard_state = SDL_GetKeyState(NULL);
        //check keys
    
    if (keyboard_state[SDLK_q] || keyboard_state[SDLK_ESCAPE])
        //exit the program
    {
        running = false;
    }
    
    if (keyboard_state[SDLK_p]&&(lastKeyP == false))
        //makes it so that pause can be turned on and off
    {
        checkNow = !checkNow;
        lastKeyP = true;
    }
    if(!keyboard_state[SDLK_p]) //stops from checking
    {
        lastKeyP = false;
    }
        
    if(keyboard_state[SDLK_DOWN]) //increase speed of check
    {
        if(speed < 10)
            speed++;
    }
        
    if(keyboard_state[SDLK_UP]) //decrease speed of check
    {
        if(speed > 1)
            speed--;
    }
    
    if (keyboard_state[SDLK_BACKSPACE]) //deletes the whole board
    {
        for(int i = 0; i < (XMAX); i++)
        {
            for(int j = 0; j < (YMAX); j++)
            {
               tiles[i][j].changeState(false);
            }
        }
    }

    if(SDL_GetMouseState(&x, &y)&SDL_BUTTON(1)) //creat a live cell
    {
        mousePos.x = x;
        mousePos.y = y;
        
        changeTile(((x-(x%SIZE))/SIZE), ((y-(y%SIZE))/SIZE), true/*!getTile(((x-(x%20))/20), ((y-(y%20))/20))*/);
    }
    
    if(SDL_GetMouseState(&x, &y)&SDL_BUTTON(3)) //kill a cell
    {
        mousePos.x = x;
        mousePos.y = y;
        
        changeTile(((x-(x%SIZE))/SIZE), ((y-(y%SIZE))/SIZE), false/*!getTile(((x-(x%20))/20), ((y-(y%20))/20))*/);
    }
        
    if(events.type ==  SDL_QUIT) //closes with normal exiting.
    {
        running = false;
    }
    
    SDL_Delay(10);
        
    }
}

void Render::check() //checks for cells to kill or live
{
    for(int i = 0; i < (XMAX); i++)
    {
        for(int j = 0; j < (YMAX); j++)
        {
            turnTile[i][j] = false;
        }
    }
    
    int surround = 0;
    
    for(int i = 0; i < (XMAX); i++)
    {
        for(int j = 0; j < (YMAX); j++)
        {
            for(int n = -1; n <= 1; n++)
            {
                for(int h = -1; h <= 1; h++)
                {
                    if(((i+n)>0)&&((j+h)>0)&&((i+n)<XMAX)&&((j+h)<YMAX))
                    {
                        if((n==0)&&(h==0))
                        {
                        }
                        else if(getTile((i+n),(j+h)))
                        {
                            surround++;
                        }
                    }
                }
            }
            
            if((getTile(i, j)==true) && ((surround == 2) || (surround == 3)))
            {
                turnTile[i][j] = true;
            }
            
            if((getTile(i, j)==false) && (surround == 3))
            {
                turnTile[i][j] = true;
            }
            
            surround = 0;
            
        }
    }
    
    for(int i = 0; i < (XMAX); i++)
    {
        for(int j = 0; j < (YMAX); j++)
        {
            changeTile(i, j, turnTile[i][j]);
        }
    }
}

void Render::changeTile(int numX, int numY, bool state) //changes cell state
{
    tiles[numX][numY].changeState(state);
}

bool Render::getTile(int numX, int numY) //gets cell state
{
    return tiles[numX][numY].getState();
}




 