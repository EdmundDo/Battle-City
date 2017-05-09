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
        if(controllers[i].get()->getTank().getHealth() <= 0) {
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
    map.removePreferredStartCoord(startCoords.getX(), startCoords.getY());
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
        if(controllers[i] != nullptr) {
            controllers[i]->act(a);
        }
    }
}

void Game::update() {
    updateMap();
    updateEntities();
}

// Uses grid checks for simplicity
void Game::checkCollisions() {
    for(vector<unique_ptr<Entity>>::iterator eit = entities.begin(); eit < entities.end(); eit++) {
        
        Entity *entity = eit->get();
        
        int ex = entity->getGridX();
        int ey = entity->getGridY();
        int ewidth = entity->getWidth() / 10;
        int eheight = entity->getHeight() / 10;
        
        if(Tank *t = dynamic_cast<Tank*>(entity)) {

            // Check surroundings only if moved
            if(controllers[t->getControllerId()]->getRecentlyMoved()) {
                for(int x = ex + ewidth + 1; x >= ex - 1; x--) {
                    for (int y = ey + eheight + 1; y >= ey - 1; y--) {
                        MapObject* obj = map.getMapObjectGridAt(x, y);

                        if(obj != nullptr && !obj->getIsPassable()) {
                            checkCollision(*t, *obj);
                        }
                    }
                }
                controllers[t->getControllerId()]->setRecentlyMoved(false);
            }

            // Check if a bullet hit
            for(vector<unique_ptr<Entity>>::iterator pit = entities.begin(); pit < entities.end(); pit++) {
                if(pit->get() != entity) {
                    if(Projectile *p = dynamic_cast<Projectile*>(pit->get())) {
                        if(checkCollision(*t, *p)) {
                            
                            t->setHealth(t->getHealth() - p->getDamage());
                            // Erase bullet
                            pit = entities.erase(pit);
                            
                            // Erase tank
                            if(t->getHealth() <= 0) {
                                entities.erase(eit);
                                break;
                            }
                        }
                    }
                }
            }
        } else if(Projectile *p = dynamic_cast<Projectile*>(entity)) {

            int px = 0, py = 0, xcond = 0, ycond = 0;
            if(p->getDirection() == 0) {
                px = ex + ewidth;
                py = ey + eheight + 1;
                xcond = ex;
                ycond = ey - eheight - 1;
            } else if(p->getDirection() == 90) {
                px = ex + ewidth + 1;
                py = ey;
                xcond = ex - ewidth - 1;
                ycond = ey - eheight - 1;
            } else if(p->getDirection() == 180) {
                px = ex;
                py = ey + eheight + 1;
                xcond = ex - ewidth - 1;
                ycond = ey - eheight - 1;
            } else if(p->getDirection() == 270) {
                px = ex + ewidth + 1;
                py = ey + eheight + 1;
                xcond = ex - ewidth - 1;
                ycond = ey;
            }
            
            bool skipIteration = false;
            for(int x = px; x >= xcond; x--) {
                for (int y = py; y >= ycond; y--) {
                    MapObject* obj = map.getMapObjectGridAt(x, y);

                    if(obj != nullptr) {
                        Terrain* tObj = dynamic_cast<Terrain*>(obj);

                        if(!tObj) {
                            if(checkCollision(*p, *obj)) {
                                eit = entities.erase(eit);
                                skipIteration = true;
                                break;
                            }
                        }
                    }
                }
                
                if(skipIteration) {
                    break;
                }
            }
        }
    }
}

