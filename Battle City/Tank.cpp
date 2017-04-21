//
//  Tank.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Tank.hpp"

#include <cmath>
#include <vector>
using namespace std;

Tank::Tank(double health, double x, double y, double direction, Color color, bool canPass, int controllerId, vector<Entity*> &entities) : Entity(x, y, direction, color, canPass), health(health), controllerId(controllerId), entities(&entities) {
    width = 20;
    height = 40;
}


Tank::~Tank() {}

void Tank::rotate(Sign sign) {
    if(sign == ENEG) {
        direction--;
    } else {
        direction++;
    }
    
    if(direction > 359) {
        direction -= 360;
    } else if(direction < 0) {
        direction += 360;
    }
}

void Tank::shoot() {
    double dirRads = direction * M_PI / 180.0;
    
    double dx, dy;
    
    dx = cos(dirRads);
    dy = sin(dirRads);
    
    Projectile p(5, dx, dy, direction, getColor(), true);
    entities->push_back(&p);
}


double Tank::getHealth(){
    return health;
}


void Tank::setHealth(double h){
    if(h > 0) {
        health = h;
    }
}

int Tank::getControllerId() {
    return controllerId;
}

void Tank::draw() {
    
}
