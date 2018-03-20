//
//  Exploration.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 24/11/2017.
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

#include "Exploration.h"
#include "Combat.h"

Exploration::Exploration(Player* player, orxCAMERA* camera) : Scene(), camera(camera), existingEnemies() {
	loadPlayerData(player);
	resetMusic();
	canSave = orxTRUE;

	setPauseMenuPosition(Scene::createVector(-50, 0, 0));
	initializeUITextAt(Scene::createVector(-500, 160, -0.1));
}

void Exploration::resetMusic() {
	if (music != orxNULL) {
		orxSound_Stop(music);
	}
	music = orxSound_CreateFromConfig("BackgroundMusic1");
}

void Exploration::resetWorld(Player* player) {
	loadPlayerData(player);
	resetMusic();
	for (std::list<Enemy*>::iterator it = existingEnemies.begin(); it != existingEnemies.end(); it++) {
		(*it)->despawn();
	}
	existingEnemies.clear();
}

void Exploration::spawnEnemy() {
	orxVECTOR ds = {
		orxMath_GetRandomFloat(510, 710),
		orxMath_GetRandomFloat(310, 510),
		0
	};
	orxVECTOR ppos = player->getPosition();
	if (ppos.fX > 710 && (ppos.fX > 2490 || orxMath_GetRandomS32(0, 99) < 50)) {
		ds.fX *= -1;
	}
	if (ppos.fY > 710 && (ppos.fY > 2490 || orxMath_GetRandomS32(0, 99) < 50)) {
		ds.fY *= -1;
	}
	orxVECTOR pos;
	orxVector_Add(&pos, &ppos, &ds);
	if (pos.fX < 0 || pos.fX > 3200 ||
		pos.fY < 0 || pos.fY > 3200 ||
		orxObject_Pick(&pos, orxString_GetID("Colliders")) != orxNULL) {
		return;
	}
	Enemy* e = Enemy::createRandomEnemy(
							 IMP,//(EnemyType)orxMath_GetRandomU32(0, ENEMYCOUNT - 1),
							 player, pos
							 );
	existingEnemies.push_back(e);
}

SceneType Exploration::update(const orxCLOCK_INFO* clockInfo) {
	// was the game already in a state that would require pausing animations?
	// (would imply that the game was paused or text was already present)
	orxBOOL wasPseudoPaused = paused || Scene::currentlyHasText();
	SceneType type = Scene::update(clockInfo);
	if (type != EXPLORATION) {
		return type;
	}
	// if game is in a paused state, do nothing
	if (paused || Scene::currentlyHasText()) {
		// if game wasn't already in such a state, pause animations
		if (!wasPseudoPaused) {
			enableAnimation(orxFALSE);
		}
		return EXPLORATION;
	} else if (wasPseudoPaused) {
		// if game is no longer in a paused state but used to be,
		// resume animations
		enableAnimation(orxTRUE);
	}
	orxFLOAT delta = clockInfo->fDT;
	player->update(orxInput_IsActive("GoUp"),
				   orxInput_IsActive("GoDown"),
				   orxInput_IsActive("GoLeft"),
				   orxInput_IsActive("GoRight"),
				   delta);
	orxVECTOR ppos = player->getPosition();
	for (std::list<Enemy*>::iterator it = existingEnemies.begin(); it != existingEnemies.end();) {
		Enemy* e = *it;
		orxVECTOR epos = e->getPosition();
		orxFLOAT distance = orxVector_GetDistance(&ppos, &epos);
		if (distance > 900) {
			existingEnemies.erase(it++);
			e->despawn();
			continue;
		} else if (distance < 600) {
			e->update(delta);
		}
		it++;
	}
	if (existingEnemies.size() < 15) {
		timeSinceEnemySpawn += delta;
		if (timeSinceEnemySpawn > 5) {
			timeSinceEnemySpawn = 0;
			spawnEnemy();
		}
	}
	//update camera position
	orxVECTOR camPos;
	orxCamera_GetPosition(camera, &camPos);
	camPos.fX = player->getPosition().fX;
	camPos.fY = player->getPosition().fY;
	orxCamera_SetPosition(camera, &camPos);
	camPos.fX -= 50;
	setPauseMenuPosition(camPos);
	pauseMenuSelection = 0;
	return nextSceneType;
}

orxSTATUS Exploration::EventHandler(const orxEVENT* currentEvent) {
	switch(currentEvent->eType) {
		case orxEVENT_TYPE_PHYSICS:
			switch (currentEvent->eID) {
				case orxPHYSICS_EVENT_CONTACT_ADD:
					orxOBJECT* objs[] = {
						orxOBJECT(currentEvent->hSender),
						orxOBJECT(currentEvent->hRecipient)
					};
					for (int i = 0; i < 2; i++) {
						orxSTRING name = (orxSTRING)orxObject_GetName(objs[i]);
						orxSTRING name2 = (orxSTRING)orxObject_GetName(objs[1 - i]);
						if (orxString_Compare(name2, "Player") == 0) {
							if (orxString_Compare(name, "Shop") == 0) {
								nextSceneType = SHOP;
								return orxSTATUS_SUCCESS;
							} else if (orxString_Compare(name, "Armory") == 0) {
								nextSceneType = ARMORY;
								return orxSTATUS_SUCCESS;
							} else {
								orxConfig_PushSection(name);
								orxBOOL isEnemy = orxConfig_GetBool("IsEnemy");
								orxConfig_PopSection();
								if (isEnemy) {
									Enemy* e = (Enemy*)orxObject_GetUserData(objs[i]);
									nextScene = new Combat(player, e);

									enableAnimation(orxFALSE);
									player->pauseAnimation();
									existingEnemies.remove(e);

									nextSceneType = COMBAT;
									orxCHAR text[40];
									orxString_Print(text, "%s encountered a(n) %s!",
													player->getName(), e->getName());

									orxVECTOR pos;
									orxCamera_GetPosition(camera, &pos);
									orxVector_Add(&pos, &pos, &UITextOffset);
									moveUITextTo(pos);

									loadUIText(text);

									return orxSTATUS_SUCCESS;
								}
							}
						} else {
							// only monsters move (aside from the player),
							// so if neither entity is a player,
							// a monster must have hit something
							if (orxString_Compare(name, "Player") != 0) {
								orxConfig_PushSection(name2);
								orxBOOL isEnemy = orxConfig_GetBool("IsEnemy");
								orxConfig_PopSection();
								if (isEnemy) {
									Enemy* e = (Enemy*)orxObject_GetUserData(objs[1 - i]);
									e->newRandomDirection();
									return orxSTATUS_SUCCESS;
								}
							}
						}
					}
					break;
			}
			break;
		default:
			break;
	}

	return orxSTATUS_SUCCESS;
}

void Exploration::enableAnimation(orxBOOL enable) {
	for (std::list<Enemy*>::iterator it = existingEnemies.begin(); it != existingEnemies.end(); it++) {
		if (enable) {
			(*it)->resumeAnimation();
		} else {
			(*it)->pauseAnimation();
		}
	}
}

void Exploration::activate() {
	enableAnimation(orxTRUE);
	Scene::activate();
}

SceneType Exploration::getSceneType() {
	return EXPLORATION;
}
