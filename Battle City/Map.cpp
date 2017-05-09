//
//  Map.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "Map.hpp"
#include "MapIO.hpp"
#include "graphics.hpp"

Map::Map(string filepath) {
    if(!loadMapFromFile(filepath)) {
        throw std::runtime_error("Error loading file.");
    }
}

Map::Map(int width, int height) : width(width), height(height) {}

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
    unique_ptr<MapObject> mobjPtr(mobj);
    mapObjs.push_back(move(mobjPtr));
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
    if(!preferredStartCoords.empty()) {
        int rand_index = rnd() % preferredStartCoords.size();
        return preferredStartCoords[rand_index];
    } else {
        int randX = rnd() % width * 10;
        int randY = rnd() % height * 10;
        return Point2D(randX, randY);
    }
}

MapObject* Map::getMapObjectAt(int x, int y) const {
    for(int i = 0; i < mapObjs.size(); i++) {
        if(x == mapObjs[i]->getX() && y == mapObjs[i]->getY()) {
            return mapObjs[i].get();
        }
    }
    
    return nullptr;
}

MapObject* Map::getMapObjectGridAt(int x, int y) const {
    for(int i = 0; i < mapObjs.size(); i++) {
        if(x == mapObjs[i]->getGridX() && y == mapObjs[i]->getGridY()) {
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

Obstacle* Map::getObstacleGridAt(int x, int y) const {
    for(int i = 0; i < mapObjs.size(); i++) {
        MapObject *mobj = mapObjs[i].get();
        if(x == mapObjs[i]->getGridX() && y == mapObjs[i]->getGridY()) {
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

Terrain* Map::getTerrainGridAt(int x, int y) const {
    for(int i = 0; i < mapObjs.size(); i++) {
        if(x == mapObjs[i]->getGridX() && y == mapObjs[i]->getGridY()) {
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

void Map::drawMap(bool showPreferredStartCoords) {
    for(int i = 0; i < mapObjs.size(); i++) {
        mapObjs[i]->draw();
    }
    
    if(showPreferredStartCoords) {
        for(int i = 0; i < preferredStartCoords.size(); i++) {
            int x = preferredStartCoords[i].getX(), y = preferredStartCoords[i].getY();
            glColor3ub(0, 150, 150);
            glBegin(GL_QUADS);
            glVertex2i(x, y);
            glVertex2i(x + 10, y);
            glVertex2i(x + 10, y + 10);
            glVertex2i(x, y + 10);
            glEnd();
        }
    }
}

bool Map::loadMapFromFile(string filepath) {
    MapData mapData = MapIO::read(filepath);
    
    if(mapData.success) {
        this->width = mapData.width;
        this->height = mapData.height;
        
        this->preferredStartCoords = mapData.preferredStartCoords;
        
        for(int i = 0; i < mapData.mapObjs.size(); i++) {
            mapObjs.push_back(move(mapData.mapObjs[i]));
        }
    } else {
        return false;
    }
    
    return true;
}
