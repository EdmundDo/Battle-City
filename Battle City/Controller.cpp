//
//  Controller.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Controller.hpp"

Controller::Controller (Tank &tank) : tank(tank), canMoveForward(true), canMoveBack(true), canRotateRight(true), canRotateLeft(true), recentlyMoved(false) {}

Controller::~Controller() {}

void Controller::shoot() {
    tank.shoot();
}

void Controller::rotateLeft() {
    if(canRotateLeft) {
        tank.rotate(EPOS);
    }
    
    if(!canRotateRight) {
        canRotateRight = true;
    }
    
    canMoveBack = true;
    canMoveForward = true;
    recentlyMoved = true;
}

void Controller::rotateRight() {
    if(canRotateRight) {
        tank.rotate(ENEG);
    }
    
    if(!canRotateLeft) {
        canRotateLeft = true;
    }
    
    canMoveBack = true;
    canMoveForward = true;
    recentlyMoved = true;
}

void Controller::moveForward() {
    if(canMoveForward) {
        tank.move(EPOS);
    }
    
    if(!canMoveBack) {
        canMoveBack = true;
    }
    
    recentlyMoved = true;
}

void Controller::moveBackward() {
    if(canMoveBack) {
        tank.move(ENEG);
    }
    
    if(!canMoveForward) {
        canMoveForward = true;
    }
    
    recentlyMoved = true;
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

bool Controller::getCanRotateRight() const {
    return canRotateRight;
}

void Controller::setCanRotateLeft(bool tf) {
    canRotateLeft = tf;
}

bool Controller::getCanRotateLeft() const {
    return canRotateLeft;
}

void Controller::setRecentlyMoved(bool tf) {
    recentlyMoved = tf;
}
bool Controller::getRecentlyMoved() const {
    return recentlyMoved;
}

Tank Controller::getTank() const {
    return tank;
}
