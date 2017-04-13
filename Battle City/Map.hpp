//
//  Map.hpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#ifndef Map_hpp
#define Map_hpp

#include <vector>
using namespace std;

struct Point2D {
    int x;
    int y;
};

class Map {
public:
    Map(int width, int height);
    ~Map();
    
    MapObject* getObstacleAt(int x, int y);
    Terrain* getTerrainAt(int x, int y);
    
    vector<Point2D> getPreferredStartCoords() const;
    void addPreferredStartCoord(int x, int y);
    void removePreferredStartCoord(int x, int y);
    
    void addMapObj(MapObject &mobj);
    void removeMapObjAt(int x, int y);
    
private:
    vector<Point2D> preferredStartCoords;
    vector<MapObject> mapObjs;
    int width, height;
    
};

#endif /* Map_hpp */
