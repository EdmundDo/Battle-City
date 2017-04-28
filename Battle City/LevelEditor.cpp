//
//  LevelEditor.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Obstacle.hpp"
#include "LevelEditor.hpp"

LevelEditor::LevelEditor(int width, int height) : currentMap(width, height), selectedIndex(0), selectedColorIndex(0), red(0), green(0), blue(0) {
    readObjects();
}

LevelEditor::LevelEditor(string filepath) : currentMap(filepath), selectedIndex(0), red(0), green(0), blue(0) {
    readObjects();
}

void LevelEditor::addObstacle(string name,int x, int y, int height, int width, Color color) {
    currentMap.addMapObj(new Obstacle(name, x, y, height, width, color));
}

void LevelEditor::addObstacle(string name,int x, int y, int height, int width, Color color, Terrain terrain){
    currentMap.addMapObj(new Obstacle(name,x, y, height, width,color, terrain));
}

void LevelEditor::addTerrain(string name,int x, int y, int height, int width, Color color, bool isPassible){
    currentMap.addMapObj(new Terrain(name,x, y,height, width,color,isPassible));
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

void LevelEditor::fillTerrain(Terrain *t){
    for(int x=0;x<currentMap.getWidth();x++){
        for(int y=0;y<currentMap.getHeight();y++){
            if(currentMap.getMapObjectAt(x,y)==nullptr){
                t->setX(x);
                t->setY(y);
                currentMap.addMapObj(t);
            }
        }
    }
}

void LevelEditor::save(string filename) {
    MapIO::write(currentMap, filename);
}

void LevelEditor::load(string filepath) {
    Map map(filepath);
    currentMap = map;
}

void LevelEditor::readObjects() {
    
    ifstream in("config/objects.txt");
    
    // reads the file
    string type, line;
    while(getline(in, type)) {          // first line is data type
        
        string name;
        Color color;
        int width = -1, height = -1, coordX = -1, coordY = -1;
        bool isPassable = true;
        
        while(!in.eof()) {              // ending object type declaration
            getline(in, line);
            if(line == "}=end") {
                break;
            }
            
            // checks for the type of line and assigns the value appropriately
            if (line.find("name=") != string::npos) {
                name = line.substr(5, line.length());
            } else if (line.find("width=") != string::npos) {
                width = stoi(line.substr(6, line.length()));
            } else if (line.find("height=") != string::npos) {
                height = stoi(line.substr(7, line.length()));
            } else if(line.find("color=") != string::npos) {
                
                string strColor = line.substr(6, line.length());
                int rgIndex = strColor.find(" ");
                int gbIndex = strColor.find(" ", rgIndex + 1);
                
                color.red = stoi(strColor.substr(0, rgIndex));
                color.green = stoi(strColor.substr(rgIndex, gbIndex - rgIndex));
                color.blue = stoi(strColor.substr(gbIndex, line.length() - gbIndex));
                
            } else if(type == "terrain" && line.find("isPassable=") != string::npos) {
                string strIsPassable = line.substr(11, line.length());
                if(strIsPassable == "false") {
                    isPassable = false;
                }
            }
        }
        
        // creates the relevant object
        if(type == "obstacle") {
            unique_ptr<MapObject> o(new Obstacle(name, coordX, coordY, width, height, color));
            mapObjs.push_back(move(o));
        } else if(type == "terrain") {
            unique_ptr<MapObject> t(new Terrain(name, coordX, coordY, width, height, color, isPassable));
            mapObjs.push_back(move(t));
        }
    }
}

void LevelEditor::nextSelection() {
    if(selectedIndex == mapObjs.size() - 1) {
        selectedIndex = 0;
    } else {
        selectedIndex++;
    }
}

void LevelEditor::nextColorSelection() {
    if(selectedColorIndex == 2) {
        selectedColorIndex = 0;
    } else if (selectedColorIndex < 2) {
        selectedColorIndex++;
    }
}

MapObject* LevelEditor::getCurrentSelection() {
    return mapObjs[selectedIndex].get();
}

int LevelEditor::getCurrentSelectionIndex() {
    return selectedIndex;
}

void LevelEditor::setCurrentSelection(int i) {
    this->selectedIndex = i;
}

int LevelEditor::getSelectedColorIndex() {
    return selectedColorIndex;
}

void LevelEditor::setSelectedColorIndex(int i) {
    this->selectedColorIndex = i;
}

void LevelEditor::changeRedVal(LSign sign) {
    if(sign == POS && red < 255) {
        red++;
    } else if(red > 0) {
        red--;
    }
}

void LevelEditor::changeGreenVal(LSign sign) {
    if(sign == POS && green < 255) {
        green++;
    } else if(green > 0) {
        green--;
    }
}

void LevelEditor::changeBlueVal(LSign sign) {
    if(sign == POS && blue < 255) {
        blue++;
    } else if(blue > 0) {
        blue--;
    }
}

void LevelEditor::draw() {
    currentMap.drawMap();
}
