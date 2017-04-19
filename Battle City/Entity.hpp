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
     * Effects: moves the entity
     */
    
    virtual void move (Sign sign);
    
    /**
     * Requires: nothing
     * Modifies: directions
     * Effects: getters and setters
     */

    
    virtual double getX() const;
    virtual double getY() const;
    virtual double getDirection() const;
    virtual void setDirection(double s);
    virtual Color getColor() const;

    virtual void draw() = 0;

protected:
    
    Point2D topLeft;
    bool canPass;
    Color color;
    double direction;


};











#endif /* Entity_hpp */
