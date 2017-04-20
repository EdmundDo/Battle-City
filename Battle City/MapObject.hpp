//
//  MapObject.hpp
//  CS120
//
//  Created by Shaw on 4/13/17.
//  Copyright © 2017 Shaw. All rights reserved.
//

#ifndef MapObject_hpp
#define MapObject_hpp
#include <iostream>
using namespace std;
#include <stdio.h>
#include"Color.hpp"

class MapObject{
    
public:
    MapObject();
    
    string getName();
    
    int getCoordX();
    
    int getCoordY();
    
    void draw();
    
    
    
protected:
    
    
    string name;
    int coordX;
    int coordY;
    
    Color color;
    
};




#endif /* MapObject_hpp */
