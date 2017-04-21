//
//  main.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include <iostream>
#include "Obstacle.hpp"
#include "Terrain.hpp"
#include "LevelEditor.hpp"
#include "Color.hpp"

#include <iostream>
using namespace std;

void   testObstacleandTerrain();
void  testLevelEditor();


int main(int argc, const char * argv[]) {
    
    cout<<"Test Obstacle and Terrain classes:"<<endl;
    testObstacleandTerrain();
    
    testLevelEditor();

    
    return 0;
}

void testObstacleandTerrain(){
    
    Color color;
    color.red = 100;
    color.green = 100;
    color.blue = 100 ;
    
    Obstacle o ("water",1,2,3,4,color);
    
    Terrain t("stand",4,3,2,1,color,false);
    
    //test set and getunderlyingTerrain()
    o.setUnderlyingTerrain(t);
    //should prints "stand"
    cout<<o.getunderlyingTerrain().getName()<<endl;
    
    //test get and setIsPassable()
    t.setIsPassable(true);
    //should prints 1
    cout<<t.getIsPassable()<<endl;
    
}

void testLevelEditor(){
    
    Map m(20, 10);
    Color color;
    color.red = 212;
    color.green = 97;
    color.blue = 123;
    
    // Add mapobjs
       Terrain t("Water", 2, 1, 3, 4, color, false);
    
    
    
    LevelEditor l(m);
    
//    l.addTerrain("stand",1,2,3,4,color,true);
//    l.addObstacle("Wall", 1, 2, 3, 4, color,t);
//    l.save();

    
    l.addPreferredStart(1, 2);
    
    
    
    
}
