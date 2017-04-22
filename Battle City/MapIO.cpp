//
//  MapIO.cpp
//  Battle City
//
//  Created by Edmund Do on 4/19/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "MapIO.hpp"
#include "Color.hpp"
#include "Terrain.hpp"
#include "Obstacle.hpp"

MapIO::MapIO() {}

MapIO::~MapIO() {}

void MapIO::write(Map &map, string filepath) {
    
    ofstream out(filepath);
    
    out << map.getWidth() << endl;
    out << map.getHeight() << endl;
    
    vector<Point2D> startCoords = map.getPreferredStartCoords();
    for(int i = 0; i < startCoords.size(); i++) {
        Point2D startCoord = startCoords[i];
        out << "preferredStart" << endl;
        out << "{" << endl;
        out << "x=" << startCoord.getX() << endl;
        out << "y=" << startCoord.getY() << endl;
        out << "}=end" << endl;
    }
    
    for(int x = 0; x < map.getWidth(); x++) {
        for(int y = 0; y < map.getHeight(); y++) {
            
            if(Obstacle *o = map.getObstacleAt(x,y)) {
                cout << "made it 1" << endl;
                out << "obstacle"<<endl;
                out << "{" <<endl;
                out << "name=" << o->getName() << endl;
                out << "width=" << o->getWidth() << endl;
                out << "height=" << o->getHeight() << endl;
                out << "color=" << o->getColor().red << " " << o->getColor().green << " " << o->getColor().blue << endl;
                out << "x=" << o->getCoordX() << endl;
                out << "y=" << o->getCoordY() << endl;
                out << "}=end" << endl;

            } else if(Terrain *t = map.getTerrainAt(x, y)) {
                cout << "made it 2" << endl;
                out << "terrain"<<endl;
                out << "{" <<endl;
                out << "name=" << t->getName() << endl;
                out << "width=" << t->getWidth() << endl;
                out << "height=" << t->getHeight() << endl;
                out << "color=" << t->getColor().red << " " << t->getColor().green << " " << t->getColor().blue << endl;
                out << "x=" << t->getCoordX() << endl;
                out << "y=" << t->getCoordY() << endl;
                out << "isPassable=" << t->getIsPassable() << endl;
                out << "}=end" << endl;
                
            }
        }
    }
}

MapData MapIO::read(string filepath) {
    
    ifstream in(filepath);
    
    // Creates the map
    string width, height;
    getline(in, width);
    getline(in, height);
    
    MapData mapData;
    mapData.width = stoi(width);
    mapData.height = stoi(height);
    
    // reads the file
    string type, line;
    while(getline(in, type)) {          // first line is data type
        
        string name;
        Color color;
        int width = -1, height = -1, coordX = -1, coordY = -1;
        bool isPassable = true;
        
        while(!in.eof()) {              // ending object type declaration
            getline(in, line);
            if(line == "}=end") {
                break;
            }
            
            // checks for the type of line and assigns the value appropriately
            if (line.find("name=") != string::npos) {
                name = line.substr(5, line.length());
            } else if (line.find("width=") != string::npos) {
                width = stoi(line.substr(6, line.length()));
            } else if (line.find("height=") != string::npos) {
                height = stoi(line.substr(7, line.length()));
            }else if(line.find("color=") != string::npos) {
                
                string strColor = line.substr(6, line.length());
                int rgIndex = strColor.find(" ");
                int gbIndex = strColor.find(" ", rgIndex + 1);
                
                color.red = stoi(strColor.substr(0, rgIndex));
                color.green = stoi(strColor.substr(rgIndex, gbIndex - rgIndex));
                color.blue = stoi(strColor.substr(gbIndex, line.length() - gbIndex));
                
            } else if(line.find("x=") != string::npos) {
                coordX = stoi(line.substr(2, line.length()));
            } else if(line.find("y=") != string::npos) {
                coordY = stoi(line.substr(2, line.length()));
            } else if(type == "terrain" && line.find("isPassable=") != string::npos) {
                string strIsPassable = line.substr(11, line.length());
                if(strIsPassable == "false") {
                    isPassable = false;
                }
            }
        }
        
        // creates the relevant object
        if(type == "obstacle") {
            std::unique_ptr<MapObject> o(new Obstacle(name, coordX, coordY, width, height, color));
            mapData.mapObjs.push_back(std::move(o));
        } else if(type == "terrain") {
            std::unique_ptr<MapObject> t(new Terrain(name, coordX, coordY, width, height, color, isPassable));
            mapData.mapObjs.push_back(std::move(t));
        } else if (type == "preferredStart") {
            Point2D p(coordX, coordY);
            mapData.preferredStartCoords.push_back(p);
        }
    }
    
    return mapData;
}
