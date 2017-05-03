//
//  Projectile.cpp
//  Battle City
//
//  Created by Yixiong Zhang on 4/3/17.
//  Copyright © 2017 Yixiong Zhang. All rights reserved.
//

#include "Projectile.hpp"
#include "GameWindow.hpp"

Projectile::Projectile(double damage, double x, double y, double direction, Color color, bool canPassAllTerrain): Entity(x, y, direction, color, canPassAllTerrain), damage(damage) {
    width = WIDTH;
    height = WIDTH;
}

Projectile::~Projectile() {}

void Projectile::move(Sign sign) {
    Entity::move(sign, 5);
}

void Projectile::setDamage(double d){
    damage = d;
}

double Projectile::getDamage() const{
    return damage;    
}


void Projectile::draw() {

    glColor3f(color.red, color.green, color.blue);
    glBegin(GL_QUADS);
    glVertex2i(topLeft.getX(), topLeft.getY());
    glVertex2i(topLeft.getX() + width, topLeft.getY());
    glVertex2i(topLeft.getX() + width, topLeft.getY() + height);
    glVertex2i(topLeft.getX(), topLeft.getY() + height);
    glEnd();
    
    
}

