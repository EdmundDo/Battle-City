//
//  Obstacle.cpp
//  CS120
//
//  Created by Shaw on 4/13/17.
//  Copyright © 2017 Shaw. All rights reserved.
//

#include "Obstacle.hpp"


Obstacle::Obstacle(Terrain a):underlyingTerrain(a){
    
}


 Terrain Obstacle::getunderlyingTerrain(){
     
     return underlyingTerrain;
     
}



void Obstacle::setUnderlyingTerrain(Terrain a){
    
    underlyingTerrain = a;
    
}

DestructibleObstacle::DestructibleObstacle(Terrain a, double h):Obstacle(a),health(h){
    
}


double DestructibleObstacle::getRemainingHealth(){
    return health;
}
