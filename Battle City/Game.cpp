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
#include <iostream>

Game::Game(Map &map) : map(map) {}

Game::~Game() {}


int Game::checkGameStatus() {
    for(int i = 0; i < controllers.size(); i++) {
        if(controllers[i].get()->getTank().getHealth() == 0) {
            controllers[i].reset(nullptr);
        }
    }
    
    for(int i = 0; i < controllers.size(); i++) {
        if (controllers[i] == nullptr) {
            // draw change to game over screen
            isPlaying = false;
            return i;
        }
    }
    
    return -1;
}

void Game::createPlayerTank(TankKeyBindings bindings, Color color) {
    Point2D startCoords = map.getRandomStartCoords();
    createPlayerTank(bindings, startCoords.getX() * 10, startCoords.getY() * 10, 90, color);
}

void Game::createPlayerTank(TankKeyBindings bindings, int x, int y, int direction, Color color) {
    unique_ptr<Tank> tank(new Tank(100, x, y, direction, color, false, controllers.size(), entities));
    unique_ptr<PlayerController> p (new PlayerController(*tank.get(), bindings));
    
    controllers.push_back(move(p));
    entities.push_back(move(tank));
}

void Game::handleKey(char a) {
    for(int i = 0; i < controllers.size(); i++) {
        if(controllers[i] != nullptr) {
            controllers[i]->act(a);
        }
    }
}

void Game::update() {
    updateMap();
    updateEntities();
}

void Game::checkCollisions() {
    for(int i = 0; i < entities.size(); i++) {
        bool skipIteration = false;
        
        // Check for overlapping coordinates
        double ex = entities[i]->getX();
        double ey = entities[i]->getY();
        double ewidth = entities[i]->getWidth();
        double eheight = entities[i]->getHeight();
        
        // Check for overlapping obstacles around entities[i]
        for(int x = ex + ewidth; x > ex - ewidth; x--) {
            for (int y = ey + eheight; y > ey - eheight; y--) {
                MapObject* obj = map.getMapObjectAt(x/10, y/10);
                //cout << x/10 << " " << y/10 << endl;
                if(obj != nullptr) {
                    Terrain* tObj = dynamic_cast<Terrain*>(obj);
                    
                    if(tObj && tObj->getIsPassable()) {
                        continue;
                    }
                    
                    if(Tank *t = dynamic_cast<Tank*>(entities[i].get())) {
                        checkCollision(*t, *obj);
                    } else if(Projectile *p = dynamic_cast<Projectile*>(entities[i].get())) {
                        if(checkCollision(*p, *obj)) {
                            entities.erase(entities.begin() + i);
                            skipIteration = true;
                            break;
                        }
                    }
                }
            }
            
            if(skipIteration) {
                skipIteration = false;
                break;
            }
        }
        
        for(int j = 0; j < entities.size(); j++) {
            if(j != i) {
                // Check if entities[i] and entities[j] overlap
                if(Tank *t1 = dynamic_cast<Tank*>(entities[i].get())) {
                    if(Projectile *p = dynamic_cast<Projectile*>(entities[j].get())) {
                        if(checkCollision(*t1, *p)) {
                            cout << p->getDamage() << " " << t1->getHealth() << endl;
                            
                            // Erase bullet
                            entities.erase(entities.begin() + j);

                            if(t1->getHealth() <= 0) {
                                entities.erase(entities.begin() + i);
                            }
                            
                            skipIteration = true;
                            break;
                        }
                    }
                }
            }
            
            if(skipIteration) {
                skipIteration = false;
                break;
            }
        }
    }
}

void Game::draw() {
    map.drawMap();
    for(int i = 0; i < entities.size(); i++) {
        entities[i]->draw();
    }
}

void Game::updateMap() {
    // Empty for the time being until we have time to implement destructible obstacles
}

