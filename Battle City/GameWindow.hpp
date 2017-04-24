//
//  GameWindow.hpp
//  Battle City
//
//  Created by Edmund Do on 4/23/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#ifndef GameWindow_hpp
#define GameWindow_hpp

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/time.h>
#endif

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>

// Program initialization
void init(void);

// Draw the window
void display(void);

// Called when window is resized, and when window is first created, before display().
void reshape(int w, int h);

// Refresh the display, called when system is idle
void refresh(void);

// Process keyboard events
void kbd(unsigned char key, int x, int y);

// Handle "mouse cursor moved" events
void cursor(int x, int y);

// Handle "mouse moved with button pressed" events
void drag(int x, int y);

// Handle mouse button pressed and released events
void mouse(int button, int state, int x, int y);

#endif /* GameWindow_hpp */
