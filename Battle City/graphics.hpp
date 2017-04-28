//
//  graphics.hpp
//  Battle City
//
//  Created by Edmund Do on 4/25/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#ifndef graphics_h
#define graphics_h

#include <stdlib.h>
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

#endif /* graphics_h */
