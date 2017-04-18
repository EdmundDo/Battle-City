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
    tank.rotate(ENEG);
}

void Controller::rotateRight() {
    tank.rotate(EPOS);
}

void Controller::moveForward() {
    tank.move(EPOS);
}

void Controller::moveBackward() {
    tank.move(ENEG);
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

Tank Controller::getTank() const {
    return tank;
}
