//
//  Terrain.hpp
//  CS120
//
//  Created by Shaw on 4/14/17.
//  Copyright © 2017 Shaw. All rights reserved.
//

#ifndef Terrain_hpp
#define Terrain_hpp

#include "MapObject.hpp"

class Terrain : public MapObject{
    
public:
    
    Terrain(int x, int y, bool isPassable);
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: getters and setters
     */
    
    bool getIsPassable() const;
    void setIsPassable(bool a);
    
    virtual void draw() override;
    
private:
    bool isPassable;
};

#endif /* Terrain_hpp */
