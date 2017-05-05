//
//  MapObject.cpp
//  CS120
//
//  Created by Shaw on 4/13/17.
//  Copyright © 2017 Shaw. All rights reserved.
//

#include "MapObject.hpp"
#include "Color.hpp"

MapObject::MapObject(string name, int x, int y, int width, int height, Color color) : name(name), width(width), height(height), color(color) {
    this->topLeft.setX(x);
    this->topLeft.setY(y);
}

void MapObject::draw(){
    glColor3ub(color.red, color.green, color.blue);
    glBegin(GL_QUADS);
    glVertex2i(topLeft.getX() * 10 + 1, topLeft.getY() * 10 - 1);
    glVertex2i(topLeft.getX() * 10 + width + 1, topLeft.getY() * 10 - 1);
    glVertex2i(topLeft.getX() * 10 + width + 1, topLeft.getY() * 10 + height + 1);
    glVertex2i(topLeft.getX() * 10 + 1, topLeft.getY() * 10 + height + 1);
    glEnd();
}

string MapObject::getName() const{
    return name;
}

int MapObject::getX() const{
    return topLeft.getX() * 10;
}

void MapObject::setX(int x){
    topLeft.setX(x);
}

int MapObject::getY() const{
    return topLeft.getY() * 10;
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



