//
//  Tank.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Tank.hpp"

Tank::Tank(double health, double x, double y, double direction, Color color, bool canPass) : Entity(x, y, direction, color, canPass), health(health) {}


Tank::~Tank() {}

void Tank::rotate(Sign sign) {
    if(sign == ENEG) {
        direction--;
    } else {
        direction++;
    }
}

Projectile Tank::shoot() {
    
}


double Tank::getHealth(){
    return health;
}


void Tank::setHealth(double h){
    health = h;
    
}

void Tank::draw() {
    
}
