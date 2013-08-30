//
//  Globals.h
//  ConwaysGameofLife
//
//  Created by Justin Dagenhart on 7/22/13.
//  Copyright (c) 2013 Justin Dagenhart. All rights reserved.
//

#ifndef __ConwaysGameofLife__Globals__
#define __ConwaysGameofLife__Globals__

#include <SDL.h>
#include "tile.hpp"

const int XMAX = 32;//128; //32 for grid
const int YMAX = 24;//96; // 24 for grid
const int SIZE = 20; //20 for grid

class Render
{
public:
    Render();
    ~Render();
    
    void init();
    void draw();
    void event();
    void check();
    void changeTile(int numX, int numY, bool state); //num being the tile that is changed
    bool getTile(int numX, int numY); //num being the tile that is read from
    
    bool running;
    bool checkNow;
    
    bool lastKeyP;
    
    int x, y;
    
    ///*Uint16*/ int xMouse; // = SDL_MouseButtonEvent().x;
    ///*Uint16*/ int yMouse; // = SDL_MouseButtonEvent().y;
    SDL_Rect mousePos;
    SDL_Rect tileDraw;
    
private:
    SDL_Surface *Surf_Display;
    SDL_Surface *bg;
    //SDL_Surface *dead = NULL;
    SDL_Surface *aliveTile;
    SDL_Surface *Pause;
    
    SDL_Rect PausePos;
    
    SDL_Event events;
    
    tile tiles[XMAX][YMAX];
    bool turnTile[XMAX][YMAX];
    
};

#endif /* defined(__ConwaysGameofLife__Globals__) */
