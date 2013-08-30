//
//  main.cpp
//  ConwaysGameofLife
//
//  Created by Justin Dagenhart on 7/22/13.
//  Copyright (c) 2013 Justin Dagenhart. All rights reserved.
//

#include "Render.hpp"

int main( int argc, char* args[] )
{
    Render render;
    
    render.init();
    
    int i = 0;
    
    while(render.running)
    {
        render.event();
        render.draw();
        
        if((render.checkNow)&&(i == render.speed))
        {
            render.check();
        }
        
        i++;
        if(i > render.speed) i = 0;
    }
    
    
    //Quit SDL
    SDL_Quit();
    
    return 0;
}