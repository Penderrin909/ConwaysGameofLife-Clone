//
//  tile.h
//  ConwaysGameofLife
//
//  Created by Justin Dagenhart on 7/22/13.
//  Copyright (c) 2013 Justin Dagenhart. All rights reserved.
//

#ifndef __ConwaysGameofLife__tile__
#define __ConwaysGameofLife__tile__

class tile
{
public:
    tile();
    ~tile();
    
    int getxPos();
    int getyPos();
    bool getState();
    void changeState(bool changes);
    
private:
    int xPos; //must be a multiple of 20 from 0 to 620 x24
    int yPos; //must be a multiple of 20 from 0 to 480 x32
    
    bool alive; //is that tile alive currently?
};

#endif /* defined(__ConwaysGameofLife__tile__) */
