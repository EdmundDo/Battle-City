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


#include <iostream>
using namespace std;

void testMapIO();
void testPlayerControllers();

int main(int argc, const char * argv[]) {
    testMapIO();
    return 0;
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


