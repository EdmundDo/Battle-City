//
//  Entity.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Entity.hpp"
#include <cmath>

Entity::Entity(double x, double y, double direction, Color color, bool canPass) : direction(direction), color(color), canPass(canPass) {
    topLeft.setX(x);
    topLeft.setY(y);
}

Entity::~Entity() {}

void Entity::move(Sign sign) {
    double dirRads = direction * M_PI / 180.0;
    double dx, dy;
    
    dx = cos(dirRads);
    dy = sin(dirRads);
    
    topLeft.setX(topLeft.getX() + sign * dx);
    topLeft.setY(topLeft.getY() + sign * dy);
}

double Entity::getX() const{
    return topLeft.getX();
}


double Entity::getY() const{
    return topLeft.getY();
    
}

double Entity::getHeight() const {
    return height;
}

void Entity::setHeight(double height) {
    this->height = height;
}

double Entity::getWidth() const {
    return width;
}

void Entity::setWidth(double width) {
    this->width = width;
}

double Entity::getDirection() const{
    return direction;
    
}

void Entity::setDirection(double s){
    direction = s;
    
}

Color Entity::getColor() const{
    return color;
}

void Entity::setColor(Color &color) {
    this->color = color;
}

void Entity::setColor(int r, int g, int b) {
    this->color.red = r;
    this->color.green = g;
    this->color.blue = b;
}

bool Entity::getCanPass() {
    return canPass;
}

void Entity::setCanPass(bool tf) {
    canPass = tf;
}
