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

struct TankKeyBindings {
    char rlk, rrk, mfk, mbk, sk;
};

class PlayerController : public Controller {
public:
    PlayerController(Tank &tank, TankKeyBindings bindings);
    ~PlayerController();
    
    virtual void update();
    
    /**
     * Requires: nothing
     * Modifies: forwardFlag and backwardFlag
     * Effects: holds down movment for better animation
     */
    
    virtual void setForwardFlag(bool tf);
    virtual bool getForwardFlag() const;
    virtual void setBackwardFlag(bool tf);
    virtual bool getBackwardFlag() const;
    
    /**
     * see Controller#act(char c)
     */
    
    virtual void act(char c) override;
    
private:
    // Binded keys
    char rotateLeftKey, rotateRightKey, moveForwardKey, moveBackwardKey, shootKey;
    bool forwardFlag, backwardFlag;
};

#endif /* PlayerController_hpp */
