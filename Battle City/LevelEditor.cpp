//
//  LevelEditor.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Obstacle.hpp"
#include "LevelEditor.hpp"

LevelEditor::LevelEditor(int width, int height) : currentMap(width, height), selectedIndex(0), selectedColorIndex(0), mode(false) {
    
    readObjects();
    
    color.red = mapObjs[0]->getColor().red;
    color.green = mapObjs[0]->getColor().green;
    color.blue = mapObjs[0]->getColor().blue;
}

LevelEditor::LevelEditor(string filepath) : currentMap(filepath), selectedIndex(0), selectedColorIndex(0), mode(false) {
    readObjects();
    
    color.red = mapObjs[0]->getColor().red;
    color.green = mapObjs[0]->getColor().green;
    color.blue = mapObjs[0]->getColor().blue;
}

void LevelEditor::addObstacle(string name, int x, int y, int height, int width) {
    MapObject *mobj = currentMap.getMapObjectAt(x, y);
    if(mobj == nullptr) {
        currentMap.addMapObj(new Obstacle(name, x, y, height, width, color));
    } else {
        if(Terrain* tobj = dynamic_cast<Terrain*>(mobj)) {
            currentMap.removeMapObjAt(x, y);
            currentMap.addMapObj(new Obstacle(name, x, y, height, width, color, *tobj));
        }
    }
}

void LevelEditor::addTerrain(string name,int x, int y, int height, int width, bool isPassable) {
    if(currentMap.getMapObjectAt(x, y) == nullptr) {
        currentMap.addMapObj(new Terrain(name, x, y, height, width, color, isPassable));
    }
}

void LevelEditor::removeMapObjAt(int x, int y){
    currentMap.removeMapObjAt(x,y);
}

void LevelEditor::addPreferredStart(int x, int y){
    MapObject *mobj = currentMap.getMapObjectAt(x, y);
    if(mobj == nullptr || mobj->getIsPassable()) {
        currentMap.addPreferredStartCoord(x,y);
    }
}

void LevelEditor::removePreferredStart(int x, int y){
    currentMap.removePreferredStartCoord(x,y);
}

void LevelEditor::fillTerrain(Terrain *t){
    for(int x = 0; x < currentMap.getWidth() * 10; x += 10){
        for(int y = 0; y < currentMap.getHeight() * 10; y += 10){
            if(currentMap.getMapObjectAt(x,y) == nullptr){
                currentMap.addMapObj(new Terrain(t->getName(), x, y, t->getWidth(), t->getHeight(), color, t->getIsPassable()));
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

void LevelEditor::toggleMode() {
    if(!mode) {
        mode = true;
    } else {
        mode = false;
    }
}

bool LevelEditor::getMode() {
    return mode;
}

void LevelEditor::nextSelection() {
    mapObjs[selectedIndex]->setColor(color);
    if(selectedIndex < mapObjs.size() - 1) {
        selectedIndex++;
    } else {
        selectedIndex = 0;
    }
    color = getCurrentSelection()->getColor();
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

Color LevelEditor::getColor() {
    return color;
}

void LevelEditor::incrementSelectedColor() {
    if(selectedColorIndex == 0) {
        changeRedVal(POS);
    } else if(selectedColorIndex == 1) {
        changeGreenVal(POS);
    } else if(selectedColorIndex == 2) {
        changeBlueVal(POS);
    }
}

void LevelEditor::decrementSelectedColor() {
    if(selectedColorIndex == 0) {
        changeRedVal(NEG);
    } else if(selectedColorIndex == 1) {
        changeGreenVal(NEG);
    } else if(selectedColorIndex == 2) {
        changeBlueVal(NEG);
    }
}

void LevelEditor::changeRedVal(LSign sign) {
    if(sign == POS && color.red < 255) {
        color.red++;
    } else if(sign == NEG && color.red > 0) {
        color.red--;
    }
}

void LevelEditor::changeGreenVal(LSign sign) {
    if(sign == POS && color.green < 255) {
        color.green++;
    } else if(sign == NEG && color.green > 0) {
        color.green--;
    }
}

void LevelEditor::changeBlueVal(LSign sign) {
    if(sign == POS && color.blue < 255) {
        color.blue++;
    } else if(sign == NEG && color.blue > 0) {
        color.blue--;
    }
}

void LevelEditor::draw() {
    currentMap.drawMap(true);
    
    MapObject* mobj = getCurrentSelection();
    int startX = 100, startY = 510;
    
    if(!mode) {
        // Prints name
        glColor3f(1, 1, 1);
        glRasterPos2i(startX, startY);
        for(int i = 0; i < mobj->getName().length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, mobj->getName()[i]);
        }
        
        // Prints red val
        glRasterPos2i(startX + 100, startY);
        for(int i = 0; i < 5; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, "Red: "[i]);
        }
        
        string red = to_string(color.red);
        for(int i = 0; i < red.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, red[i]);
        }
        
        // Prints green val
        glRasterPos2i(startX + 200, startY);
        for(int i = 0; i < 7; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, "Green: "[i]);
        }
        
        string green = to_string(color.green);
        for(int i = 0; i < green.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, green[i]);
        }
        
        // Prints blue val
        glRasterPos2i(startX + 300, startY);
        for(int i = 0; i < 6; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, "Blue: "[i]);
        }
        
        string blue = to_string(color.blue);
        for(int i = 0; i < blue.length(); i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, blue[i]);
        }
    } else {
        glColor3f(1, 1, 1);
        glRasterPos2i(startX, startY);
        for(int i = 0; i < 32; i++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, "Preferred Start Coordinate Mode"[i]);
        }
    }
}
