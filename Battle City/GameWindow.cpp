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
GLdouble width, height;
int wd;

// Game params
int mouseX, mouseY;

enum GameState {menu, lvlEditor, gameplay, gameOver};
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
    glColor3f(1, 1, 1);
    glRasterPos2i(300, 250);
    for (int i = 0; i < query.length(); ++i) {
        glutBitmapCharacter(font, query[i]);
    }
    
    if(input != "") {
        unsigned char inputc[input.length()];
        strcpy((char*) inputc, input.c_str());
        
        int x = width - glutBitmapLength(font, inputc) / 2;
        glRasterPos2i(x, height / 2);
        
        for (int i = 0; i < input.length(); ++i) {
            glutBitmapCharacter(font, input[i]);
        }
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
        switch(key) {
            case 'w':
                switch(gstate) {
                    case menu:
                        gameMenu->nextSelection();
                        break;
                    case lvlEditor:
                        switch (editor->getSelectedColorIndex()) {
                            case 0:
                                editor->changeRedVal(POS);
                                break;
                            case 1:
                                editor->changeGreenVal(POS);
                                break;
                            case 2:
                                editor->changeBlueVal(POS);
                                break;
                            default:
                                break;
                        }
                        break;
                    case gameplay:
                        game->handleKey('w');
                        break;
                    default:
                        break;
                }
                break;
            case 'a':
                switch(gstate) {
                    case menu:
                        break;
                    case lvlEditor:
                        editor->nextSelection();
                        break;
                    case gameplay:
                        game->handleKey('a');
                        break;
                    default:
                        break;
                }
                break;
            case 'd':
                switch(gstate) {
                    case menu:
                        break;
                    case lvlEditor:
                        editor->nextSelection();
                        break;
                    case gameplay:
                        game->handleKey('d');
                        break;
                    default:
                        break;
                }
                break;
            case 's':
                switch(gstate) {
                    case menu:
                        gameMenu->nextSelection();
                        break;
                    case lvlEditor:
                        switch (editor->getSelectedColorIndex()) {
                            case 0:
                                editor->changeRedVal(NEG);
                                break;
                            case 1:
                                editor->changeGreenVal(NEG);
                                break;
                            case 2:
                                editor->changeBlueVal(NEG);
                                break;
                            default:
                                break;
                        }
                        break;
                    case gameplay:
                        game->handleKey('s');
                        break;
                    default:
                        break;
                }
                break;
            case 'i':
                switch(gstate) {
                    case menu:
                        break;
                    case lvlEditor:
                        break;
                    case gameplay:
                        game->handleKey('i');
                        break;
                    default:
                        break;
                }
                break;
            case 'j':
                switch(gstate) {
                    case menu:
                        break;
                    case lvlEditor:
                        break;
                    case gameplay:
                        game->handleKey('j');
                        break;
                    default:
                        break;
                }
                break;
            case 'l':
                switch(gstate) {
                    case menu:
                        break;
                    case lvlEditor:
                        break;
                    case gameplay:
                        game->handleKey('l');
                        break;
                    default:
                        break;
                }
                break;
            case 'k':
                switch(gstate) {
                    case menu:
                        break;
                    case lvlEditor:
                        break;
                    case gameplay:
                        game->handleKey('k');
                        break;
                    default:
                        break;
                }
                break;
            case ';':
                switch(gstate) {
                    case menu:
                        break;;;
                    case lvlEditor:
                        break;
                    case gameplay:
                        game->handleKey(';');
                        break;
                    default:
                        break;
                }
                break;
            case ' ':
                switch(gstate) {
                    case menu:
                        break;
                    case lvlEditor:
                        break;
                    case gameplay:
                        game->handleKey(' ');
                        break;
                    default:
                        break;
                }
                break;
            case 'q':
                switch(gstate) {
                    case menu:
                        break;
                    case lvlEditor:
                        overlay = textField;
                        query = "Enter save file name: ";
                        break;
                    case gameplay:
                        break;
                    default:
                        break;
                }
                break;
            case 'c':
                switch (gstate) {
                    case lvlEditor:
                        editor->nextColorSelection();
                        break;
                    default:
                        break;
                }
                break;
            case 13:
                // enter key
                switch(gstate) {
                    case menu:
                        switch(gameMenu->getCurrentSelection()) {
                            case startGame:
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
                            case mapEditor:
                                editor.reset(new LevelEditor(20, 20));
                                gstate = lvlEditor;
                                break;
                        }
                        break;
                    case lvlEditor:
                        break;
                    case gameplay:
                        break;
                    default:
                        break;
                }
                break;
            case 27:
                // esc key
                glutDestroyWindow(wd);
                exit(0);
            default:
                // otherwise
                if(gstate == gameOver) {
                    gstate = menu;
                }
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
    
    switch(key) {
        case 'w':
            switch(gstate) {
                case menu:
                    break;
                case lvlEditor:
                    break;
                case gameplay:
                    game->handleKey('w');
                    break;
                default:
                    break;
            }
            break;
        case 's':
            switch(gstate) {
                case menu:
                    break;
                case lvlEditor:
                    break;
                case gameplay:
                    game->handleKey('s');
                    break;
                default:
                    break;
            }
            break;
        case 'i':
            switch(gstate) {
                case menu:
                    break;
                case lvlEditor:
                    break;
                case gameplay:
                    game->handleKey('i');
                    break;
                default:
                    break;
            }
            break;
        case 'k':
            switch(gstate) {
                case menu:
                    break;
                case lvlEditor:
                    break;
                case gameplay:
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
    cout << "clicked in window" << endl;
    switch(gstate) {
        case menu:
            break;
        case lvlEditor:
            cout << "clicked in lvleditor" << endl;
            if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
                int objX = x / 10, objY = y / 10;
                Color color = {1, 1, 1};
                MapObject* obj = editor->getCurrentSelection();
                
                if(Obstacle* oObj = dynamic_cast<Obstacle*>(obj)) {
                    editor->addObstacle(oObj->getName(), objX, objY, 10, 10, oObj->getColor());
                } else if (Terrain* tObj = dynamic_cast<Terrain*>(obj)){
                    editor->addTerrain(tObj->getName(), objX, objY, 10, 10, tObj->getColor(), tObj->getIsPassable());
                }
                
                cout << "Added object at: " << objX << ", " << objY << endl;
            }
            
            if(button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
                int px = x / 10, py = x / 10;
                editor->addPreferredStart(px, py);
            }
            
            break;
        case gameplay:
            cout << "clicked in gameplay" << endl;
            break;
        case gameOver:
            break;
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
    glutIgnoreKeyRepeat(true);
    
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

