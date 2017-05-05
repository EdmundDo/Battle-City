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
    glColor3ub(color.red, color.green, color.blue);
    glBegin(GL_QUADS);
    glVertex2i(topLeft.getX() * 10 + 1, topLeft.getY() * 10 - 1);
    glVertex2i(topLeft.getX() * 10 + width + 1, topLeft.getY() * 10 - 1);
    glVertex2i(topLeft.getX() * 10 + width + 1, topLeft.getY() * 10 + height + 1);
    glVertex2i(topLeft.getX() * 10 + 1, topLeft.getY() * 10 + height + 1);
    glEnd();
    
    glColor3ub(0, 0, 0);
    glBegin(GL_LINES);
    glVertex2d(topLeft.getX() * 10, topLeft.getY() * 10);
    glVertex2d(topLeft.getX() * 10 + width, topLeft.getY() * 10);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2d(topLeft.getX() * 10 + width, topLeft.getY() * 10);
    glVertex2d(topLeft.getX() * 10 + width, topLeft.getY() * 10 + height);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2d(topLeft.getX() * 10, topLeft.getY() * 10);
    glVertex2d(topLeft.getX() * 10, topLeft.getY() * 10 + height);
    glEnd();
    
    glBegin(GL_LINES);
    glVertex2d(topLeft.getX() * 10 , topLeft.getY() * 10 + height);
    glVertex2d(topLeft.getX() * 10 + width, topLeft.getY() * 10 + height);
    glEnd();
}

DestructibleObstacle::DestructibleObstacle(string name, int x, int y, int width, int height, Color color, Terrain a, double h) : Obstacle(name, x, y, width, height, color, a), health(h) {}

void DestructibleObstacle::setRemainingHealth(double health) {
    this->health = health;
}

double DestructibleObstacle::getRemainingHealth() const{
    return health;
}
