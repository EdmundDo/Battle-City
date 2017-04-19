//
//  MapIO.hpp
//  Battle City
//
//  Created by Edmund Do on 4/19/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#ifndef MapIO_hpp
#define MapIO_hpp

#include "Map.hpp"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class MapIO {
public:
    MapIO();
    ~MapIO();
    
    /**
     * Requires: filepath exists
     * Modifies: filepath
     * Effects: getters and setters
     */
    
    void setFilePath(string filepath);
    string getFilePath() const;
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: writes the mapbojects of the map into a file
     */
    
    void write(Map &map);
    
    /**
     * Requires: filepath exists
     * Modifies: nothing
     * Effects: reads the mapobjects of the Map into a new Map
     */
    
    Map read();
    
private:
    string filepath;
    ofstream out;
    ifstream in;
};

#endif /* MapIO_hpp */
