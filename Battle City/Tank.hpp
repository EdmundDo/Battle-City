//
//  Tank.hpp
//  Battle City
//
//  Created by Yixiong Zhang on 4/3/17.
//  Copyright © 2017 Yixiong Zhang. All rights reserved.
//

#ifndef Tank_hpp
#define Tank_hpp

#include "Entity.hpp"
#include "Projectile.hpp"

#include <vector>
using namespace std;

class Tank : public Entity{
public:
    Tank(double health, double x, double y, double direction, Color color, bool canPass, int controllerId, vector<unique_ptr<Entity>> &entities);
    ~Tank();
    
    /**
     * @See Entity#move(Sign)
     */
    
    virtual void move(ESign sign) override;
    
    /**
     * Requires: nothing
     * Modifies: entities
     * Effects: creates a projectile
     */
    
    void shoot();
    
    /**
     * Requires: nothing
     * Modifies: direction
     * Effects: rotates the tank
     */
    
    void rotate(ESign r);
    
    /**
     * Requires: h > 0
     * Modifies: health
     * Effects: getters and setters
     */
    
    void setHealth(double h);
    double getHealth();
    int getControllerId();
    
    virtual void draw() override;
    
private:
    int controllerId;
    vector<unique_ptr<Entity>> &entities;
    double health;
};

#endif /* Tank_hpp */
