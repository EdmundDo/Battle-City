//
//  GameWindow.cpp
//  Battle City
//
//  Created by Edmund Do on 4/23/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#include "GameWindow.hpp"
#include "Game.hpp"
#include "LevelEditor.hpp"
#include "GameMenu.hpp"
#include "Obstacle.hpp"
#include "Terrain.hpp"

#include <string>
#include <iostream>
using namespace std;

// GL params
static GLdouble width, height;
int wd;

// Game params
int mouseX, mouseY;

enum GameState {menu, lvlEditor, gameplay, gameOver, instruction, gameExit};

enum Overlay {none, textField};
GameState gstate;
Overlay overlay = none;


unique_ptr<Game> game;
unique_ptr<LevelEditor> editor;
unique_ptr<GameMenu> gameMenu(new GameMenu());

string query = "";
string input = "";

void* font = GLUT_BITMAP_HELVETICA_18;

void init() {
    width = 700;
    height = 500;
    mouseX = mouseY = -1;
    gstate = menu;
}

void initGL() {
    // Black and opaque
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(1, 1, 1);
}

// display helpers

void displayMenu() {
    gameMenu->draw();
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
    editor->draw();
}

/**
 * Draws the tanks, projectils, and map. Reflective of game changes.
 */

void displayGameplay() {
    // do something
    game->draw();
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
        glutBitmapCharacter(font, message[i]);
    }
}






void displayTextField() {
    unsigned char inputc[query.length()];
    strcpy((char*) inputc, query.c_str());
    
    glColor3f(1, 1, 1);
    int x = (width - glutBitmapLength(font, inputc)) / 2;
    glRasterPos2i(x, height / 2 - 10);
    for (int i = 0; i < query.length(); ++i) {
        glutBitmapCharacter(font, query[i]);
    }
    
    if(input != "") {
        unsigned char inputci[input.length()];
        strcpy((char*) inputci, input.c_str());
        
        x = (width - glutBitmapLength(font, inputci)) / 2;
        glRasterPos2i(x, height / 2 + 10);
        
        for (int i = 0; i < input.length(); ++i) {
            glutBitmapCharacter(font, input[i]);
        }
    }
}


void displayInstruction(){
    //set color to
    
    // Draw strings
    string message = "Game Instructions";
    // set color to lime green
    glColor3f(50/255.0, 205/255.0, 50/255.0);
    glRasterPos2i(250, 50);
    for (int i = 0; i < message.length(); ++i) {
        glutBitmapCharacter(font, message[i]);
    }

    int startX = 100; int startY= 100;
    string messages[] = {"Player 1", "W - Move forward", "S - Move backward", "A - Move left", "D - Move right", "Space - Shoot" };
    
    glColor3f(0, 1, 1);
    for(int i = 0; i < sizeof(messages) / sizeof(messages[0]); i++) {
        glRasterPos2i(startX, startY);
        for(int j = 0; j < messages[i].length(); j++) {
            glutBitmapCharacter(font, messages[i][j]);
        }
        startY += 50;
    }
    
    int startX2 = 400; int startY2= 100;
    string messages2[] = {"Player 2", "I - Move forward", "K - Move backward", "J - Move left", "L - Move right","; - Shoot" };
    
    glColor3f(1, 1, 0);
    for(int i = 0; i < sizeof(messages2) / sizeof(messages2[0]); i++) {
        glRasterPos2i(startX2, startY2);
        for(int j = 0; j < messages2[i].length(); j++) {
            glutBitmapCharacter(font, messages2[i][j]);
        }
        startY2 += 50;
    }
}

