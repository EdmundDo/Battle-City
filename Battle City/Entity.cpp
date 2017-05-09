//
//  Entity.cpp
//  Battle City
//
//  Created by Yixiong Zhang on 4/3/17.
//  Copyright © 2017 Yixiong Zhang. All rights reserved.
//

#include "Entity.hpp"
#include "Constants.hpp"

#include <cmath>

Entity::Entity(int x, int y, double direction, Color color, bool canPassAllTerrain) : direction(direction), color(color), canPassAllTerrain(canPassAllTerrain) {
    topLeft.setX(x);
    topLeft.setY(y);
}

Entity::~Entity() {}

void Entity::move(ESign sign) {
    move(sign, 1);
}

void Entity::move(ESign sign, double rate) {
    double dirRads = direction * M_PI / 180.0;
    double dx, dy;
    
    dx = cos(dirRads);
    dy = -sin(dirRads);
    
    topLeft.setX(topLeft.getX() + sign * dx * rate);
    topLeft.setY(topLeft.getY() + sign * dy * rate);
}

int Entity::getX() const{
    return topLeft.getX();
}

int Entity::getGridX() const {
    return topLeft.getX() / GRID_SIZE;
}

int Entity::getY() const{
    return topLeft.getY();
}

int Entity::getGridY() const {
    return topLeft.getY() / GRID_SIZE;
}

int Entity::getHeight() const {
    return height;
}

void Entity::setHeight(double height) {
    this->height = height;
}

int Entity::getWidth() const {
    return width;
}

void Entity::setWidth(double width) {
    this->width = width;
}

double Entity::getDirection() const{
    return direction;
}

void Entity::setDirection(double s){
    direction = s;
}

Color Entity::getColor() const{
    return color;
}

void Entity::setColor(Color &color) {
    this->color = color;
}

void Entity::setColor(int r, int g, int b) {
    this->color.red = r;
    this->color.green = g;
    this->color.blue = b;
}

bool Entity::getCanPassAllTerrain() {
    return canPassAllTerrain;
}

void Entity::setCanPassAllTerrain(bool tf) {
    canPassAllTerrain = tf;
}
