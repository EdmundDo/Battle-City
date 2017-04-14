//
//  Game.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Game.hpp"

#include <random>
using namespace std;

Game::Game(Map map) : map(map) {}

Game::~Game() {}

bool Game::checkGameStatus() {
    for(int i = 0; i < controllers.size(); i++) {
        if(controllers[i].getTank().getHealth == 0) {
            controllers.erase(controllers.begin() + i);
        }
    }
    
    if (controllers.size() == 0) {
        // draw
        isPlaying = false;
    } else if (controllers.size() == 1) {
        controllers[0].getTank().getColor(); // This tank won
        isPlaying = false;
    }
}

void Game::createPlayerTank(TankKeyBindings bindings) {
    vector<Point2D> startCoords = map.getPreferredStartCoords();
    
    // get random start coordinate
    random_device rnd;
    int rand_index = rnd() % startCoords.size();
    
    createTankController(bindings, startCoords[rand_index].x, startCoords[rand_index].y);
}

void Game::createPlayerTank(TankKeyBindings bindings, int x, int y) {
    Tank tank();        // Init with start coords startCoords[rand_index].x and startCoords[rand_index].y
                        // etc., etc...
    
    controllers.push_back(PlayerController(tank, bindings));
}

void Game::update() {
    updateMap();
    updateEntities();
}

void Game::checkCollisions() {
    for(int i = 0; i < entities.size(); i++) {
        // Check for overlapping coordinates
        
        double x = entities[i].getX();
        double y = entities[i].getY();
        
        // Check area around entities[i]
        // Map.getObjectAt()
        // And check for overlap
        int checkX = x + 1, checkY;
        
        for(int checkX = x + entities[i].getWidth(); checkX > x - entities[i].getWidth(); i--
        
        for(int j = 0; j < entities.size(); j++) {
            // Check if entities[i] and entities[j] overlap
        }
    }
}

void Game::updateMap() {
    // Empty for the time being until we implement destriuctible obstacles
}

void Game::updateEntities() {
    checkCollisions();
    
    for(int i = 0; i < entities.size(); i++) {
        entities.draw();
    }
}



void Game::handleCollision(Entity e, MapObject mobj) {
    
}

void Game::handleCollision(Entity e1, Entity e2) {
    
}
