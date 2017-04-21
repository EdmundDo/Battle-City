//
//  main.cpp
//  Battle City
//
//  Created by Yixiong Zhang on 4/3/17.
//  Copyright © 2017 Yixiong Zhang. All rights reserved.
//

#include "Tank.hpp"
#include "Entity.hpp"
#include "Projectile.hpp"
#include <iostream>
#include <vector>
#include "Color.hpp"
using namespace std;


void test_tank();
void test_projectitle();

int main() {
 
    test_tank();
    test_projectitle();
    return 0;

}

//Testing tank.

void test_tank(){
    Color color;
    color.red = 1;
    color.blue = 2;
    color.green = 3;
    vector <Entity*> entities;

    Tank t(100,1,2,3,color,false,0,entities);
    double direction = t.getDirection();
    t.rotate(EPOS);
    if(direction< t.getDirection()){
        cout<< "PASS 1" <<endl;
    }
    
    //Testing direction.
    
    direction = t.getDirection();
    t.rotate(ENEG);
    if (direction > t.getDirection()){
        cout <<"PASS 2"<<endl;
        }
    
    //Testing shoot.
    
    t.shoot();
    if (entities[0]!=nullptr){
        cout <<"PASS 3"<<endl;
    }
    
   //Testing setHealth and getHealth.
    
    t.setHealth(20);
    t.getHealth();
    if (20 == t.getHealth()) {
        cout << "PASS 4"<< endl;
    } else {

        cout << "FAIL"<<endl;
        
    }
    
    //Testing getControllerID.
    
    double controllerId = 0;
    t.getControllerId();
    if (controllerId == t.getControllerId()){
        cout<<"PASS 5"<< endl;
        
    }else{
        cout << "FAIL" <<endl;
    
    }
   

    //Testing getX.
    
    if(1 == t.getX()){
        cout <<"PASS 6"<<endl;
       
        
    }else{
        cout << "FAIL"<<endl;
        
    }
    
    //Testing getY.
    
    if(2 == t.getY()){
        cout <<"PASS 7" <<endl;
        
        
    }else{
        cout << "FAIL" <<endl;
    }
    
    //Testing setWidth and getWidth.
    t.setWidth(30);
    t.getWidth();
    if(30==t.getWidth()){
        cout <<"PASS 8"<<endl;
        
    }else{
        cout << "FAIL"<<endl;
   
    }
    
    //Testing setHeight and getHeight.
    
    t.setHeight(40);
    t.getHeight();
    if(40==t.getHeight()){
        cout << "PASS 9"<<endl;
        
    }else{
        cout << "FAIL" <<endl;
    }
    
    //Testing setColor and getColor.
    
    t.setColor(225,0,0);
    color = t.getColor();
   
    if (color.red == 225){
        cout << "PASS 10"<<endl;
        
    }else{
        cout << "FAIL"<<endl;
        
    }
    
    
}


// Testing projectile.

void test_projectitle(){
    
    Color color;
    color.red = 4;
    color.blue = 5;
    color.green = 6;
    vector <Entity*> entities;
    
    Projectile p(200,3,4,5,color,false);
    
    p.setDamage(30);

    // Testing getDamge.
    
    if (30==p.getDamage()){
        cout << "PASS 11" <<endl;
        
    }else{
        
        cout<<"Fail" << endl;
 
    }
    
    
    
    //Testing setCanPass and getCanPass.
    
    p.setCanPass(false);
    
    if (false==p.getCanPass()){
        cout << "PASS 12" << endl;
    }else{
        cout<< "Fail" << endl;
    }
    

}



    





