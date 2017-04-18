//
//  Tank.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Tank.hpp"

#include <cmath>

Tank::Tank(double health, double x, double y, double direction, Color color, bool canPass, int controllerId) : Entity(x, y, direction, color, canPass), health(health), controllerId(controllerId) {}


Tank::~Tank() {}

void Tank::rotate(Sign sign) {
    if(sign == ENEG) {
        direction--;
    } else {
        direction++;
    }
}

Projectile Tank::shoot() {
    double dirRads = direction * M_PI / 180.0;
    
    double dx, dy;
    
    dx = cos(dirRads);
    dy = sin(dirRads);
    
    Projectile p(5, dx, dy, direction, getColor(), true);
    return p;
}


double Tank::getHealth(){
    return health;
}


void Tank::setHealth(double h){
    health = h;
}

int Tank::getControllerId() {
    return controllerId;
}

void Tank::draw() {
    
}