void Game::updateEntities() {
    // Bullet destoryed when leaving  map
    for(int i = 0; i < entities.size(); i++) {
        if(Projectile* p = dynamic_cast<Projectile*>(entities[i].get())) {
            if(p->getX() < 0 || p->getX() + p->getWidth() > map.getWidth() * 10
               || p->getY() < 0 || p->getY() + p->getHeight() > map.getHeight() * 10) {
                entities.erase(entities.begin()+i);
            } else {
                p->move(EPOS);
            }
        }
    }
    
    for(int i = 0; i < controllers.size(); i++) {
        if(PlayerController* pc = dynamic_cast<PlayerController*>(controllers[i].get())) {
            pc->update();
        }
    }
    
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
    
    // Point overlaps, (for side overlaps while allowing movement along walls)
    bool topLeftOverlap = isOverlapping(t.getX(), t.getY(), mobj),
        topRightOverlap = isOverlapping(t.getX() + t.getWidth(), t.getY(), mobj),
        bottomLeftOverlap = isOverlapping(t.getX(), t.getY() + t.getHeight(), mobj),
        bottomRightOverlap = isOverlapping(t.getX() + t.getWidth(), t.getY() + t.getHeight(), mobj);
    
    // Map Object Overlap (for corner overlaps)
    bool mTopLeftOverlap = isOverlapping(mobj.getX(), mobj.getY(), t),
        mTopRightOverlap = isOverlapping(mobj.getX() + mobj.getWidth(), mobj.getY(), t),
        mBottomLeftOverlap = isOverlapping(mobj.getX(), mobj.getY() + mobj.getHeight(), t),
        mBottomRightOverlap = isOverlapping(mobj.getX() + mobj.getWidth(), mobj.getY() + mobj.getHeight(), t);
    
    if(t.getDirection() == 90) {
        if(topLeftOverlap && topRightOverlap) {
            controllers[controllerId]->setCanMoveForward(false);
        } else if(bottomLeftOverlap && bottomRightOverlap) {
            controllers[controllerId]->setCanMoveBack(false);
        }
        
        if((mTopLeftOverlap || mTopRightOverlap)) {
            controllers[controllerId]->setCanMoveBack(false);
        } else if(mBottomLeftOverlap || mBottomRightOverlap) {
            controllers[controllerId]->setCanMoveForward(false);
        }
    }
    
    if(t.getDirection() == 270) {
        if(topLeftOverlap && topRightOverlap) {
            controllers[controllerId]->setCanMoveBack(false);
        } else if (bottomLeftOverlap && bottomRightOverlap) {
            controllers[controllerId]->setCanMoveForward(false);
        }
        
        if(mTopLeftOverlap || mTopRightOverlap) {
            controllers[controllerId]->setCanMoveForward(false);
        } else if(mBottomLeftOverlap || mBottomRightOverlap) {
            controllers[controllerId]->setCanMoveBack(false);
        }
    }
    
    if(t.getDirection() == 0) {
        if(topRightOverlap && bottomRightOverlap) {
            controllers[controllerId]->setCanMoveForward(false);
        } else if (topLeftOverlap && bottomLeftOverlap) {
            controllers[controllerId]->setCanMoveBack(false);
        }
        
        if(mTopLeftOverlap || mBottomLeftOverlap) {
            controllers[controllerId]->setCanMoveForward(false);
        } else if(mTopRightOverlap || mBottomRightOverlap) {
            controllers[controllerId]->setCanMoveBack(false);
        }
    }
    
    if(t.getDirection() == 180) {
        if(topRightOverlap && bottomRightOverlap) {
            controllers[controllerId]->setCanMoveBack(false);
        } else if (topLeftOverlap && bottomLeftOverlap) {
            controllers[controllerId]->setCanMoveForward(false);
        }
        
        if(mTopLeftOverlap || mBottomLeftOverlap) {
            controllers[controllerId]->setCanMoveBack(false);
        } else if(mTopRightOverlap || mBottomRightOverlap) {
            controllers[controllerId]->setCanMoveForward(false);
        }
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
