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
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effect: responds to input based on key press
     */
    
    virtual void act(char c) = 0;
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effect: calls tank.shoot()
     */
    
    virtual void shoot();
    
    /**
     * Requires: nothing
     * Modifies: tank
     * Effects: calls tank's move and rotate methods in a certain direction
     */
    
    virtual void rotateLeft();
    virtual void rotateRight();
    virtual void moveForward();
    virtual void moveBackward();
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: gets the tank belonging to the instance
     */
    
    virtual void getTank();
    
protected:
    Tank tank;                  // Tank associated with this object
};

#endif /* Controller_hpp */