void displayExit(){
    string message = "Game Exit";
    glColor3f(255, 0, 102);
    glRasterPos2i(300, 250);
    for (int i = 0; i < message.length(); ++i) {
        glutBitmapCharacter(font, message[i]);
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
    
    switch(gstate) {
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
        case instruction:
            displayInstruction();
            break;
        case gameExit:
            displayExit();
        default:
            break;
    }
    
    switch(overlay) {
        case textField:
            displayTextField();
            break;
        default:

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
    
    if(overlay == none) {
        switch (gstate) {
            case menu:
                switch(key) {
                    case 'w':
                        gameMenu->nextSelection();
                        break;
                    case 'a':
                        gameMenu->nextSelection();
                        break;
                    case 'd':
                        gameMenu->nextSelection();
                        break;
                    case 's':
                        gameMenu->nextSelection();
                        break;
                    case 'q':
                        break;
                    case 13:
                        switch(gameMenu->getCurrentSelection()) {
                            case GMStartGame:
                            {
                                game.reset(new Game(*gameMenu->getMap()));
                                gstate = gameplay;
                                
                                TankKeyBindings kb1 = {'a','d','w','s',' '};
                                Color color1 = {1,0,0};
                                game->createPlayerTank(kb1,color1);
                                
                                TankKeyBindings kb2 = {'j','l','i','k',';'};
                                Color color2 = {0,0,1};
                                game->createPlayerTank(kb2,color2);
                                
                                break;
                            }
                            case GMMapEditor:
                                editor.reset(new LevelEditor(20, 20));
                                gstate = lvlEditor;
                                break;
                            case GMInstructions:
                                gstate = instruction;
                                break;
                                
                            case GMExit:
                                gstate = gameExit;
                                break;
                        }
                        break;
                    default:
                        break;
                }
                break;
                        
            case lvlEditor:
                switch (key) {
                    case 'w':
                        editor->nextSelection();
                        break;
                    case 'q':
                        overlay = textField;
                        query = "Enter save file name: ";
                        break;
                    default:
                        break;
                }
                break;
                
            case gameplay:
                switch(key) {
                    case 'w':
                        game->handleKey('w');
                        break;
                    case 'a':
                        game->handleKey('a');
                        break;
                    case 'd':
                        game->handleKey('d');
                        break;
                    case 's':
                        game->handleKey('s');
                        break;
                    case 'i':
                        game->handleKey('i');
                        break;
                    case 'j':
                        game->handleKey('j');
                        break;
                    case 'l':
                        game->handleKey('l');
                        break;
                    case 'k':
                        game->handleKey('k');
                        break;
                    case ' ':
                        game->handleKey(' ');
                        break;
                    case 'q':
                        gstate = menu;
                        break;
                    default:
                        break;
                }
                break;
            case instruction:
                switch (key) {
                    case 'q':
                        // do something
                        gstate = menu;
                        break;
                    default:
                        break;
                }
                break;
                
            default:
                break;

        }
    } else {
        switch(overlay) {
            case textField:
                switch(key) {
                    case 13:
                        switch(gstate) {
                            case lvlEditor:
                                editor->save(input);
                                gstate = menu;
                            default:
                                break;
                        }
                        
                        input = "";
                        query = "";
                        overlay = none;
                    default:
                        input += key;
                        break;
                }
                break;
            default:
                break;
        }
    }
    
    glutPostRedisplay();
}

void kbdup(unsigned char key, int x, int y) {
    
    switch(gstate) {
        case gameplay:
            switch(key) {
                case 'w':
                    game->handleKey('w');
                    break;
                case 's':
                    game->handleKey('s');
                    break;
                case 'i':
                    game->handleKey('i');
                    break;
                case 'k':
                    game->handleKey('k');
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
    
    glutPostRedisplay();
}

void kbdS(int key, int x, int y) {
    // do something
    
    switch(gstate) {
        case lvlEditor:
            switch (key) {
                case GLUT_KEY_UP:
                    editor->incrementSelectedColor();
                    break;
                case GLUT_KEY_DOWN:
                    editor->decrementSelectedColor();
                    break;
                case GLUT_KEY_RIGHT:
                    editor->nextColorSelection();
                    break;
                case GLUT_KEY_LEFT:
                    editor->nextColorSelection();
                    break;
                default:
                    break;
            }
            break;
    }
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
    if(overlay == none) {
        switch(gstate) {
            case menu:
                break;
            case lvlEditor:
                cout << "clicked in lvleditor" << endl;
                if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
                    int objX = x / 10, objY = y / 10;
                    Color color = editor->getColor();
                    MapObject* obj = editor->getCurrentSelection();
                    
                    if(Obstacle* oObj = dynamic_cast<Obstacle*>(obj)) {
                        editor->addObstacle(oObj->getName(), objX, objY, 10, 10);
                    } else if (Terrain* tObj = dynamic_cast<Terrain*>(obj)){
                        editor->addTerrain(tObj->getName(), objX, objY, 10, 10, tObj->getIsPassable());
                    }
                    
                    cout << "Added object at: " << objX << ", " << objY << endl;
                }
                
                if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
                    int objX = x / 10, objY = y / 10;
                    editor->removeMapObjAt(objX, objY);
                    cout << "Removed object at: " << objX << ", " << objY << endl;
                }
                
                break;
            case gameplay:
                cout << "clicked in gameplay" << endl;
                break;
            case gameOver:
                break;
        }
    }
    
    glutPostRedisplay();
}

void timer(int extra) {
    // do something
    if(gstate == gameplay) {
        game->update();
    }
    
    glutPostRedisplay();
    glutTimerFunc(10, timer, 0);
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
    glutKeyboardUpFunc(kbdup);
    
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
