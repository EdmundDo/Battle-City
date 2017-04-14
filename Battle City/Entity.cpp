//
//  Entity.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Entity.hpp"
#include <cmath>

Entity::Entity(double x, double y, double direction, Color color, bool canPass) : coordX(x), coordY(y), direction(direction), color(color), canPass(canPass) {}

void Entity::move(Sign sign) {
    double dirRads = direction * M_PI / 180.0;
    double dx, dy;
    
    dx = cos(dirRads);
    dy = sin(dirRads);
    
    
    coordX = sign * dx;
    coordY = sign * dy;
}

double Entity:: getX() const{
    return coordX;
    
}


double Entity:: getY() const{
    return coordY;
    
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

void Entity::draw(){
    
}
