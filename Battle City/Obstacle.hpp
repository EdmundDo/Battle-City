//
//  Obstacle.hpp
//  CS120
//
//  Created by Shaw on 4/13/17.
//  Copyright © 2017 Shaw. All rights reserved.
//

#ifndef Obstacle_hpp
#define Obstacle_hpp

#include "MapObject.hpp"
#include "Terrain.hpp"

class Obstacle : public MapObject{

public:
     //constructor
    
    Obstacle(string name, int x, int y, int width, int height, Color color);
    Obstacle(string name, int x, int y, int width, int height, Color color, Terrain a);
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: getters and setters
     */
    
    Terrain getunderlyingTerrain();
    void setUnderlyingTerrain(Terrain a);
    
    virtual void draw() override;
    
private:
    Terrain underlyingTerrain;
};



class DestructibleObstacle : public Obstacle{
    
public:
    
    //constructor
    DestructibleObstacle(string name, int x, int y, int width, int height, Color color, Terrain a, double health);
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: getters and setters
     */
    
    void setRemainingHealth(double health);
    double getRemainingHealth() const;
    
private:
    double health;
};

#endif /* Obstacle_hpp */
