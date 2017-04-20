//
//  MapObject.hpp
//  CS120
//
//  Created by Shaw on 4/13/17.
//  Copyright © 2017 Shaw. All rights reserved.
//

#ifndef MapObject_hpp
#define MapObject_hpp

#include "Color.hpp"
#include "Point2D.hpp"

#include <string>
using namespace std;

class MapObject{
    
public:
    MapObject(int x, int y);
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: getters
     */
    
    virtual string getName() const;
    virtual int getCoordX() const;
    virtual int getCoordY() const;
    
    virtual void draw() = 0;
    
protected:
    
    string name;
    Point2D topLeft;
    Color color;
    
};

#endif /* MapObject_hpp */
