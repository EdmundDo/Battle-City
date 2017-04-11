//
//  PlayerController.hpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#ifndef PlayerController_hpp
#define PlayerController_hpp

#include "Tank.hpp"
#include "Controller.hpp"

#include <iostream>

struct TankBindings {
    char rlk, rrk, mfk, mbk, sk;
};

class PlayerController : public Controller {
public:
    PlayerController(Tank tank, TankBindings bindings);
    ~PlayerController();
    
    virtual void act(char c = '\0') override;
private:
    char rotateLeftKey, rotateRightKey, moveForwardKey, moveBackwardKey, shootKey;
};

#endif /* PlayerController_hpp */
