//
//  LevelEditor.hpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#ifndef LevelEditor_hpp
#define LevelEditor_hpp

#include <stdio.h>
#include "Map.hpp"
#include "Color.hpp"
#include "Terrain.hpp"
#include "Obstacle.hpp"
#include "MapIO.hpp"

using namespace std;

class LevelEditor{
    
public:
    LevelEditor(Map m);
    
   
    
    void addObstacle(string name,int x,int y,int height, int width,Color color, Terrain terrain);
    
    void addTerrain(string name, int x,int y, int height, int width, Color color, bool isPassible);
    
    void removeMapObjAt(int x, int y);
    
    void addPreferredStart(int x, int y);
    
    void removePreferredStart(int x, int y);
    
    void fillTerrain(Terrain t);
    
    void save();
    
private:
    Map currentMap;
    
};
#endif /* LevelEditor_hpp */
