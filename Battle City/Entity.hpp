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
    
    virtual double getX() const;
    virtual double getY() const;
    virtual void setDirection(double s);
    virtual double getDirection() const;
    virtual Color getColor() const;

    virtual void draw() = 0;

protected:
    
    bool canPass;
    Color color;
    double coordX;
    double coordY;
    double direction;


};











#endif /* Entity_hpp */
