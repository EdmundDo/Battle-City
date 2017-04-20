//
//  Terrain.cpp
//  CS120
//
//  Created by Shaw on 4/14/17.
//  Copyright © 2017 Shaw. All rights reserved.
//

#include "Terrain.hpp"

Terrain::Terrain(int x, int y, Color color, bool isPassable) : MapObject(x, y, color), isPassable(isPassable) {}

bool Terrain::getIsPassable() const{
    return isPassable;
}

void Terrain::setIsPassable(bool a ){
    isPassable = a;
}
