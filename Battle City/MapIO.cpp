//
//  MapIO.cpp
//  Battle City
//
//  Created by Edmund Do on 4/19/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "MapIO.hpp"
#include "Color.hpp"

Map MapIO::read() {
    
    // Creates the map
    string width, height;
    in >> width;
    in >> height;
    
    Map map(stoi(width), stoi(height));
    
    // reads the file
    string type, line;
    while(in >> type) {         // first line is object type
        
        string name;
        Color color;
        int coordX = -1, coordY = -1;
        bool isPassable = true;
        
        while(line != "}") {    // ending object type declaration
            getline(in, line);
            
            // checks for the type of line and assigns the value appropriately
            if (line.find("name=") != string::npos) {
                name = line.substr(5, line.length());
            } else if(line.find("color=") != string::npos) {
                
                string strColor = line.substr(6, line.length());
                int rgIndex = strColor.find(" ");
                int gbIndex = strColor.find(" ", rgIndex + 1);
                
                color.red = stoi(strColor.substr(0, rgIndex));
                color.green = stoi(strColor.substr(rgIndex, gbIndex - rgIndex));
                color.blue = stoi(strColor.substr(gbIndex, line.length() - gbIndex));
                
            } else if(line.find("x=") != string::npos) {
                coordX = stoi(line.substr(2, line.length()));
            } else if(line.find("y=") != string::npos) {
                coordX = stoi(line.substr(2, line.length()));
            } else if(type == "terrain" && line.find("isPassable=") != string::npos) {
                string strIsPassable = line.substr(11, line.length());
                if(strIsPassable == "false") {
                    isPassable = false;
                }
            }
        }
        
        // creates the relevant object
        if(type == "obstacle") {
            
            Obstacle o(name, color, coordX, coordY);
            map.addMapObj(o);
            
        } else if(type == "terrain") {
            
            Terrain t(name, color, coordX, coordY, isPassable);
            map.addMapObj(&t);
            
        }
    }
    
    return map;
}
