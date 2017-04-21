//
//  main.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Color.hpp"
#include "PlayerController.hpp"
#include "Tank.hpp"
#include "MapIO.hpp"
#include "Obstacle.hpp"
#include "Terrain.hpp"
#include "Game.hpp"


#include <iostream>
using namespace std;

void testGame();
void testMap();
void testMapIO();
void testPlayerControllers();

int main(int argc, const char * argv[]) {
    testGame();
    return 0;
}

void testGame() {
    Map m(20, 10);
    Color color;
    color.red = 212;
    color.green = 97;
    color.blue = 123;
    
    // Add mapobjs
    Obstacle o("Wall", 1, 2, 3, 4, color);
    Terrain t("Water", 2, 1, 3, 4, color, false);
    m.addMapObj(o);
    m.addMapObj(t);
    
    // Controller
    TankKeyBindings tkb;
    tkb.mbk = 's';
    tkb.mfk = 'w';
    tkb.rlk = 'a';
    tkb.rrk = 'd';
    tkb.sk = 'm';
    
    Color color2;
    color.red = 212;
    color.green = 97;
    color.blue = 123;
    
    vector<Entity*> entities;
    
    Game game(m);
    
    game.createPlayerTank(tkb, color2);
    
    if(game.checkGameStatus()) {
        cout << "Passed 1" << endl;
    }
    
    
    
}

void testMap() {
    Map m(20, 10);
    Color color;
    color.red = 212;
    color.green = 97;
    color.blue = 123;
    
    if(m.getWidth() == 20) {
        cout << "Passed 1" << endl;
    }
    
    if(m.getHeight() == 10) {
        cout << "Passed 2" << endl;
    }
    
    // Add mapobjs
    Obstacle o("Wall", 1, 2, 3, 4, color);
    Terrain t("Water", 2, 1, 3, 4, color, false);
    m.addMapObj(o);
    m.addMapObj(t);
    
    if(m.getObstacleAt(1, 2)->getName() == "Wall") {
        cout << "Passed 3" << endl;
    }
    
    if(m.getTerrainAt(2, 1)->getName() == "Water") {
        cout << "Passed 4" << endl;
    }
    
    if(m.getMapObjectAt(2, 1)->getName() == "Water") {
        cout << "Passed 4.1" << endl;
    }
    
    // Adding and removing startCoords
    m.addPreferredStartCoord(2, 3);
    Point2D p = m.getRandomStartCoords();
    if(p.getX() == 2 && p.getY() == 3 && m.getPreferredStartCoords().size() == 1) {
        cout << "Passed 5" << endl;
    }
    
    // Run again to check randomness
    m.addPreferredStartCoord(1, 2);
    Point2D p2 = m.getRandomStartCoords();
    cout << p2.getX() << " " << p2.getY() << endl;
    
    m.removePreferredStartCoord(1, 2);
    if(m.getPreferredStartCoords().size() == 1) {
        cout << "Passed 5.1" << endl;
    }
    
    m.removePreferredStartCoord(2, 2);
    
    // Remove mapobj
    m.removeMapObjAt(2, 1);
    if(m.getMapObjectAt(2, 1) == nullptr) {
        cout << "Passed 6" << endl;
    }
}

void testMapIO() {
    Map m(10, 10);
    Color color;
    color.red = 212;
    color.green = 97;
    color.blue = 123;
    Obstacle o("Wall", 1, 1, 1, 1, color);
    Terrain t("Grass", 1, 2, 1, 1, color, true);
    
    m.addMapObj(o);
    m.addMapObj(t);
    m.addPreferredStartCoord(7, 8);
    
    MapIO::write(m, "map.txt");
    MapData md = MapIO::read("map.txt");
    cout << "Width: " << md.width << " Height: " << md.height << endl;
    for (int i = 0; i < md.preferredStartCoords.size(); i++) {
        cout << md.preferredStartCoords[i].getX() << " " << md.preferredStartCoords[i].getY() << endl;
    }
    
    for (int i = 0; i < md.mapObjs.size(); i++) {
        cout << md.mapObjs[i]->getName() << " " << md.mapObjs[i]->getCoordX() << " " << md.mapObjs[i]->getCoordY() << endl;
    }
    
}

