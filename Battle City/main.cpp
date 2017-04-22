//
//  main.cpp
//  Battle City
//
//  Created by Yixiong Zhang on 4/3/17.
//  Copyright © 2017 Yixiong Zhang. All rights reserved.
//

#include "Tank.hpp"
#include "Entity.hpp"
#include "Projectile.hpp"
#include "Obstacle.hpp"
#include "Terrain.hpp"
#include "LevelEditor.hpp"
#include "Color.hpp"
#include "PlayerController.hpp"
#include "MapIO.hpp"
#include "Obstacle.hpp"
#include "Terrain.hpp"
#include "Game.hpp"

#include <vector>
#include <iostream>
using namespace std;

void testObstacleandTerrain();
void testLevelEditor();
void testTank();
void testProjectile();
void testGame();
void testMap();
void testMapIO();
void testPlayerControllers();


int main(int argc, const char * argv[]) {
    
    testObstacleandTerrain();
    testLevelEditor();
    testTank();
    testProjectile();
    testGame();
    testMap();
    testMapIO();
    testPlayerControllers();
    return 0;

}

// Testing tank.

void testTank(){
    Color color;
    color.red = 1;
    color.blue = 2;
    color.green = 3;
    vector <std::unique_ptr<Entity>> entities;

    Tank t(100, 1, 2, 3, color, false, 0, entities);
    double direction = t.getDirection();
    t.rotate(EPOS);
    if(direction< t.getDirection()){
        cout<< "PASS 1" <<endl;
    }
    
    //Testing direction.
    
    direction = t.getDirection();
    t.rotate(ENEG);
    if (direction > t.getDirection()){
        cout <<"PASS 2"<<endl;
    }
    
    //Testing shoot.
    
    t.shoot();
    if (entities[0]!=nullptr){
        cout <<"PASS 3"<<endl;
    }
    
   //Testing setHealth and getHealth.
    
    t.setHealth(20);
    t.getHealth();
    if (20 == t.getHealth()) {
        cout << "PASS 4"<< endl;
    } else {
        cout << "FAIL"<<endl;
    }
    
    //Testing getControllerID.
    
    double controllerId = 0;
    t.getControllerId();
    if (controllerId == t.getControllerId()){
        cout<<"PASS 5"<< endl;
    } else {
        cout << "FAIL" <<endl;
    }
   

    //Testing getX.
    
    if(1 == t.getX()){
        cout <<"PASS 6"<<endl;
    } else {
        cout << "FAIL"<<endl;
    }
    
    //Testing getY.
    
    if(2 == t.getY()){
        cout <<"PASS 7" <<endl;
    }else{
        cout << "FAIL" <<endl;
    }
    
    //Testing setWidth and getWidth.
    t.setWidth(30);
    t.getWidth();
    if(30==t.getWidth()){
        cout <<"PASS 8"<<endl;
    }else{
        cout << "FAIL"<<endl;
    }
    
    //Testing setHeight and getHeight.
    
    t.setHeight(40);
    t.getHeight();
    if(40==t.getHeight()){
        cout << "PASS 9"<<endl;
    }else{
        cout << "FAIL" <<endl;
    }
    
    //Testing setColor and getColor.
    
    t.setColor(225,0,0);
    color = t.getColor();
   
    if (color.red == 225){
        cout << "PASS 10"<<endl;
    }else{
        cout << "FAIL"<<endl;
    }
}

void testObstacleandTerrain(){
    
    Color color;
    color.red = 100;
    color.green = 100;
    color.blue = 100 ;
    
    Obstacle o ("water",1,2,3,4,color);
    
    Terrain t("stand",4,3,2,1,color,false);
    
    //test set and getunderlyingTerrain()
    o.setUnderlyingTerrain(t);
    //should prints "stand"
    cout<<o.getunderlyingTerrain().getName()<<endl;
    
    //test get and setIsPassable()
    t.setIsPassable(true);
    //should prints 1
    cout<<t.getIsPassable()<<endl;
    
}

void testLevelEditor(){
    
    Map m(20, 10);
    Color color;
    color.red = 212;
    color.green = 97;
    color.blue = 123;
    
    // Add mapobjs
    Terrain t("Water", 2, 1, 3, 4, color, false);
    
    LevelEditor l(m);
    
    l.addTerrain("stand", 1, 3, 3, 4,color,true);
    l.addTerrain("Rocks", 2, 1, 3, 4, color, false);
    l.addObstacle("Cliffs", 1, 2, 3, 4, color,t);
    l.save("map.txt");
    l.load("map.txt");

    l.addPreferredStart(1, 2);
}

// Testing projectile.

void testProjectile(){
    
    Color color;
    color.red = 4;
    color.blue = 5;
    color.green = 6;
    
    Projectile p(200,3,4,5,color);
    
    p.setDamage(30);

    // Testing getDamge.
    
    if (30==p.getDamage()){
        cout << "PASS 11" <<endl;
    } else {
        cout<<"Fail" << endl;
    }
    
    //Testing setCanPass and getCanPass.
    
    p.setCanPassAllTerrain(false);
    
    if (false==p.getCanPassAllTerrain()){
        cout << "PASS 12" << endl;
    }else{
        cout<< "Fail" << endl;
    }
}

void testGame() {
    Map m(20, 10);
    Color color;
    color.red = 212;
    color.green = 97;
    color.blue = 123;
    
    // Add mapobjs
    m.addMapObj(new Obstacle("Wall", 1, 2, 3, 4, color));
    m.addMapObj(new Terrain("Water", 2, 1, 3, 4, color, false));
    
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
    
    Game game(m);
    
    game.createPlayerTank(tkb, color2);
    game.createPlayerTank(tkb, color);
    
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
    m.addMapObj(new Obstacle("Wall", 1, 2, 3, 4, color));
    m.addMapObj(new Obstacle("Wall", 3, 2, 3, 4, color));
    m.addMapObj(new Terrain("Water", 2, 1, 3, 4, color, false));
    
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
    
    m.addMapObj(new Obstacle("Wall", 1, 1, 1, 1, color));
    m.addMapObj(new Terrain("Grass", 1, 2, 1, 1, color, true));
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
    
    vector<std::unique_ptr<Entity>> entities;
    
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
    
    pc.act('m');
    if(entities.size() > 0) {
        cout << "Passed 15" << endl;
    }
}


