//
//  MapObject.cpp
//  CS120
//
//  Created by Shaw on 4/13/17.
//  Copyright © 2017 Shaw. All rights reserved.
//

#include "MapObject.hpp"

MapObject::MapObject(int x, int y) {
    this->topLeft.setX(x);
    this->topLeft.setY(y);
}

string MapObject::getName() const{
    return name;
}

int MapObject::getCoordX() const{
    return topLeft.getX();
}

int MapObject::getCoordY() const{
    return topLeft.getY();
}

