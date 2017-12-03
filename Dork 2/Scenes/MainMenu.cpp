//
//  MainMenu.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 03/12/2017.
//      <alesvinciguerra@gmail.com>
//Copyright (C) 2017 Arc676/Alessandro Vinciguerra

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

#include "MainMenu.h"

void MainMenu::activate() {}
void MainMenu::deactivate() {}

MainMenu::MainMenu() {
	//
}

SceneType MainMenu::getSceneType() {
	return MAIN_MENU;
}

SceneType MainMenu::update(const orxCLOCK_INFO* clockInfo) {
	if (currentSelection == 0) {
		orxKEYBOARD_KEY keyPressed = orxKeyboard_ReadKey();
		if (keyPressed == orxKEYBOARD_KEY_BACKSPACE && cursorPos > 0) {
			name[cursorPos--] = 0;
		} else if (keyPressed != orxKEYBOARD_KEY_NONE && cursorPos < NAMELENGTH) {
			const orxSTRING character = orxKeyboard_GetKeyName(keyPressed);
			orxU32 c = orxString_GetFirstCharacterCodePoint(character, orxNULL);
			if (orxString_IsCharacterAlphaNumeric(c)) {
				name[cursorPos++] = c;
			}
		}
	}
	orxVECTOR pos;
	orxObject_GetPosition(selector, &pos);
	if (getKeyDown((orxSTRING)"GoDown") && currentSelection < 3) {
		currentSelection++;
		pos.fY += 60;
	} else if (getKeyDown((orxSTRING)"GoUp") && currentSelection > 0) {
		currentSelection--;
		pos.fY -= 60;
	} else if (getKeyDown((orxSTRING)"Enter")) {
		if (currentSelection == 2) {
			player = new Player(name, chosenType);
			return EXPLORATION;
		} else if (currentSelection == 3) {
			//
		}
	}
	return MAIN_MENU;
}
