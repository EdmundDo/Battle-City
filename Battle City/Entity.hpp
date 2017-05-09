//
//  Entity.hpp
//  Battle City
//
//  Created by Yixiong Zhang on 4/3/17.
//  Copyright © 2017 Yixiong Zhang. All rights reserved.
//

#ifndef Entity_hpp
#define Entity_hpp

#include "Color.hpp"
#include "Point2D.hpp"

enum ESign {ENEG = -1, EPOS = 1};

class Entity{

public:
    
    //default constructor
    Entity(int x, int y, double direction, Color color, bool canPass);
    // desstructor
    ~Entity();
    
    /**
     * Requires: nothing
     * Modifies: coordX, coordY
     * Effects: moves the entity in the direction the entity is facing
     */
    
    virtual void move (ESign sign);

    /**
     * Requires: nothing
     * Modifies: coordX, coordY
     * Effects: moves the entity in the direction the entity is facing at a specified rate
     */
    
    virtual void move (ESign sign, double rate);
    
    /**
     * Requires: r, g, b must be between 0 and 255
     * Modifies: directions
     * Effects: getters and setters
     */
    
    virtual int getX() const;
    virtual int getGridX() const;
    virtual int getY() const;
    virtual int getGridY() const;
    virtual int getHeight() const;
    virtual void setHeight(double height);
    virtual int getWidth() const;
    virtual void setWidth(double width);
    virtual double getDirection() const;
    virtual void setDirection(double s);
    virtual Color getColor() const;
    virtual void setColor(Color &color);
    virtual void setColor(int r, int g, int b);
    virtual bool getCanPassAllTerrain();
    virtual void setCanPassAllTerrain(bool tf);


    virtual void draw() = 0;

protected:
    
    bool canPassAllTerrain;
    double direction;
    int height, width;
    Point2D topLeft;
    Color color;
};


#endif /* Entity_hpp */
