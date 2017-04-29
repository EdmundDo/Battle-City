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
                    checkCollision(*t1, *p, i);
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
    if(isOverlapping(p.getX(), p.getY(), mobj)
       || isOverlapping(p.getX() + p.getWidth(), p.getY(), mobj)
       || isOverlapping(p.getX() + p.getWidth(), p.getY() + p.getHeight(), mobj)
       || isOverlapping(p.getX(), p.getY() + p.getHeight(), mobj)) {
        return true;
    }
    
    return false;
}

bool Game::checkCollision(Tank &t, MapObject &mobj) {
    int controllerId = t.getControllerId();
    
    // Check if obstacle overlaps in front
    if(isOverlapping(t.getX(), t.getY(), mobj) || isOverlapping(t.getX() + t.getWidth(), t.getY(), mobj)) {
        // disable moving forward
        controllers[controllerId]->setCanMoveForward(false);
    }
    
    // Check if obstacle overlaps in back
    if(isOverlapping(t.getX(), t.getY() + t.getHeight(), mobj) || isOverlapping(t.getX() + t.getWidth(), t.getY() + t.getHeight(), mobj)) {
        // disable moving backward
        controllers[controllerId]->setCanMoveBack(false);
    }
    
    // Check if obstacle overlaps the left side, topLeft coordinate already checked so check bottomLeft
    if(isOverlapping(t.getX(), t.getX() + t.getHeight(), mobj)) {
        // disable rotating right
        controllers[controllerId]->setCanRotateRight(false);
    }
    
    if(true) {       // Check if obstacle overlaps the left side
        controllers[controllerId]->setCanRotateLeft(false);
    }
}

void Game::checkCollision(Tank &t1, Tank &t2) {
    int controllerIdOne = t1.getControllerId();
    int controllerIdTwo = t2.getControllerId();
    
    if(true) {              // Check if overlapping on t1 front and t2 right side
        controllers[controllerIdOne]->setCanMoveForward(false);
        controllers[controllerIdTwo]->setCanRotateRight(false);
    } else if(true) {       // Check if overlapping on t1 front and t2 left side
        controllers[controllerIdOne]->setCanMoveForward(false);
        controllers[controllerIdTwo]->setCanRotateLeft(false);
    } else if(true) {       // Check if overlapping on t1 back and t2 right side
        controllers[controllerIdOne]->setCanMoveBack(false);
        controllers[controllerIdTwo]->setCanRotateRight(false);
    } else if(true) {       // Check if obstacle overlaps t1 back and t2 left side
        controllers[controllerIdOne]->setCanMoveBack(false);
        controllers[controllerIdTwo]->setCanRotateLeft(false);
    }
}

void Game::checkCollision(Tank &t, Projectile &p, int i) {
    if(true) {              // Check if projectile and tank are overlapping
        t.setHealth(t.getHealth() - p.getDamage());
    }
    
    entities.erase(entities.begin() + i);
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
