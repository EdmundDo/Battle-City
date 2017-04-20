//
//  Entity.hpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include "Color.hpp"

#include "Point2D.hpp"

enum Sign {ENEG = -1, EPOS = 1};

class Entity{

public:
    
    //default constructor
    Entity(double x, double y, double direction, Color color, bool canPass);
    // desstructor
    ~Entity();
    
    /**
     * Requires: nothing
     * Modifies: coordX, coordY
     * Effects: moves the entity in the direction the entity is facing
     */
    
    virtual void move (Sign sign);
    
    /**
     * Requires: r, g, b must be between 0 and 255
     * Modifies: directions
     * Effects: getters and setters
     */
    
    virtual double getX() const;
    virtual double getY() const;
    virtual double getHeight() const;
    virtual void setHeight(double height);
    virtual double getWidth() const;
    virtual void setWidth(double width);
    virtual double getDirection() const;
    virtual void setDirection(double s);
    virtual Color getColor() const;
    virtual void setColor(Color &color);
    virtual void setColor(int r, int g, int b);

    virtual void draw() = 0;

protected:
    
    bool canPass;
    double direction,
        height, width;
    Color color;
    Point2D topLeft;


};











#endif /* Entity_hpp */
