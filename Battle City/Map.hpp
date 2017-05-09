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
#include "MapObject.hpp"
#include "Obstacle.hpp"
#include "Terrain.hpp"

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
     * Requires: x < width and y < height
     * Modifies: nothing
     * Effects: Sees if a preferred start coord exists
     */
    
    bool doesPreferredStartCoordExist(int x, int y);
    
    /**
     * Requires: mobj.getX() and mobj.getY()
     * Modifies: mapObjs
     * Effects: Adds an object to the map
     */
    
    void addMapObj(MapObject *mobj);
    
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
     * Effects: getters
     */
    
    MapObject* getMapObjectAt(int x, int y) const;
    MapObject* getMapObjectGridAt(int x, int y) const;
    Obstacle* getObstacleAt(int x, int y) const;
    Obstacle* getObstacleGridAt(int x, int y) const;
    Terrain* getTerrainAt(int x, int y) const;
    Terrain* getTerrainGridAt(int x, int y) const;
    vector<Point2D> getPreferredStartCoords() const;
    
    int getWidth() const;
    int getHeight() const;
    
    // Overloaded operators
    Map& operator= (Map &map);
    
    void drawMap(bool showPreferredStartCoords = false);
    
private:
    vector<Point2D> preferredStartCoords;
    vector<unique_ptr<MapObject>> mapObjs;
    int width, height;
    
    bool loadMapFromFile(string filepath);
    
};

#endif /* Map_hpp */
