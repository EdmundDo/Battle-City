//
//  Map.hpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include "Point2D.hpp"

#include <vector>
#include <random>
using namespace std;

class Map {
public:
    Map(string filepath);
    Map(int width, int height);
    ~Map();
    
    /**
     * Requires: x < width and y < height
     * Modifies: preferredStartLocations
     * Effects: Adds a start coordinate to the map
     */
    
    void addPreferredStartCoord(int x, int y);
    
    /**
     * Requires: x < width and y < height
     * Modifies: preferredStartLocations
     * Effects: Removes a start coordinate from the map
     */
    
    void removePreferredStartCoord(int x, int y);
    
    /**
     * Requires: mobj.getX() < width and mobj.getY() < height
     * Modifies: mapObjs
     * Effects: Adds an object to the map
     */
    
    void addMapObj(MapObject &mobj);
    
    /**
     * Requires: x < width and y < height
     * Modifies: mapObjs
     * Effects: Removes an object to the map
     */
    
    void removeMapObjAt(int x, int y);
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: gets a random start coordinate
     */
    
    Point2D getRandomStartCoords() const;
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: getters for objects in the Map
     */
    
    MapObject* getMapObjectAt(int x, int y) const;
    Obstacle* getObstacleAt(int x, int y) const;
    Terrain* getTerrainAt(int x, int y) const;
    
private:
    vector<Point2D> preferredStartCoords;
    vector<MapObject> mapObjs;
    int width, height;
    
    void loadMapFromFile(string filepath);
    
};

#endif /* Map_hpp */
