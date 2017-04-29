//
//  Map.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Map.hpp"
#include "MapIO.hpp"

Map::Map(string filepath) {
    loadMapFromFile(filepath);
}

Map::Map(int width, int height) : width(width), height(height) {
    preferredStartCoords.push_back(Point2D(0, 0));
}

Map::~Map() {}

void Map::addPreferredStartCoord(int x, int y) {
    Point2D point(x, y);
    preferredStartCoords.push_back(point);
}

void Map::removePreferredStartCoord(int x, int y) {
    for(int i = 0; i < preferredStartCoords.size(); i++) {
        if(preferredStartCoords[i].getX() == x && preferredStartCoords[i].getY() == y) {
            preferredStartCoords.erase(preferredStartCoords.begin() + i);
        }
    }
}

bool Map::doesPreferredStartCoordExist(int x, int y) {
    for(int i = 0; i < preferredStartCoords.size(); i++) {
        if(x == preferredStartCoords[i].getX() && y == preferredStartCoords[i].getY()) {
            return true;
        }
    }
    
    return false;
}

void Map::addMapObj(MapObject *mobj) {
    unique_ptr<MapObject> mobjp(mobj);
    mapObjs.push_back(move(mobjp));
}

void Map::removeMapObjAt(int x, int y) {
    for(int i = 0; i < mapObjs.size(); i++) {
        if(mapObjs[i]->getX() == x && mapObjs[i]->getY() == y) {
            mapObjs.erase(mapObjs.begin() + i);
        }
    }
}

Point2D Map::getRandomStartCoords() const {
    random_device rnd;
    int rand_index = rnd() % preferredStartCoords.size();
    return preferredStartCoords[rand_index];
}

MapObject* Map::getMapObjectAt(int x, int y) const {
    for(int i = 0; i < mapObjs.size(); i++) {
        if(x == mapObjs[i]->getX() && y == mapObjs[i]->getY()) {
            return mapObjs[i].get();
        }
    }
    
    return nullptr;
}

Obstacle* Map::getObstacleAt(int x, int y) const {
    for(int i = 0; i < mapObjs.size(); i++) {
        if(x == mapObjs[i]->getX() && y == mapObjs[i]->getY()) {
            if(Obstacle* o = dynamic_cast<Obstacle*>(mapObjs[i].get())) {
                return o;
            }
        }
    }
    
    return nullptr;
}

Terrain* Map::getTerrainAt(int x, int y) const {
    for(int i = 0; i < mapObjs.size(); i++) {
        if(x == mapObjs[i]->getX() && y == mapObjs[i]->getY()) {
            if(Terrain* t = dynamic_cast<Terrain*>(mapObjs[i].get())) {
                return t;
            }
        }
    }
    
    return nullptr;
}

vector<Point2D> Map::getPreferredStartCoords() const {
    return preferredStartCoords;
}

int Map::getWidth() const {
    return width;
}

int Map::getHeight() const {
    return height;
}

Map& Map::operator = (Map &map) {
    this->mapObjs = move(map.mapObjs);
    this->width = map.width;
    this->height = map.height;
    this->preferredStartCoords = map.preferredStartCoords;
    return *this;
}

void Map::drawMap() {
    for(int i = 0; i < mapObjs.size(); i++) {
        mapObjs[i]->draw();
    }
}

void Map::loadMapFromFile(string filepath) {
    MapData mapData = MapIO::read(filepath);
    
    this->width = mapData.width;
    this->height = mapData.height;
    
    this->preferredStartCoords = mapData.preferredStartCoords;
    
    for(int i = 0; i < mapData.mapObjs.size(); i++) {
        mapObjs.push_back(move(mapData.mapObjs[i]));
    }
}
