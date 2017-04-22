//
//  LevelEditor.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Obstacle.hpp"
#include "LevelEditor.hpp"

void LevelEditor::addObstacle(string name,int x, int y, int height, int width, Color color) {
    Obstacle o(name, x, y, height, width, color);
    currentMap.addMapObj(o);
}

void LevelEditor::addObstacle(string name,int x, int y, int height, int width, Color color, Terrain terrain){
    Obstacle o(name,x, y, height, width,color, terrain);
    currentMap.addMapObj(o);
}

void LevelEditor::addTerrain(string name,int x, int y, int height, int width, Color color, bool isPassible){
    Terrain t(name,x, y,height, width,color,isPassible);
    currentMap.addMapObj(t);
}

void LevelEditor::removeMapObjAt(int x, int y){
    currentMap.removeMapObjAt(x,y);
}

void LevelEditor::addPreferredStart(int x, int y){
    currentMap.addPreferredStartCoord(x,y);
}

void LevelEditor::removePreferredStart(int x, int y){
    currentMap.removePreferredStartCoord(x,y);
}


void LevelEditor::fillTerrain(Terrain t){
    for(int x=0;x<currentMap.getWidth();x++){
        for(int y=0;y<currentMap.getHeight();y++){
            if(currentMap.getMapObjectAt(x,y)==nullptr){
                t.setXcoord(x);
                t.setYcoord(y);
                currentMap.addMapObj(t);
            }
        }
    }
}







