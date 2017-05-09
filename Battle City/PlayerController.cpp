//
//  PlayerController.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "PlayerController.hpp"

PlayerController::PlayerController(Tank &tank, TankKeyBindings bindings) : Controller(tank), rotateLeftKey(bindings.rlk), rotateRightKey(bindings.rrk), moveForwardKey(bindings.mfk), moveBackwardKey(bindings.mbk), shootKey(bindings.sk), forwardFlag(false), backwardFlag(false) {}

PlayerController::~PlayerController() {}

void PlayerController::update() {
    if(forwardFlag) {
        moveForward();
    } else if(backwardFlag) {
        moveBackward();
    }
}

void PlayerController::act(char c) {
    if(c == rotateLeftKey) {
        rotateLeft();
    } else if(c == rotateRightKey) {
        rotateRight();
    } else if(c == moveForwardKey) {
        if(!forwardFlag) {
            forwardFlag = true;
            backwardFlag = false;
        } else {
            forwardFlag = false;
        }
    } else if(c == moveBackwardKey) {
        if(!backwardFlag) {
            backwardFlag = true;
            forwardFlag = false;
        } else {
            backwardFlag = false;
        }
    } else if(c == shootKey) {
        shoot();
   
    }
}

void PlayerController::setForwardFlag(bool tf) {
    forwardFlag = tf;
}

bool PlayerController::getForwardFlag() const {
    return forwardFlag;
}

void PlayerController::setBackwardFlag(bool tf) {
    backwardFlag = tf;
}

bool PlayerController::getBackwardFlag() const {
    return backwardFlag;
}
