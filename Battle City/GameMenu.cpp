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

GameMenu::GameMenu() : currentSelection(GMStartGame), mapSelection(0) {}

GameMenu::~GameMenu() {}

void GameMenu::nextSelection() {
    if(currentSelection == GMStartGame) {
        currentSelection = GMMapEditor;
    } else if(currentSelection == GMMapEditor) {
        currentSelection = GMInstructions;
    } else if (currentSelection == GMInstructions){
        currentSelection = GMExit;
    } else if (currentSelection == GMExit){
        currentSelection = GMStartGame;
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
    return maps[mapSelection];
}

void GameMenu::setCurrentSelection(Selection s) {
    this->currentSelection = s;
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
    string menuItem[] = {"Start Game", "Map Editor", "Instructions", "Exit"};
    
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
    
    string selectionMessage = "Select a map:";
    unsigned char selectStr[selectionMessage.length()];
    strcpy((char*) selectStr, selectionMessage.c_str());
    mStartX = (700 - glutBitmapLength(GLUT_BITMAP_HELVETICA_18, selectStr)) / 2;
    
    glRasterPos2i(mStartX, mStartY - 25);
    for(int i = 0; i < selectionMessage.length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, selectionMessage[i]);
    }
    
    glBegin(GL_TRIANGLES);
    glColor3ub(255, 255, 255);
    glVertex2i(275, 435);
    glVertex2i(265, 445);
    glVertex2i(275, 455);
    glEnd();
    
    unsigned char mapStr[maps[mapSelection].length()];
    strcpy((char*) mapStr, maps[mapSelection].c_str());
    mStartX = (700 - glutBitmapLength(GLUT_BITMAP_HELVETICA_18, mapStr)) / 2;
    
    glRasterPos2i(mStartX, mStartY);
    for(int i = 0; i < maps[mapSelection].length(); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, maps[mapSelection][i]);
    }
    
    glBegin(GL_TRIANGLES);
    glColor3ub(255, 255, 255);
    glVertex2i(425, 435);
    glVertex2i(435, 445);
    glVertex2i(425, 455);
    glEnd();
}

string GameMenu::selectionToString(Selection s) {
    switch(s) {
        case GMStartGame:
            return "Start Game";
        case GMMapEditor:
            return "Map Editor";
        case GMInstructions:
            return "Instructions";
        case GMExit:
            return "Exit";
        default:
            return "";
    }
}
