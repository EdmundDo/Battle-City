//
//  LevelEditor.hpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#ifndef LevelEditor_hpp
#define LevelEditor_hpp

#include "Map.hpp"
#include "Color.hpp"
#include "Terrain.hpp"
#include "MapIO.hpp"

enum LSign {NEG = -1, POS = 1};

class LevelEditor {
public:
    LevelEditor(int width, int height);
    LevelEditor(string filepath);
    
    /**
     * Requires: x < currentMap.width, y < currentMap.height
     * Modifies: currentMap
     * Effects: Adds an obstacle to currentMap
     */
    
    void addObstacle(string name,int x, int y, int height, int width);
    void addObstacle(string name,int x,int y,int height, int width, Terrain terrain);
    
    /**
     * Requires: x < currentMap.width, y < currentMap.height
     * Modifies: currentMap
     * Effects: Adds an terrain to currentMap
     */
    
    void addTerrain(string name, int x,int y, int height, int width, bool isPassible);
    
    /**
     * Requires: x < currentMap.width, y < currentMap.height
     * Modifies: currentMap
     * Effects: Removes an object to currentMap
     */
    
    void removeMapObjAt(int x, int y);
    
    /**
     * Requires: x < currentMap.width, y < currentMap.height
     * Modifies: currentMap
     * Effects: Adds a preferred start to currentMap
     */
    
    void addPreferredStart(int x, int y);
    
    /**
     * Requires: x < currentMap.width, y < currentMap.height
     * Modifies: currentMap
     * Effects: Removes a preferred start to currentMap
     */
    
    void removePreferredStart(int x, int y);
    
    /**
     * Requires: nothing
     * Modifies: currentMap
     * Effects: Fills the empty slots with the specified terrain
     */
    
    void fillTerrain(Terrain *t);
    
    /**
     * Requires: filename.length > 0
     * Modifies: nothing
     * Effects: Saves the map
     */
    
    void save(string filename);
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: loads the map from a txt
     */
    
    void load(string filepath);
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: Reads the possible objects from a txt
     */
    
    void readObjects();
    
    void nextSelection();
    void nextColorSelection();
    
    void toggleMode();
    bool getMode();
    
    MapObject* getCurrentSelection();
    Color getColor();
    
    void incrementSelectedColor();
    void decrementSelectedColor();
    
    void changeRedVal(LSign sign);
    void changeGreenVal(LSign sign);
    void changeBlueVal(LSign sign);
    
    void draw();
    
private:
    Color color;
    Map currentMap;
    vector<unique_ptr<MapObject>> mapObjs;
    
    int selectedIndex, selectedColorIndex;
    bool mode;
    
};

#endif /* LevelEditor_hpp */
