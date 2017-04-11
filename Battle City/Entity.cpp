//
//  Entity.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Entity.hpp"

#include <cmath>

void Entity::move(int sign) {
    double dir = tank.getDirection(), dirRads = dir * M_PI / 180.0;
    
    double lenA, lenB, lenC; // Lengths of sides of triangle
    
    lenA = cos(dirRads);
    lenB = sin(dirRads);
    lenC = sqrt(pow(lenA, 2) + pow(lenB, 2));
    
    // Scales the triangle to get one unit of movement in any positive direction
    tank.move(sign * lenA * (1/lenC), sign * lenB * (1/lenC));
}
