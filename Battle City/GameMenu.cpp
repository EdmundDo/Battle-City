//
//  GameMenu.cpp
//  Battle City
//
//  Created by Edmund Do on 4/24/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "GameMenu.hpp"
#include "graphics.hpp"

const string GameMenu::maps[] = {"map.txt", "Custom Map"};

GameMenu::GameMenu() : currentSelection(startGame), mapSelection(0), map(new Map("map.txt")) {}

GameMenu::~GameMenu() {}

void GameMenu::nextSelection() {
    if(currentSelection == startGame) {
        currentSelection = mapEditor;
    } else if(currentSelection == mapEditor) {
        currentSelection = instructions;
    } else if (currentSelection == instructions){
        currentSelection = startGame;
    }
}

void GameMenu::nextMapSelection() {
    if(mapSelection < 1) {
        mapSelection++;
    } else {
        mapSelection = 0;
    }
}

Selection GameMenu::getCurrentSelection() {
    return currentSelection;
}

string GameMenu::getCurrentMapSelection() {
    //return maps[currentSelection];
    return "";
}

void GameMenu::setCurrentSelection(Selection s) {
    this->currentSelection = s;
}

Map* GameMenu::getMap() {
    return map.get();
}

void GameMenu::draw() {
    int tStartX = 215, tStartY = 100;
    string title = "BATTLE CITY";
    
    glColor3f(150.0/255.0, 22.0/255.0, 11.0/255.0);
    for (int i = 0; i < title.length(); i++, tStartX += 25) {
        glRasterPos2i(tStartX, tStartY);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, title[i]);
    }
    
    
    int miStartX = 300, miStartY = 200;
    string menuItem[] = {"Start Game", "Map Editor", "Instructions"};
    
    glColor3f(1, 1, 1);
    for(int i = 0; i < sizeof(menuItem) / sizeof(menuItem[0]); i++) {
        glRasterPos2i(miStartX, miStartY);
        for (int j = 0; j < menuItem[i].length(); j++) {
            if(selectionToString(currentSelection) == menuItem[i]) {
                int prevMStartY = miStartY;
                miStartY -= 13;
                miStartX = 275;
                
                glBegin(GL_TRIANGLES);
                glColor3f(1, 1, 1);
                glVertex2i(miStartX, miStartY + 15);
                glVertex2i(miStartX, miStartY - 5);
                glVertex2i(miStartX + 10, miStartY + 5);
                glEnd();
                
                miStartX = 300;
                miStartY = prevMStartY;
            }
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, menuItem[i][j]);
        }
        miStartY += 50;
    }
    
    int mStartX = 0, mStartY = 450;
    
    unsigned char mapStr[maps[mapSelection].length()];
    strcpy((char*) mapStr, maps[mapSelection].c_str());
    mStartX = (700 - glutBitmapLength(GLUT_BITMAP_HELVETICA_18, mapStr)) / 2;
    
    glRasterPos2i(mStartX, mStartY);
    for(int i = 0; i < maps[mapSelection].length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, maps[mapSelection][i]);
    }
}

string GameMenu::selectionToString(Selection s) {
    switch(s) {
        case startGame:
            return "Start Game";
        case mapEditor:
            return "Map Editor";
        case instructions:
            return "Instructions";
        default:
            return "";
    }
}
