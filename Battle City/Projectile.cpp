//
//  Projectile.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Projectile.hpp"


Projectile::Projectile(double damage, double x, double y, double direction, Color color, bool canPass): Entity(x, y, direction, color, canPass), damage(damage) {
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

