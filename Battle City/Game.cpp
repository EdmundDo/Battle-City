//
//  Game.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Game.hpp"
#include "Point2D.hpp"

#include <random>

Game::Game(Map &map) : map(map) {}

Game::~Game() {}

bool Game::checkGameStatus() {
    for(int i = 0; i < controllers.size(); i++) {
        if(controllers[i].get()->getTank().getHealth() == 0) {
            controllers.erase(controllers.begin() + i);
        }
    }

    if (controllers.size() == 0) {
        // draw change to game over screen
        isPlaying = false;
        return false;
    } else if (controllers.size() == 1) {
        // This tank won do change to game over screen
        isPlaying = false;
        return false;
    }
    
    return true;
}

void Game::createPlayerTank(TankKeyBindings bindings, Color color) {
    Point2D startCoords = map.getRandomStartCoords();
    createPlayerTank(bindings, startCoords.getX(), startCoords.getY(), 90, color);
}

void Game::createPlayerTank(TankKeyBindings bindings, int x, int y, int direction, Color color) {
    unique_ptr<Tank> tank(new Tank(100, x, y, direction, color, false, controllers.size(), entities));
    unique_ptr<PlayerController> p (new PlayerController(*tank.get(), bindings));
    
    controllers.push_back(move(p));
    entities.push_back(move(tank));
}

void Game::handleKey(char a) {
    for(int i = 0; i < controllers.size(); i++) {
        controllers[i]->act(a);
    }
}

void Game::update() {
    updateMap();
    updateEntities();
}

void Game::checkCollisions() {
    for(int i = 0; i < entities.size(); i++) {
        // Check for overlapping coordinates
        double ex = entities[i]->getX();
        double ey = entities[i]->getY();
        double ewidth = entities[i]->getWidth();
        double eheight = entities[i]->getHeight();
        
        // Check for overlapping obstacles around entities[i]
        
        for(int x = ex + entities[i]->getWidth(); x > ex - ewidth; x--) {
            for (int y = ey + entities[i]->getHeight(); y > ey - eheight; y--) {
                MapObject* obj;
                if((obj = map.getMapObjectAt(x, y)) != nullptr) {
                    if(Tank *t = dynamic_cast<Tank*>(entities[i].get())) {
                        checkCollision(*t, *obj);
                    } else if(Projectile *p = dynamic_cast<Projectile*>(entities[i].get())) {
                        if(checkCollision(*p, *obj)) {
                            entities.erase(entities.begin() + i);
                        }
                    }
                }
            }
        }
        
        for(int j = 0; j < entities.size(); j++) {
            // Check if entities[i] and entities[j] overlap
            if(Tank *t1 = dynamic_cast<Tank*>(entities[i].get())) {
                if(Tank *t2 = dynamic_cast<Tank*>(entities[j].get())) {
                    checkCollision(*t1, *t2);
                    checkCollision(*t2, *t1);
                } else if(Projectile *p = dynamic_cast<Projectile*>(entities[j].get())) {
                    if(checkCollision(*t1, *p)) {
                        entities.erase(entities.begin() + i);
                    }
                }
            }
        }
    }
}

void Game::draw() {
    Color color;
    color.red = 1;
    color.green = 1;
    color.blue = 1 ;
    
    Obstacle o ("water",1,1,50,50,color);
    o.draw();
    map.drawMap();
    
    for(int i = 0; i < entities.size(); i++) {
        entities[i]->draw();
    }
}

void Game::updateMap() {
    // Empty for the time being until we have time to implement destructible obstacles
}

void Game::updateEntities() {
    checkCollisions();
}

bool Game::checkCollision(Projectile &p, MapObject &mobj) {
    
    bool topLeftOverlap = isOverlapping(p.getX(), p.getY(), mobj),
        topRightOverlap = isOverlapping(p.getX() + p.getWidth(), p.getY(), mobj),
        bottomLeftOverlap = isOverlapping(p.getX(), p.getY() + p.getHeight(), mobj),
        bottomRightOverlap = isOverlapping(p.getX() + p.getWidth(), p.getY() + p.getHeight(), mobj);
    
    if(topLeftOverlap || topRightOverlap || bottomLeftOverlap || bottomRightOverlap) {
        return true;
    }
    
    return false;
}

