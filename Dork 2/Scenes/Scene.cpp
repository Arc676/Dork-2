//
//  Scene.cpp
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

#include "Scene.h"

Scene::Scene() {
	pauseSelector = orxObject_CreateFromConfig("Selector");
	orxObject_Enable(pauseSelector, orxFALSE);
}

orxBOOL Scene::playMusic = orxTRUE;

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
	if (Scene::playMusic && music != orxNULL) {
		orxSound_Play(music);
	}
}

void Scene::deactivate() {
	if (music != orxNULL) {
		orxSound_Pause(music);
	}
}

SceneType Scene::update(const orxCLOCK_INFO* clockInfo) {
	if (getKeyDown((orxSTRING)"Pause")) {
		paused = !paused;
		orxObject_Enable(pauseSelector, paused);
	}
	if (paused) {
		orxVECTOR pos;
		orxObject_GetPosition(pauseSelector, &pos);
		if (getKeyDown((orxSTRING)"GoDown") && pauseMenuSelection < 2) {
			pauseMenuSelection++;
			pos.fY += 60;
		} else if (Scene::getKeyDown((orxSTRING)"GoUp") && pauseMenuSelection > 0) {
			pauseMenuSelection--;
			pos.fY -= 60;
		} else if (Scene::getKeyDown((orxSTRING)"Enter")) {
			switch (pauseMenuSelection) {
				case 0:
					if (canSave && player->write() == orxSTATUS_SUCCESS) {
						pauseMenuSelection = 2;
						pos.fY = 120;
					}
					break;
				case 1:
					toggleMusic();
					break;
				case 2:
					orxObject_Enable(pauseSelector, orxFALSE);
					paused = orxFALSE;
					break;
				default:
					break;
			}
		}
		orxObject_SetPosition(pauseSelector, &pos);
	}
	return getSceneType();
}