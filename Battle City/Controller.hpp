//
//  Controller.hpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#ifndef Controller_hpp
#define Controller_hpp

#include "Tank.hpp"

#include <iostream>

class Controller {
public:
    Controller(Tank tank);
    virtual ~Controller();
    
    virtual void act(char c) = 0;
    
    virtual void shoot();
    virtual void rotateLeft();
    virtual void rotateRight();
    virtual void moveForward();
    virtual void moveBackward();
    
private:
    Tank tank;
};

#endif /* Controller_hpp */
