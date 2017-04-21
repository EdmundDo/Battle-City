//
//  Obstacle.cpp
//  CS120
//
//  Created by Shaw on 4/13/17.
//  Copyright © 2017 Shaw. All rights reserved.
//

#include "Obstacle.hpp"


Obstacle::Obstacle(string name, int x, int y, int width, int height, Color color) : MapObject(name, x, y, width, height, color), underlyingTerrain(Terrain("nothing", x, y, width, height, color, true)) {}

Obstacle::Obstacle(string name, int x, int y, int width, int height, Color color, Terrain a) : MapObject(name, x, y, width, height, color), underlyingTerrain(a) {}

Terrain Obstacle::getunderlyingTerrain(){
    return underlyingTerrain;
}

void Obstacle::setUnderlyingTerrain(Terrain a){
    underlyingTerrain = a;
}

void Obstacle::draw() {
    
}



DestructibleObstacle::DestructibleObstacle(string name, int x, int y, int width, int height, Color color, Terrain a, double h) : Obstacle(name, x, y, width, height, color, a), health(h) {}

void DestructibleObstacle::setRemainingHealth(double health) {
    this->health = health;
}

double DestructibleObstacle::getRemainingHealth() const{
    return health;
}
