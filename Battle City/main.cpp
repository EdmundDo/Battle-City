//
//  main.cpp
//  Battle City
//
//  Created by Edmund Do on 4/3/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
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
    cout << "hello world" << endl;
    test_tank();
    test_projectitle();
    
    
    
    
    
    return 0;


}

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
        cout<< "PASS1" <<endl;
    }
    
    direction = t.getDirection();
    t.rotate(ENEG);
    if (direction > t.getDirection()){
        cout <<"PASS2"<<endl;
        }
    
    
    t.shoot();
    if (entities[0]!=nullptr){
        cout <<"PASS3"<<endl;
    }
    
   
    t.setHealth(20);
    t.getHealth();
    if (20 == t.getHealth()) {
        cout << "PASS4"<< endl;
    } else {

        cout << "FAIL"<<endl;
        
    }
    
    double controllerId = 0;
    t.getControllerId();
    if (controllerId == t.getControllerId()){
        cout<<"PASS5"<< endl;
        
    }else{
        cout << "FAIL" <<endl;
    
    }
    
}



void test_projectitle(){
    
    Color color;
    color.red = 4;
    color.blue = 5;
    color.green = 6;
    vector <Entity*> entities;
    
    Projectile p(200,3,4,5,color,false);
    
    p.setDamage(30);

    
    if (30==p.getDamage()){
        cout << "PASS6" <<endl;
        
    }else{
        
        cout<<"Fail" << endl;
 
    }
    
    
    p.setCanPass(false);
    
    if (false==p.getCanPass()){
        cout << "PASS7" << endl;
    }else{
        cout<< "Fail" << endl;
    }
    
    
    
}



