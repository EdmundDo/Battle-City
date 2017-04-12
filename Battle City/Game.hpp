//
//  Game.hpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "Entity.hpp"
#include "Map.hpp"
#include "MapObject.hpp"
#include "Controller.hpp"
#include "PlayerController.hpp"

#include <vector>
using namespace std;

class Game {
public:
    Game();
    ~Game();
    
    /**
     * Requires: nothing
     * Modifies: isPlaying
     * Effects: true if game over conditions have been met, false otherwise
     */
    
    bool checkGameStatus();
    
    /**
     * Requires: nothing
     * Modifies: controllers
     * Effects: Adds a tank to the map with the specified controller
     */
    
    void createPlayerTank(TankKeyBindings bindings);
    
    /**
     * Requires: x < map.getWidth() and y < map.getHeight()
     * Modifies: controllers
     * Effects: Adds a tank to the map with the specified controller
     */
    
    void createPlayerTank(TankKeyBindings bindings, int x, int y);
    
    /**
     * Requires: nothing
     * Modifies: map
     * Effects: Loads a playable map
     */
    
    void loadMap(Map &map);
    
    /**
     * Requires: isPlaying == true
     * Modifies: map and entities
     * Effects: updates the map and entities in the game
     */
    
    void update();
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: checks for collisions and sends it to a handler
     */
    
    void checkCollisions();
    
private:
    bool isPlaying;
    
    Map map;
    vector<Entity> entities;
    vector<Controller> controllers;
    
    /**
     * Helper methods for update()
     */
    
    void updateMap();
    void updateEntities();
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: prevents the entity from moving through mobj
     */
    
    void handleCollision(Entity e, MapObject mobj);
    
    /**
     * Requires: nothing
     * Modifies: e1, e2
     * Effects: e1 and e2 interacts
     */
    
    void handleCollision(Entity e1, Entity e2);
};

#endif /* Game_hpp */
