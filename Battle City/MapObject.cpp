//
//  MapObject.cpp
//  CS120
//
//  Created by Shaw on 4/13/17.
//  Copyright © 2017 Shaw. All rights reserved.
//

#include "MapObject.hpp"
#include "Color.hpp"

#include "Constants.hpp"

MapObject::MapObject(string name, int x, int y, int width, int height, Color color, bool isPassable) : name(name), width(width), height(height), color(color), isPassable(isPassable) {
    this->topLeft.setX(x);
    this->topLeft.setY(y);
}

string MapObject::getName() const{
    return name;
}

int MapObject::getX() const{
    return topLeft.getX();
}

int MapObject::getGridX() const {
    return topLeft.getX() / GRID_SIZE;
}

void MapObject::setX(int x){
    topLeft.setX(x);
}

int MapObject::getY() const{
    return topLeft.getY();
}

int MapObject::getGridY() const {
    return topLeft.getY() / GRID_SIZE;
}

void MapObject::setY(int y){
    topLeft.setY(y);
}

int MapObject::getWidth() const{
    return width;
}

int MapObject::getHeight() const{
    return height;
}

bool MapObject::getIsPassable() const{
    return isPassable;
}

void MapObject::setIsPassable(bool a ){
    isPassable = a;
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

void MapObject::draw(){
    glColor3ub(color.red, color.green, color.blue);
    glBegin(GL_QUADS);
    glVertex2i(topLeft.getX(), topLeft.getY());
    glVertex2i(topLeft.getX() + width, topLeft.getY());
    glVertex2i(topLeft.getX() + width, topLeft.getY() + height);
    glVertex2i(topLeft.getX(), topLeft.getY() + height);
    glEnd();
}



