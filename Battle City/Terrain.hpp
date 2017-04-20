//
//  Terrain.hpp
//  CS120
//
//  Created by Shaw on 4/14/17.
//  Copyright © 2017 Shaw. All rights reserved.
//

#ifndef Terrain_hpp
#define Terrain_hpp
#include "Obstacle.hpp"

class Terrain:public Obstacle{
    
public:
    
    Terrain();
    
    bool getIsPassable();
    
    void setIsPassable(bool a);
    
private:
    
    bool isPassable;
    
    
};


#include <stdio.h>

#endif /* Terrain_hpp */
