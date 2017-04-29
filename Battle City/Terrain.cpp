//
//  Terrain.cpp
//  CS120
//
//  Created by Shaw on 4/14/17.
//  Copyright © 2017 Shaw. All rights reserved.
//

#include "Terrain.hpp"

Terrain::Terrain(string name, int x, int y, int width, int height, Color color, bool isPassable) : MapObject(name, x, y, width, height, color), isPassable(isPassable) {}

bool Terrain::getIsPassable() const{
    return isPassable;
}

void Terrain::setIsPassable(bool a ){
    isPassable = a;
}

