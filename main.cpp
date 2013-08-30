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
        
        if((render.checkNow)&&(i == 10))
        {
            render.check();
        }
        
        i++;
        if(i == 11) i = 0;
    }
    
    
    //Quit SDL
    SDL_Quit();
    
    return 0;
}