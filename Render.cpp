//
//  Globals.cpp
//  ConwaysGameofLife
//
//  Created by Justin Dagenhart on 7/22/13.
//  Copyright (c) 2013 Justin Dagenhart. All rights reserved.
//

#include "Render.hpp"

Render::Render()
{
    running = true;
    checkNow = true;
    lastKeyP = false;
    Surf_Display = NULL;
    bg = NULL;
    aliveTile = NULL;
    Pause = NULL;
}

Render::~Render()
{
    
}

void Render::init()
{
    //Start SDL
    SDL_Init( SDL_INIT_EVERYTHING );
    Surf_Display = SDL_SetVideoMode( 640, 480, 32, SDL_SWSURFACE );
    
    bg = SDL_LoadBMP("images/grid.bmp");
    
    aliveTile = SDL_LoadBMP( "images/alive.bmp" );
    
    Pause = SDL_LoadBMP("images/Pause.bmp");
    
    for(int i = 0; i < (XMAX); i++)
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
    SDL_BlitSurface(bg, NULL, Surf_Display, NULL);
    
    //SDL_BlitSurface(aliveTile, NULL, Surf_Display, &mousePos);
    
    for(int i = 0; i < (XMAX); i++)
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
    
    if(!checkNow)
    {
        PausePos.x = 6;
        PausePos.y = 1;
        
        SDL_BlitSurface(Pause, NULL, Surf_Display, &PausePos);
    }
    
    //Update Screen
    SDL_Flip(Surf_Display);
}

void Render::event()
{
    //SDL_PumpEvents();
    while(SDL_PollEvent(&events))
    {
    
    Uint8 *keyboard_state = SDL_GetKeyState(NULL);
    
    if (keyboard_state[SDLK_q] || keyboard_state[SDLK_ESCAPE])
    {
        running = false;
    }
    
    if (keyboard_state[SDLK_p]&&(lastKeyP == false))
    {
        checkNow = !checkNow;
        lastKeyP = true;
    }
    if(!keyboard_state[SDLK_p])
    {
        lastKeyP = false;
    }
    
    if (keyboard_state[SDLK_BACKSPACE])
    {
        for(int i = 0; i < (XMAX); i++)
        {
            for(int j = 0; j < (YMAX); j++)
            {
               tiles[i][j].changeState(false);
            }
        }
    }

    if(SDL_GetMouseState(&x, &y)&SDL_BUTTON(1))
    {
        mousePos.x = x;
        mousePos.y = y;
        
        changeTile(((x-(x%SIZE))/SIZE), ((y-(y%SIZE))/SIZE), true/*!getTile(((x-(x%20))/20), ((y-(y%20))/20))*/);
    }
    
    if(SDL_GetMouseState(&x, &y)&SDL_BUTTON(3))
    {
        mousePos.x = x;
        mousePos.y = y;
        
        changeTile(((x-(x%SIZE))/SIZE), ((y-(y%SIZE))/SIZE), false/*!getTile(((x-(x%20))/20), ((y-(y%20))/20))*/);
    }
        
    if(events.type ==  SDL_QUIT)
    {
        running = false;
    }
    
    SDL_Delay(10);
        
    }
}

void Render::check()
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
            
            /*if(getTile((i-1),(j-1)))
            {
                surround++;
            }
            if(getTile((i),(j-1)))
            {
                surround++;
            }
            if(getTile((i+1),(j-1)))
            {
                surround++;
            }
            if(getTile((i-1),(j)))
            {
                surround++;
            }
            if(getTile((i+1),(j)))
            {
                surround++;
            }
            if(getTile((i-1),(j+1)))
            {
                surround++;
            }
            if(getTile((i),(j+1)))
            {
                surround++;
            }
            if(getTile((i+1),(j+1)))
            {
                surround++;
            }*/
            
            /*if(getTile(i, j) && ((surround == 1) || (surround == 0)))
            {
                turnTile[i][j] = false;
            }*/
            
            if((getTile(i, j)==true) && ((surround == 2) || (surround == 3)))
            {
                turnTile[i][j] = true;
            }
            
            if((getTile(i, j)==false) && (surround == 3))
            {
                turnTile[i][j] = true;
            }
            
            /*if(!(getTile(i, j)) && (surround >=4))
            {
                turnTile[i][j] = false;
            }

            if(!(getTile(i, j)) && (surround <=2))
            {
                turnTile[i][j] = false;
            }*/
            
            /*if((surround <= 2)||(surround >= 5))
            {
                turnTile[i][j] = false;
            }
            
            if((surround == 3)||(surround == 4))
            {
                turnTile[i][j] = true;
            }*/
            
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

void Render::changeTile(int numX, int numY, bool state)
{
    tiles[numX][numY].changeState(state);
}

bool Render::getTile(int numX, int numY)
{
    return tiles[numX][numY].getState();
}




