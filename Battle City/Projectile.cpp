//
//  Projectile.cpp
//  Battle City
//
//  Created by Yixiong Zhang on 4/3/17.
//  Copyright © 2017 Yixiong Zhang. All rights reserved.
//

#include "Projectile.hpp"


Projectile::Projectile(double damage, double x, double y, double direction, Color color, bool canPassAllTerrain): Entity(x, y, direction, color, canPassAllTerrain), damage(damage) {
    width = 10;
    height = 10;
}

Projectile::~Projectile() {}

void Projectile::setDamage(double d){
    damage = d;
}

double Projectile::getDamage() const{
    return damage;    
}

void Projectile::draw() {
    
}

