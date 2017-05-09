//
//  Point2D.hpp
//  Battle City
//
//  Created by Edmund Do on 4/18/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#ifndef Point2D_hpp
#define Point2D_hpp

class Point2D {
public:
    Point2D();
    Point2D(int x, int y);
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: getters and setters
     */
    
    int getX() const;
    void setX(int x);
    int getY() const;
    void setY(int y);
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: calculates the difference between the two points
     */
    
    static double distance(const Point2D &p1, const Point2D &p2);
    
private:
    double x;
    double y;
};

#endif /* Point2D_hpp */
