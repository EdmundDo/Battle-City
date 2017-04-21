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
    MapObject(string name, int x, int y, int width, int height, Color color);
    
    /**
     * Requires: r, g, b must be between 0 and 255
     * Modifies: color
     * Effects: getters and setters
     */
    
    virtual string getName() const;
    virtual int getCoordX() const;
    virtual int getCoordY() const;
    virtual int getWidth() const;
    virtual int getHeight() const;
    virtual Color getColor() const;
    virtual void setColor(Color &color);
    virtual void setColor(int r, int g, int b);
    
    virtual void draw() = 0;
    
protected:
    
    string name;
    Point2D topLeft;
    int width, height;
    Color color;
    
};

#endif /* MapObject_hpp */
