//
//  GameMenu.cpp
//  Battle City
//
//  Created by Edmund Do on 4/24/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "GameMenu.hpp"
#include "graphics.hpp"

GameMenu::GameMenu() : currentSelection(startGame), map(new Map("map.txt")) {}

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

Selection GameMenu::getCurrentSelection() {
    return currentSelection;
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
    
    
    int mStartX = 300, mStartY = 200;
    string menuItem[] = {"Start Game", "Map Editor", "Instructions"};
    
    glColor3f(1, 1, 1);
    for(int i = 0; i < sizeof(menuItem) / sizeof(menuItem[0]); i++) {
        glRasterPos2i(mStartX, mStartY);
        for (int j = 0; j < menuItem[i].length(); j++) {
            if(selectionToString(currentSelection) == menuItem[i]) {
                int prevMStartY = mStartY;
                mStartY -= 13;
                mStartX = 275;
                
                glBegin(GL_TRIANGLES);
                glColor3f(1, 1, 1);
                glVertex2i(mStartX, mStartY + 15);
                glVertex2i(mStartX, mStartY - 5);
                glVertex2i(mStartX + 10, mStartY + 5);
                glEnd();
                
                mStartX = 300;
                mStartY = prevMStartY;
            }
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, menuItem[i][j]);
        }
        mStartY += 50;
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
