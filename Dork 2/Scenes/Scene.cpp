//
//  Scene.cpp
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

#include "Scene.h"

orxBOOL Scene::playMusic = orxTRUE;
const orxVECTOR Scene::textMargin = Scene::createVector(10, 10, 0);

orxVECTOR Scene::createVector(orxFLOAT x, orxFLOAT y, orxFLOAT z) {
	orxVECTOR vector;
	vector.fX = x;
	vector.fY = y;
	vector.fZ = z;
	return vector;
}

Scene::Scene() {
	pauseSelector = orxObject_CreateFromConfig("Selector");
	orxObject_Enable(pauseSelector, orxFALSE);

	pauseMenu = orxObject_CreateFromConfig("PauseMenu");
	orxObject_Enable(pauseMenu, orxFALSE);
}

void Scene::destroy() {
	orxObject_SetLifeTime(pauseMenu, 0);
	orxObject_SetLifeTime(pauseSelector, 0);
}

void Scene::setPauseMenuPosition(orxVECTOR pos) {
	pos.fZ = -0.1;
	pos.fX -= 160;
	pos.fY -= 80;
	orxObject_SetPosition(pauseSelector, &pos);
	pos.fX += 180;
	pos.fY += 90;
	orxObject_SetPosition(pauseMenu, &pos);
}

orxBOOL Scene::getKeyDown(orxSTRING key) {
	return orxInput_IsActive(key) && orxInput_HasNewStatus(key);
}

void Scene::loadPlayerData(Player* player) {
	this->player = player;
}

Player* Scene::getPlayerData() {
	return player;
}

Scene* Scene::getNextScene() {
	return nextScene;
}

orxSTATUS Scene::EventHandler(const orxEVENT*) {
	return orxSTATUS_SUCCESS;
}

void Scene::toggleMusic() {
	Scene::playMusic = !Scene::playMusic;
	if (music != orxNULL) {
		if (Scene::playMusic) {
			orxSound_Play(music);
		} else {
			orxSound_Pause(music);
		}
	}
}

void Scene::activate() {
	nextSceneType = getSceneType();
	if (Scene::playMusic && music != orxNULL) {
		orxSound_Play(music);
	}
}

void Scene::deactivate() {
	if (music != orxNULL) {
		orxSound_Pause(music);
	}
}

void Scene::loadUIText(orxSTRING text) {
	hasText = orxTRUE;
	orxObject_SetTextString(uiTextObject, text);
	orxObject_Enable(uiTextObject, orxTRUE);
	orxObject_Enable(uiTextSprite, orxTRUE);
}

void Scene::dismissUIText() {
	hasText = orxFALSE;
	orxObject_Enable(uiTextObject, orxFALSE);
	orxObject_Enable(uiTextSprite, orxFALSE);
}

void Scene::initializeUITextAt(orxVECTOR pos) {
	uiTextObject = orxObject_CreateFromConfig("UIText");
	uiTextSprite = orxObject_CreateFromConfig("UITextSprite");

	moveUITextTo(pos);

	orxObject_Enable(uiTextObject, orxFALSE);
	orxObject_Enable(uiTextSprite, orxFALSE);
}

void Scene::moveUITextTo(orxVECTOR pos) {
	orxObject_SetPosition(uiTextSprite, &pos);
	orxVector_Add(&pos, &pos, &textMargin);
	orxObject_SetPosition(uiTextObject, &pos);
}

orxBOOL Scene::currentlyHasText() {
	return hasText;
}

SceneType Scene::update(const orxCLOCK_INFO* clockInfo) {
	if (getKeyDown((orxSTRING)"Pause")) {
		paused = !paused;
		orxObject_Enable(pauseSelector, paused);
		orxObject_Enable(pauseMenu, paused);
	}
	if (paused) {
		orxVECTOR pos;
		orxObject_GetPosition(pauseSelector, &pos);
		int prevSelection = pauseMenuSelection;
		if (getKeyDown((orxSTRING)"GoDown") && pauseMenuSelection < PAUSE_MENU_ITEM_COUNT) {
			pauseMenuSelection++;
			pos.fY += 60;
		} else if (Scene::getKeyDown((orxSTRING)"GoUp") && pauseMenuSelection > 0) {
			pauseMenuSelection--;
			pos.fY -= 60;
		} else if (Scene::getKeyDown((orxSTRING)"Enter")) {
			switch (pauseMenuSelection) {
				case PAUSE_SAVE:
					if (canSave && player->write() == orxSTATUS_SUCCESS) {
						pauseMenuSelection = 2;
						pos.fY += 120;
					}
					break;
				case PAUSE_TOGGLE_MUSIC:
					toggleMusic();
					break;
				case PAUSE_RESUME:
				case PAUSE_EXIT:
				{
					//unpause
					orxObject_Enable(pauseSelector, orxFALSE);
					orxObject_Enable(pauseMenu, orxFALSE);
					paused = orxFALSE;

					//reset selector position
					orxVECTOR pos;
					orxObject_GetPosition(pauseSelector, &pos);
					pos.fY -= 60 * pauseMenuSelection;
					orxObject_SetPosition(pauseSelector, &pos);

					int selected = pauseMenuSelection;
					pauseMenuSelection = 0;

					//return to main menu if necessary
					if (selected == PAUSE_EXIT) {
						return MAIN_MENU;
					}
				}
					break;
				default:
					break;
			}
		}
		if (pauseMenuSelection != prevSelection) {
			orxObject_SetPosition(pauseSelector, &pos);
			orxObject_AddSound(pauseSelector, "SelectorSound");
		}
	} else if (hasText) {
		if (Scene::getKeyDown((orxSTRING)"Enter")) {
			dismissUIText();
		}
	}
	return getSceneType();
}
