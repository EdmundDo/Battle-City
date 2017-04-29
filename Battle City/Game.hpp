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
    Game(Map &map);
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
    
    void createPlayerTank(TankKeyBindings bindings, Color color);
    
    /**
     * Requires: x < map.getWidth() and y < map.getHeight()
     * Modifies: controllers
     * Effects: Adds a tank to the map with the specified controller
     */
    
    void createPlayerTank(TankKeyBindings bindings, int x, int y, int direction, Color color);
    
    /**
     * Requires: nothing
     * Modifies: tank
     * Effects: triggers the controller
     */
    
    void handleKey(char a);
    
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
    
    void draw();
    
private:
    bool isPlaying;
    
    Map &map;
    vector<unique_ptr<Entity>> entities;
    vector<unique_ptr<Controller>> controllers;
    
    /**
     * Helper methods for update()
     */
    
    void updateMap();
    void updateEntities();
    
    /**
     * Requires: nothing
     * Modifies: p
     * Effects: destroys p if collision with mobj
     */
    
    bool checkCollision(Projectile &p, MapObject &mobj);
    
    /**
     * Requires: nothing
     * Modifies: t's controller
     * Effects: prevents the entity from moving through mobj
     */
    
    void checkCollision(Tank &t, MapObject &mobj);
    
    /**
     * Requires: nothing
     * Modifies: t
     * Effects: tank takes damage from projectile if collision
     */
    
    bool checkCollision(Tank &t, Projectile &p);
    
    /**
     * Requires: nothing
     * Modifies: t1 controller and t2 controller
     * Effects: stops the tanks from moving through one another
     */
    
    void checkCollision(Tank &t1, Tank &t2);
    
    bool isOverlapping(int xIn, int yIn, MapObject &mobj) const;
    bool isOverlapping(int xIn, int yIn, Entity &entity) const;
};

#endif /* Game_hpp */
