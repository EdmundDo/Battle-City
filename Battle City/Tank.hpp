//
//  Tank.hpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#ifndef Tank_hpp
#define Tank_hpp

#include "Entity.hpp"
#include "Projectile.hpp"

class Tank : public Entity{
    
public:

    Tank(double health, double x, double y, double direction, Color color, bool canPass, int controllerId);
    ~Tank();
    
    Projectile shoot();
    void rotate(Sign r);
    void setHealth(double h);
    double getHealth();
    
    int getControllerId();
    
    virtual void draw() override;
    
private:
    int controllerId;
    double health;
    
    
    
};



























#endif /* Tank_hpp */
