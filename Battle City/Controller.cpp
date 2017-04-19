//
//  Controller.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Controller.hpp"

Controller::Controller (Tank tank) : tank(tank) {}

Controller::~Controller() {}

Projectile Controller::shoot() {
    tank.shoot();
}

void Controller::rotateLeft() {
    if(canRotateLeft) {
        tank.rotate(EPOS);
    }
    
    if(!canRotateRight) {
        canRotateRight = true;
    }
}

void Controller::rotateRight() {
    if(canRotateRight) {
        tank.rotate(ENEG);
    }
    
    if(!canRotateLeft) {
        canRotateLeft = true;
    }
}

void Controller::moveForward() {
    if(canMoveForward) {
        tank.move(EPOS);
    }
    
    if(!canMoveBack) {
        canMoveBack = true;
    }
}

void Controller::moveBackward() {
    if(canMoveBack) {
        tank.move(ENEG);
    }
    
    if(!canMoveForward) {
        canMoveForward = true;
    }
}

void Controller::setCanMoveForward(bool tf) {
    canMoveForward = tf;
}

bool Controller::getCanMoveForward() const {
    return canMoveForward;
}

void Controller::setCanMoveBack(bool tf) {
    canMoveBack = tf;
}

bool Controller::getCanMoveBack() const {
    return canMoveBack;
}

void Controller::setCanRotateRight(bool tf) {
    canRotateRight = tf;
}

bool Controller::getCanRotateright() const {
    return canRotateRight;
}

void Controller::setCanRotateLeft(bool tf) {
    canRotateLeft = tf;
}

bool Controller::getCanMRotateLeft() const {
    return canRotateLeft;
}

Tank Controller::getTank() const {
    return tank;
}
