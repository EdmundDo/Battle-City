//
//  GameMenu.hpp
//  Battle City
//
//  Created by Edmund Do on 4/24/17.
//  Copyright © 2017 Edmund Do. All rights reserved.
//

#ifndef GameMenu_hpp
#define GameMenu_hpp

#include "Map.hpp"

#include <string>
using namespace std;

enum Selection {startGame, mapEditor, instructions};

class GameMenu {
public:
    GameMenu();
    ~GameMenu();
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: chooses the next selection
     */
    
    void nextSelection();
    
    /**
     * Requires: nothing
     * Modifies: currentSelection
     * Effects: changes the currently selected option
     */
    
    Selection getCurrentSelection();
    void setCurrentSelection(Selection s);
    Map* getMap();
    
    void draw();
    
    static string selectionToString(Selection s);
private:
    Selection currentSelection;
    unique_ptr<Map> map;
};

#endif /* GameMenu_hpp */