void Game::draw() {
    map.drawMap();
    for(int i = 0; i < entities.size(); i++) {
        entities[i]->draw();
        if(Tank *t = dynamic_cast<Tank*>(entities[i].get())) {
            int controllerId = t->getControllerId();
            int health = t->getHealth();
            string message = "Player " + to_string(controllerId + 1) + " " + to_string(health);
            
            glColor3ub(255, 255, 255);
            if(controllerId == 0) {
                glRasterPos2i(10, 515);
                for(int i = 0; i < message.length(); i++) {
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, message[i]);
                }
            } else if(controllerId == 1) {
                unsigned char messageStr[message.length()];
                strcpy((char*) messageStr, message.c_str());
                
                int length = glutBitmapLength(GLUT_BITMAP_HELVETICA_12, messageStr);
                glRasterPos2i(700 - length - 10, 515);
                for(int i = 0; i < message.length(); i++) {
                    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, message[i]);
                }
            }
        }
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
    cout << mobj.getGridY() << " " << t.getGridY() << endl;
    
    if(t.getDirection() == 0) {
        // if topLeft just touching wall
        if(mobj.getY() + mobj.getHeight() - 1 != t.getY() && mobj.getY() != t.getY() + t.getHeight()) {
            if((mobj.getGridX() == t.getGridX() + 1 && mobj.getGridY() == t.getGridY())
                       || (mobj.getGridX() == t.getGridX() + 1 && mobj.getGridY() == t.getGridY() + 1)
                       || t.getX() == map.getWidth() * 10) {
                controllers[controllerId]->setCanMoveForward(false);
            } else if ((mobj.getGridX() == t.getGridX() && mobj.getGridY() == t.getGridY())
                       || (mobj.getGridX() == t.getGridX() && mobj.getGridY() == t.getGridY() + 1)
                       || t.getX() == 0) {
                controllers[controllerId]->setCanMoveBack(false);
            }
        }
    }
    
    if(t.getDirection() == 90) {
        // if topLeft just touching wall (Allows mobility along walls)
        if(mobj.getX() + mobj.getWidth() - 1 != t.getX() && mobj.getX() != t.getX() + t.getWidth()) {
            if((mobj.getGridY() == t.getGridY() && mobj.getGridX() == t.getGridX())
                       || (mobj.getGridY() == t.getGridY() && mobj.getGridX() == t.getGridX() + 1)
                       || t.getY() == 0) {
                controllers[controllerId]->setCanMoveForward(false);
            } else if ((mobj.getGridY() == t.getGridY() + 1 && mobj.getGridX() == t.getGridX())
                       || (mobj.getGridY() == t.getGridY() + 1 && mobj.getGridX() == t.getGridX() + 1)
                       || t.getY() == map.getHeight() * 10) {
                controllers[controllerId]->setCanMoveBack(false);
            }
        }
    }
    
    if(t.getDirection() == 180) {
        // if topLeft just touching wall
        if(mobj.getY() + mobj.getHeight() - 1 != t.getY() && mobj.getY() != t.getY() + t.getHeight()) {
            if((mobj.getGridX() == t.getGridX() && mobj.getGridY() == t.getGridY())
                       || (mobj.getGridX() == t.getGridX() && mobj.getGridY() == t.getGridY() + 1)
                       || t.getX() == 0) {
                controllers[controllerId]->setCanMoveForward(false);
            } else if ((mobj.getGridX() == t.getGridX() + 1 && mobj.getGridY() == t.getGridY())
                       || (mobj.getGridX() == t.getGridX() + 1 && mobj.getGridY() == t.getGridY() + 1)
                       || t.getX() == map.getWidth() * 10) {
                controllers[controllerId]->setCanMoveBack(false);
            }
        }
    }
    
    if(t.getDirection() == 270) {
        // if topLeft just touching wall
        if(mobj.getX() + mobj.getWidth() - 1 != t.getX() && mobj.getX() != t.getX() + t.getWidth()) {
            if((mobj.getGridY() == t.getGridY() + 1 && mobj.getGridX() == t.getGridX())
                       || (mobj.getGridY() == t.getGridY() + 1 && mobj.getGridX() == t.getGridX() + 1)
                       || t.getY() == map.getHeight() * 10) {
                controllers[controllerId]->setCanMoveForward(false);
            } else if ((mobj.getGridY() == t.getGridY() && mobj.getGridX() == t.getGridX())
                       || (mobj.getGridY() == t.getGridY() && mobj.getGridX() == t.getGridX() + 1)
                       || t.getY() == 0) {
                controllers[controllerId]->setCanMoveBack(false);
            }
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
