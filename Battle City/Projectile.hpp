//
//  Projectile.hpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#ifndef Projectile_hpp
#define Projectile_hpp
#include "Entity.hpp"
#include "Tank.hpp"


class Projectile : public Entity{
  
public:
    Projectile(double damage, double x, double y, double direction, Color color, bool canPass);
    ~Projectile();


    void setDamage(double d);
    double getDamage();
    
    virtual void draw() override;
    
private:
    double damage;
    
  
    
};

    
    























#endif /* Projectile_hpp */
