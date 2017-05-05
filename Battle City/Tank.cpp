//
//  Tank.cpp
//  Battle City
//
//  Created by Yixiong Zhang on 4/3/17.
//  Copyright © 2017 Yixiong Zhang. All rights reserved.
//

#include "Tank.hpp"
#include "GameWindow.hpp"

#include <cmath>

Tank::Tank(double health, double x, double y, double direction, Color color, bool canPass, int controllerId, vector<unique_ptr<Entity>> &entities) : Entity(x, y, direction, color, canPass), health(health), controllerId(controllerId), entities(entities) {
    width = 10;
    height = 10;
}

Tank::~Tank() {}

void Tank::move(ESign sign) {
    Entity::move(sign, 1);
}

void Tank::shoot() {
    double dirRads = direction * M_PI / 180.0;
    
    double dx, dy;
    
    dx = cos(dirRads);
    dy = sin(dirRads);
    
    if(direction == 0) {
        dx = topLeft.getX() + width + dx;
        dy = topLeft.getY() + dy;
    } else if(direction == 90) {
        dx = topLeft.getX() + dx;
        dy = topLeft.getY() - dy - Projectile::HEIGHT;
    } else if(direction == 180) {
        dx = topLeft.getX() - dx - Projectile::WIDTH;
        dy = topLeft.getY() + dy;
    } else if(direction == 270) {
        dx = topLeft.getX() + dx;
        dy = topLeft.getY() + height + dy;
    }
    
    Color color = {4, 2, 3};
    
    unique_ptr<Projectile> p (new Projectile(5, dx, dy, direction, color, true));
    entities.push_back(std::move(p));
}

void Tank::rotate(ESign sign) {
    if(sign == ENEG) {
        direction -= 90;
    } else {
        direction += 90;
    }
    
    if(direction > 359) {
        direction -= 360;
    } else if(direction < 0) {
        direction += 360;
    }
}

double Tank::getHealth(){
    return health;
}

void Tank::setHealth(double h){
    if(h >= 0) {
        health = h;
    }
};

int Tank::getControllerId() {
    return controllerId;
}

void Tank::draw() {
    
    glBegin(GL_QUADS);
    if(direction == 90) {
        glColor3f(1, 1, 1);
        glVertex2i(topLeft.getX(), topLeft.getY());
        glVertex2i(topLeft.getX() + width, topLeft.getY());
        glColor3f(color.red, color.green, color.blue);
        glVertex2i(topLeft.getX() + width, topLeft.getY() + height);
        glVertex2i(topLeft.getX(), topLeft.getY() + height);
    }
    
    if(direction == 270) {
        glColor3f(color.red, color.green, color.blue);
        glVertex2i(topLeft.getX(), topLeft.getY());
        glVertex2i(topLeft.getX() + width, topLeft.getY());
        glColor3f(1, 1, 1);
        glVertex2i(topLeft.getX() + width, topLeft.getY() + height);
        glVertex2i(topLeft.getX(), topLeft.getY() + height);
    }
    
    if(direction == 0) {
        glColor3f(color.red, color.green, color.blue);
        glVertex2i(topLeft.getX(), topLeft.getY());
        glColor3f(1, 1, 1);
        glVertex2i(topLeft.getX() + width, topLeft.getY());
        glVertex2i(topLeft.getX() + width, topLeft.getY() + height);
        glColor3f(color.red, color.green, color.blue);
        glVertex2i(topLeft.getX(), topLeft.getY() + height);
    }
    
    if(direction == 180) {
        glColor3f(1, 1, 1);
        glVertex2i(topLeft.getX(), topLeft.getY());
        glColor3f(color.red, color.green, color.blue);
        glVertex2i(topLeft.getX() + width, topLeft.getY());
        glVertex2i(topLeft.getX() + width, topLeft.getY() + height);
        glColor3f(1, 1, 1);
        glVertex2i(topLeft.getX(), topLeft.getY() + height);
    }
    glEnd();
    
}