void Game::checkCollision(Tank &t, MapObject &mobj) {
    int controllerId = t.getControllerId();
    
    bool topLeftOverlap = isOverlapping(t.getX(), t.getY(), mobj),
        topRightOverlap = isOverlapping(t.getX() + t.getWidth(), t.getY(), mobj),
        bottomLeftOverlap = isOverlapping(t.getX(), t.getY() + t.getHeight(), mobj),
        bottomRightOverlap = isOverlapping(t.getX() + t.getWidth(), t.getY() + t.getHeight(), mobj);
    
    // Check if obstacle overlaps in front
    if(topLeftOverlap || topRightOverlap) {
        // disable moving forward
        controllers[controllerId]->setCanMoveForward(false);
    }
    
    // Check if obstacle overlaps in back
    if(bottomLeftOverlap || bottomRightOverlap) {
        // disable moving backward
        controllers[controllerId]->setCanMoveBack(false);
    }
    
    // Check if obstacle overlaps the left side, topLeft coordinate already checked so check bottomLeft
    if(topLeftOverlap || bottomLeftOverlap) {
        // disable rotating left
        controllers[controllerId]->setCanRotateLeft(false);
    }
    
    // Check if obstacle overlaps the right side, topRight coordinate already checked so check bottomRight
    if(topRightOverlap || bottomRightOverlap) {
        // disable rotating right
        controllers[controllerId]->setCanRotateRight(false);
    }
}

bool Game::checkCollision(Tank &t, Projectile &p) {
    // Check if projectile and tank are overlapping
    
    bool topLeftOverlap = isOverlapping(t.getX(), t.getY(), p),
        topRightOverlap = isOverlapping(t.getX() + t.getWidth(), t.getY(), p),
        bottomLeftOverlap = isOverlapping(t.getX(), t.getY() + t.getHeight(), p),
        bottomRightOverlap = isOverlapping(t.getX() + t.getWidth(), t.getY() + t.getHeight(), p);
    
    if(topLeftOverlap || topRightOverlap || bottomLeftOverlap || bottomRightOverlap) {
        t.setHealth(t.getHealth() - p.getDamage());
        return true;
    }
    
    return false;
}

void Game::checkCollision(Tank &t1, Tank &t2) {
    int controllerIdOne = t1.getControllerId();
    
    bool topLeftOverlap = isOverlapping(t1.getX(), t1.getY(), t2),
        topRightOverlap = isOverlapping(t1.getX() + t1.getWidth(), t1.getY(), t2),
        bottomLeftOverlap = isOverlapping(t1.getX(), t1.getY() + t1.getHeight(), t2),
        bottomRightOverlap = isOverlapping(t1.getX() + t1.getWidth(), t1.getY() + t1.getHeight(), t2);
    
    // Check if overlapping on t1 front
    if(topLeftOverlap || topRightOverlap) {
        controllers[controllerIdOne]->setCanMoveForward(false);
    }
    
    // Check if overlapping on t1 back
    if(bottomLeftOverlap || bottomRightOverlap) {
        controllers[controllerIdOne]->setCanMoveBack(false);
    }
    
    // Check if overlapping on t1 left side
    if(topLeftOverlap || bottomLeftOverlap) {
        controllers[controllerIdOne]->setCanRotateLeft(false);
    }
    
    // Check if obstacle overlaps t1 right side
    if(topRightOverlap || bottomRightOverlap) {
        controllers[controllerIdOne]->setCanRotateRight(false);
    }
}

bool Game::isOverlapping(int xIn, int yIn, MapObject &mobj) const {
    if (xIn < mobj.getX()) {
        // out of bounds to the left of the rectangle
        return false;
    }
    if (xIn > mobj.getX() + mobj.getWidth()) {
        // out of bounds to the right of the rectangle
        return false;
    }
    if (yIn < mobj.getY()) {
        // out of bounds above the rectangle
        return false;
    }
    if (yIn > mobj.getY() + mobj.getHeight()) {
        // out of bounds below the rectangle
        return false;
    }
    return true;
}

bool Game::isOverlapping(int xIn, int yIn, Entity &entity) const {
    if (xIn < entity.getX()) {
        // out of bounds to the left of the rectangle
        return false;
    }
    if (xIn > entity.getX() + entity.getWidth()) {
        // out of bounds to the right of the rectangle
        return false;
    }
    if (yIn < entity.getY()) {
        // out of bounds above the rectangle
        return false;
    }
    if (yIn > entity.getY() + entity.getHeight()) {
        // out of bounds below the rectangle
        return false;
    }
    return true;
}
