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

enum Selection {GMStartGame, GMMapEditor, GMInstructions, GMExit};

class GameMenu {
public:
    GameMenu();
    ~GameMenu();
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: chooses the next menu selection
     */
    
    void nextSelection();
    
    /**
     * Requires: nothing
     * Modifies: nothing
     * Effects: chooses the next map selection
     */
    
    void nextMapSelection();
    
    /**
     * Requires: nothing
     * Modifies: currentSelection
     * Effects: changes the currently selected option
     */
    
    Selection getCurrentSelection();
    void setCurrentSelection(Selection s);
    string getCurrentMapSelection();
    Map* getMap();
    
    void draw();
    
    static string selectionToString(Selection s);
private:
    Selection currentSelection;
    int mapSelection;
    
    static const string maps[];
};

#endif /* GameMenu_hpp */
