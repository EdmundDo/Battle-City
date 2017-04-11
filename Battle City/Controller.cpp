//
//  Controller.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Controller.hpp"

#include <cmath>

Controller::Controller (Tank tank) {
    this->tank = tank;
}

Controller::~Controller() {}

void Controller::shoot() {
    tank.shoot();
}

void Controller::rotateLeft() {
    tank.rotate(tank.getDirection() - 1);
}

void Controller::rotateRight() {
    tank.rotate(tank.getDirection() + 1);
}

void Controller::moveForward() {
    tank.move(1);
}

void Controller::moveBackward() {
    tank.move(-1);
}
