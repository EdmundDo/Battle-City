//
//  Obstacle.hpp
//  CS120
//
//  Created by Shaw on 4/13/17.
//  Copyright © 2017 Shaw. All rights reserved.
//

#ifndef Obstacle_hpp
#define Obstacle_hpp
#include <iostream>
#include "MapObject.hpp"

#include"Terrain.cpp"

using namespace std;

class Obstacle:public MapObject{
    
public:
     //constructor
    Obstacle(Terrain a);
    
    Terrain getunderlyingTerrain();
    
   
    void setUnderlyingTerrain(Terrain a);
    
private:
    Terrain underlyingTerrain;
    
};




class DestructibleObstacle:public Obstacle{
    
public:
    
    //constructor
    DestructibleObstacle(Terrain a, double health);
    
    double getRemainingHealth();
    
private:
    
   
    
    double health;
};



#include <stdio.h>

#endif /* Obstacle_hpp */
