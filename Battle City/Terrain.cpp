//
//  Terrain.cpp
//  CS120
//
//  Created by Shaw on 4/14/17.
//  Copyright © 2017 Shaw. All rights reserved.
//

#include "Terrain.hpp"

Terrain::Terrain(){
    
}

bool Terrain::getIsPassable(){
    
    return isPassable;
}

void Terrain::setIsPassable(bool a ){
    
    isPassable = a;
    
}
