//
//  MapObject.cpp
//  CS120
//
//  Created by Shaw on 4/13/17.
//  Copyright © 2017 Shaw. All rights reserved.
//

#include "MapObject.hpp"
#include "Color.hpp"

MapObject::MapObject(int x, int y, Color color) : color(color) {
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

Color MapObject::getColor() const{
    return color;
}

void MapObject::setColor(Color &color) {
    this->color = color;
}

void MapObject::setColor(int r, int g, int b) {
    this->color.red = r;
    this->color.green = g;
    this->color.blue = b;
}

