//
//  tile.cpp
//  ConwaysGameofLife
//
//  Created by Justin Dagenhart on 7/22/13.
//  Copyright (c) 2013 Justin Dagenhart. All rights reserved.
//

#include "tile.hpp"

tile::tile()
{
    
}
tile::~tile()
{
    
}

int tile::getxPos()
{
    return xPos;
}

int tile::getyPos()
{
    return yPos;
}

bool tile::getState()
{
    return alive;
}

void tile::changeState(bool changes)
{
    alive = changes;
}