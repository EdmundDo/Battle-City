//
//  Obstacle.cpp
//  CS120
//
//  Created by Shaw on 4/13/17.
//  Copyright © 2017 Shaw. All rights reserved.
//

#include "Obstacle.hpp"


Obstacle::Obstacle(int x, int y, int width, int height, Color color, Terrain a) : MapObject(x, y, width, height, color), underlyingTerrain(a) {}

Terrain Obstacle::getunderlyingTerrain(){
    return underlyingTerrain;
}

void Obstacle::setUnderlyingTerrain(Terrain a){
    underlyingTerrain = a;
}



DestructibleObstacle::DestructibleObstacle(int x, int y, int width, int height, Color color, Terrain a, double h) : Obstacle(x, y, width, height, color, a), health(h) {}

void DestructibleObstacle::setRemainingHealth(double health) {
    this->health = health;
}

double DestructibleObstacle::getRemainingHealth() const{
    return health;
}