void testPlayerControllers() {
    TankKeyBindings tkb;
    tkb.mbk = 's';
    tkb.mfk = 'w';
    tkb.rlk = 'a';
    tkb.rrk = 'd';
    tkb.sk = 'm';
    
    Color color;
    color.red = 212;
    color.green = 97;
    color.blue = 123;
    
    vector<Entity*> entities;
    
    Tank t(100, 10, 20, 90, color, false, 0, entities);
    PlayerController pc(t, tkb);
    
    // Move in Y direction
    int x = t.getX(), y = t.getY();
    cout << "Tank CoordY: " << y << " CoordX: " << x << endl;
    pc.act('w');
    if(y < t.getY()) {
        cout << "PASSED 1" << endl;
    }
    x = t.getX(), y = t.getY();
    cout << "Tank CoordY: " << y << " CoordX: " << x << endl;
    
    x = t.getX(), y = t.getY();
    cout << "Tank CoordY: " << y << " CoordX: " << x << endl;
    pc.act('s');
    if(y > t.getY()) {
        cout << "PASSED 2" << endl;
    }
    x = t.getX(), y = t.getY();
    cout << "Tank CoordY: " << y << " CoordX: " << x << endl;
    
    // test direction
    int dir = t.getDirection();
    cout << "Tank dir: " << dir << endl;
    pc.act('a');
    if(dir < t.getDirection()) {
        cout << "PASSED 3" << endl;
    }
    dir = t.getDirection();
    cout << "Tank dir: " << x << endl;

    dir = t.getDirection();
    cout << "Tank dir: " << dir << endl;
    pc.act('d');
    if(dir > t.getDirection()) {
        cout << "PASSED 4" << endl;
    }
    dir = t.getDirection();
    cout << "Tank dir: " << dir << endl;
    
    // test moving in x (aka 0 degrees)
    for(int i = 0; i < 90; i++) {
        pc.act('d');
    }
    
    dir = t.getDirection();
    cout << "Tank dir: " << dir << endl;
    
    x = t.getX(), y = t.getY();
    cout << "Tank CoordY: " << y << " CoordX: " << x << endl;
    pc.act('w');
    if(x < t.getX()) {
        cout << "PASSED 5" << endl;
    }
    x = t.getX(), y = t.getY();
    cout << "Tank CoordY: " << y << " CoordX: " << x << endl;
    
    x = t.getX(), y = t.getY();
    cout << "Tank CoordY: " << y << " CoordX: " << x << endl;
    pc.act('s');
    if(x > t.getX()) {
        cout << "PASSED 6" << endl;
    }
    x = t.getX(), y = t.getY();
    cout << "Tank CoordY: " << y << " CoordX: " << x << endl;
    
    // testing getters and setters
    pc.setCanMoveBack(false);
    pc.setCanMoveForward(false);
    pc.setCanRotateLeft(false);
    pc.setCanRotateRight(false);
    
    if(!pc.getCanMoveBack()) {
        cout << "Passed 7" << endl;
    }
    if(!pc.getCanMoveForward()) {
        cout << "Passed 8" << endl;
    }
    if(!pc.getCanRotateRight()) {
        cout << "Passed 9" << endl;
    }
    if(!pc.getCanMoveBack()) {
        cout << "Passed 10" << endl;
    }
    
    pc.act('w');
    if(pc.getCanMoveBack()) {
        cout << "Passed 11" << endl;
    }
    pc.act('s');
    if(pc.getCanMoveForward()) {
        cout << "Passed 12" << endl;
    }
    pc.act('d');
    if(pc.getCanRotateLeft()) {
        cout << "Passed 13" << endl;
    }
    pc.act('a');
    if(pc.getCanRotateRight()) {
        cout << "Passed 14" << endl;
    }
}


