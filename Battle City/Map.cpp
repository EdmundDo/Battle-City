//
//  Map.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Map.hpp"

Map::Map(int width, int height) : width(width), height(height) {}

Map::~Map() {}

Obstacle* Map::getObstacleAt(int x, int y) {
    for(int i = 0; i < mapObjs.size(); i++) {
        if(x == mapObjs[i].getX() && y == mapObjs.getY()) {
            if(Obstacle o = dynamic_cast<Obstacle*>(mapObjs[i])) {
                return o;
            }
        }
    }
    
    return nullptr;
}

Terrain* Map::getTerrainAt(int x, int y) {
    for(int i = 0; i < mapObjs.size(); i++) {
        if(x == mapObjs[i].getX() && y == mapObjs.getY()) {
            if(Terrain t = dynamic_cast<Terrain*>(mapObjs[i])) {
                return t;
            }
        }
    }
    
    return nullptr;
}

void Map::addPreferredStartCoord(int x, int y) {
    Point2D point = {x, y};
    preferredStartCoords.push_back(point);
}

void Map::removePreferredStartCoord(int x, int y) {
    for(int i = 0; i < preferredStartCoords.size(); i++) {
        if(preferredStartCoords[i].x == x && preferredStartCoords[i].y == y) {
            preferredStartCoords.erase(preferredStartCoords.begin() + i);
        }
    }
}

void Map::addMapObj(MapObject &mobj) {
    mapObjs.push_back(&mobj);
}

void Map::removeMapObjAt(int x, int y) {
    for(int i = 0; i < mapObjs.size(); i++) {
        if(mapObjs[i].getX() == x && mapObjs[i].getY() == y) {
            mapObjs.erase(mapObjs.begin() + i);
        }
    }
}

vector<Point2D> Map::getPreferredStartCoords() const {
    return preferredStartCoords;
}
