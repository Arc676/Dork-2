//
//  Exploration.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 24/11/2017.
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

#include "Exploration.h"
#include "Combat.h"

Exploration::Exploration(Player* player, orxCAMERA* camera) : camera(camera) {
	loadPlayerData(player);
	music = orxSound_CreateFromConfig("BackgroundMusic1");
}

void Exploration::activate() {
	nextSceneType = EXPLORATION;
	orxSound_Play(music);
}

void Exploration::deactivate() {
	orxSound_Pause(music);
}

void Exploration::spawnEnemy() {
	orxVECTOR ds = {
		orxMath_GetRandomFloat(510, 710),
		orxMath_GetRandomFloat(310, 510),
		0
	};
	if (orxMath_GetRandomS32(0, 99) < 50) {
		ds.fX *= -1;
	}
	if (orxMath_GetRandomS32(0, 99) < 50) {
		ds.fY *= -1;
	}
	orxVECTOR pos;
	orxVECTOR ppos = player->getPosition();
	orxVector_Add(&pos, &ppos, &ds);
	if (pos.fX < 0 || pos.fX > 3200 || pos.fY < 0 || pos.fY > 3200) {
		return;
	}
	Enemy::createRandomEnemy(
							 GOBLIN,//(EnemyType)orxMath_GetRandomU32(0, ENEMYCOUNT - 1),
							 player->getLevel(),
							 pos
							 );
	enemiesInExistence++;
}

SceneType Exploration::update(const orxCLOCK_INFO* clockInfo) {
	orxFLOAT delta = clockInfo->fDT;
	orxU32 defaultGroupID = orxString_GetID(orxOBJECT_KZ_DEFAULT_GROUP);
	for (
		 orxOBJECT *obj = orxObject_GetNext(orxNULL, defaultGroupID);
		 obj != orxNULL;
		 obj = orxObject_GetNext(obj, defaultGroupID)
		 ) {
		orxSTRING name = (orxSTRING)orxObject_GetName(obj);
		if (orxString_Compare(name, "Player") == 0) {
			player->update(orxInput_IsActive("GoUp"),
						   orxInput_IsActive("GoDown"),
						   orxInput_IsActive("GoLeft"),
						   orxInput_IsActive("GoRight"),
						   delta);
		} else {
			orxConfig_PushSection(name);
			if (orxConfig_GetBool("IsEnemy")) {
				Enemy* e = (Enemy*)orxObject_GetUserData(obj);
				orxVECTOR distance;
				orxVECTOR ppos = player->getPosition();
				orxVECTOR epos = e->getPosition();
				orxVector_Sub(&distance, &ppos, &epos);
				if (orxVector_GetSize(&distance) > 900) {
					e->despawn();
					enemiesInExistence--;
				} else {
					e->update(delta);
				}
			}
			orxConfig_PopSection();
		}
	}
	if (enemiesInExistence < 15) {
		timeSinceEnemySpawn += delta;
		if (timeSinceEnemySpawn > 5) {
			timeSinceEnemySpawn = 0;
			spawnEnemy();
		}
	}
	//update camera position
	orxVECTOR camPos = {0, 0, 0};
	orxCamera_GetPosition(camera, &camPos);
	camPos.fX = player->getPosition().fX;
	camPos.fY = player->getPosition().fY;
	orxCamera_SetPosition(camera, &camPos);
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
									nextSceneType = COMBAT;
									enemiesInExistence--;
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

SceneType Exploration::getSceneType() {
	return EXPLORATION;
}
