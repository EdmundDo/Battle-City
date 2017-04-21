//
//  MapIO.cpp
//  Battle City
//
//  Created by Edmund Do on 4/19/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "MapIO.hpp"

void MapIO::write(Map &map){
    for (int x=0; x< map.getWidth(),x++){
        
        out << "30 "<<endl;
        
        for(int y=0; y<map.getHeight(),y++){
            
            out << "10"<<endl;
        
    
            Obstacle *o = map.getObstacleAt(x,y);
            if (o!= nullptr){
                out << "obstacle"<<endl;
                out << "{" <<endl;
                out << "name=" << o->getName() <<endl;
                out << "color=" << o->getColor()<< endl;
                out << "x=" <<o->getX()<<endl;
                out << "Y=" <<o->getY()<<endl;
                out << "}" <<endl;
                
            }
        
        
            Terrain * t = map.getTerrainAt(x, y);
            
            if (t!= nullptr){
                
                out << "terrain"<<endl;
                out << "{" <<endl;
                out << "name=" << t-o->getName() <<endl;
                out << "color=" << t->getColor() <<endl;
                out << "x=" <<t->getX()<<endl;
                out << "y=" <<t->getY()<<endl;
                out << "isPassable="<<t->getIsPassable()<<endl;
                out << "}" <<endl;
            }
           
            
        }
       
        
    }
    
    
    
}
