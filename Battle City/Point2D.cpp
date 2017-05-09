//
//  Point2D.cpp
//  Battle City
//
//  Created by Edmund Do on 4/18/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Point2D.hpp"

Point2D::Point2D() : Point2D(0, 0) {}

Point2D::Point2D(int x, int y) : x(x), y(y) {}

int Point2D::getX() const {
    return x;
}

void Point2D::setX(int x) {
    this->x = x;
}

int Point2D::getY() const {
    return y;
}

void Point2D::setY(int y) {
    this->y = y;
}

double Point2D::distance(const Point2D &p1, const Point2D &p2) {
    return 0;
}
