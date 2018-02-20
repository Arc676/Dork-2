//
//  MainMenu.h
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 03/12/2017.
//      <alesvinciguerra@gmail.com>
//Copyright (C) 2017-8 Arc676/Alessandro Vinciguerra

//This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation (version 3)

//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//You should have received a copy of the GNU General Public License
//along with this program.  If not, see <http://www.gnu.org/licenses/>.
//See README and LICENSE for more details

#ifndef MainMenu_h
#define MainMenu_h

#include "Scene.h"

// limit on player name length
#define NAMELENGTH 30

class MainMenu : public Scene {
	// player selection
	int currentSelection = 0;
	orxOBJECT* selector;
	orxOBJECT* lrArrows;

	// player name
	orxOBJECT* nameField;
	char name[NAMELENGTH];
	int cursorPos = 0;

	// chosen entity type for player
	orxOBJECT* typeField;
	EntityType chosenType = MAGIC;
public:
	MainMenu();
	
	virtual void activate();

	virtual SceneType update(const orxCLOCK_INFO*);
	virtual SceneType getSceneType();
};

#endif
