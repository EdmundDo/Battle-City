//
//  PlayerController.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "PlayerController.hpp"

PlayerController::PlayerController(Tank &tank, TankKeyBindings bindings) : Controller(tank), rotateLeftKey(bindings.rlk), rotateRightKey(bindings.rrk), moveForwardKey(bindings.mfk), moveBackwardKey(bindings.mbk), shootKey(bindings.sk) {}

PlayerController::~PlayerController() {}

void PlayerController::act(char c) {
    if(c == rotateLeftKey) {
        rotateLeft();
    } else if(c == rotateRightKey) {
        rotateRight();
    } else if(c == moveForwardKey) {
        moveForward();
    } else if(c == moveBackwardKey) {
        moveBackward();
    } else if(c == shootKey) {
        shoot();
    }
}
