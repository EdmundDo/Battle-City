//
//  GameWindow.cpp
//  Battle City
//
//  Created by Edmund Do on 4/23/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "GameWindow.hpp"
#include "Game.hpp"

#include <string>
using namespace std;

// GL params
GLdouble width, height;
int wd;

// Game params
int mouseX, mouseY;
enum GameState {menu, lvlEditor, gameplay, gameOver};
unique_ptr<Game> game;
GameState state;

void init() {
    width = 700;
    height = 500;
    mouseX = mouseY = -1;
    state = menu;
}

void initGL() {
    // Black and opaque
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(1, 1, 1);
}

// display helpers

void displayMenu() {
    int tStartX = 215, tStartY = 100;
    string title = "BATTLE CITY";
    
    glColor3f(150.0/255.0, 22.0/255.0, 11.0/255.0);
    for (int i = 0; i < title.length(); i++, tStartX += 25) {
        glRasterPos2i(tStartX, tStartY);
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, title[i]);
    }
    
    
    int mStartX = 300, mStartY = 200;
    string menuItem[] = {"Start Game", "Map Editor", "Credits"};
    
    glColor3f(1, 1, 1);
    for(int i = 0; i < sizeof(menuItem) / sizeof(menuItem[0]); i++) {
        glRasterPos2i(mStartX, mStartY);
        for (int j = 0; j < menuItem[i].length(); j++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, menuItem[i][j]);
        }
        mStartY += 50;
    }
}

/**
 * Draws the map with its objects and their respective colors
 */

void displayMap() {
    
}

/**
 * Displays a n x m grid representing the game map. Currently selected 
 * tile is shown on the bottom right.
 */

void displayLevelEditor() {
    // do something
    
}

/**
 * Draws the tanks, projectils, and map. Reflective of game changes.
 */

void displayGameplay() {
    // do something
    
}

/**
 * Draws the game over menu. "Click to try again".
 */

void displayGameOver() {
    // Draw strings
    string message = "Game Over";
    // set color to lime green
    glColor3f(50/255.0, 205/255.0, 50/255.0);
    glRasterPos2i(300, 250);
    for (int i = 0; i < message.length(); ++i) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, message[i]);
    }
}

void display() {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, height, 0.0, -1.f, 1.f);
    
    // Clear the color buffer with current clearing color
    glClear(GL_COLOR_BUFFER_BIT);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
    // DRAW THINGS
    
    switch(state) {
        case menu:
            displayMenu();
            break;
        case lvlEditor:
            displayLevelEditor();
            break;
        case gameplay:
            displayGameplay();
            break;
        case gameOver:
            displayGameOver();
            break;
    }
    
    // END DRAW THINGS
    
    glFlush();
}

// http://www.theasciicode.com.ar/ascii-control-characters/escape-ascii-code-27.html
void kbd(unsigned char key, int x, int y) {
    // escape
    if (key == 27) {
        glutDestroyWindow(wd);
        exit(0);
    }
    
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    // do something
    
    glutPostRedisplay();
}

void cursor(int x, int y) {
    // do something
    
    glutPostRedisplay();
}

// button will be GLUT_LEFT_BUTTON or GLUT_RIGHT_BUTTON
// state will be GLUT_UP or GLUT_DOWN
void mouse(int button, int state, int x, int y) {
    // do something
    
    glutPostRedisplay();
}

void timer(int extra) {
    // do something
}

int main(int argc, char** argv) {
    
    init();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    glutInitWindowSize((int)width, (int)height);
    
    // Position the window's initial top-left corner
    glutInitWindowPosition(500, 500);
    wd = glutCreateWindow("Battle City");
    
    // Register callback handler for window re-paint event
    glutDisplayFunc(display);
    
    initGL();
    // register keyboard press event processing function
    glutKeyboardFunc(kbd);
    
    // register special event: function keys, arrows, etc.
    glutSpecialFunc(kbdS);
    
    // handles mouse movement
    glutPassiveMotionFunc(cursor);
    
    // handles mouse click
    glutMouseFunc(mouse);
    
    // handles timer
    glutTimerFunc(0, timer, 0);
    
    // Enter the event-processing loop
    glutMainLoop();
    return 0;
}

