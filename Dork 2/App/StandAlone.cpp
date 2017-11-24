//
//  StandAlone.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 17/11/2017.
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

#include "StandAlone.h"

StandAlone* StandAlone::m_Instance = nullptr;

Scene* StandAlone::currentScene = nullptr;
orxVIEWPORT* StandAlone::currentViewport = nullptr;
orxCAMERA* StandAlone::currentCamera = nullptr;

orxVIEWPORT* StandAlone::mainViewport = nullptr;
orxCAMERA* StandAlone::camera = nullptr;
Exploration* StandAlone::explorationScene = nullptr;

orxVIEWPORT* StandAlone::combatViewport = nullptr;
orxCAMERA* StandAlone::combatCam = nullptr;

orxVIEWPORT* StandAlone::shopViewport = nullptr;
orxCAMERA* StandAlone::shopCam = nullptr;
Shop* StandAlone::shopScene = nullptr;

Player* StandAlone::player = nullptr;

StandAlone* StandAlone::Instance() {
	if (m_Instance != nullptr) {
		return m_Instance;
	}
	m_Instance = new StandAlone();
	return m_Instance;
}

StandAlone::StandAlone() {}

//written by Wayne "Sausage" Johnson
void StandAlone::paintTiles(const orxSTRING mapSection, float fZ) {
	int tilesWide = 100;
	int tileSize = 32;
	orxVECTOR position = orxVECTOR_0;

	orxConfig_PushSection(mapSection);

	orxU32 baseMapIndex = 0;

	orxU32 propertyCount = orxConfig_GetKeyCounter();

	for (orxS32 propertyIndex = 1; propertyIndex < propertyCount + 1; propertyIndex++) {
		orxCHAR property[30]; //good maximum length
		orxString_Print(property, "MapPart%d", propertyIndex);

		orxU32 listCount = orxConfig_GetListCounter(property);

		for (int listIndex = 0; listIndex < listCount; listIndex++) {
			const orxSTRING tile = orxConfig_GetListString(property, listIndex);

			position.fX = (baseMapIndex % tilesWide) * tileSize;
			position.fY = (baseMapIndex / tilesWide) * tileSize;
			position.fZ = fZ;

			orxCHAR formattedTileObject[30]; //good maximum length
			orxString_Print(formattedTileObject, "%sObject", tile);

			//orxLOG(formattedTileObject);

			orxOBJECT *obj = orxObject_CreateFromConfig(formattedTileObject);

			if (obj != orxNULL) {
				orxVECTOR tilePos = orxVECTOR_0;
				orxObject_GetPosition(obj, &tilePos);

				orxObject_SetPosition(obj, &position);
			}
			baseMapIndex++;
		}
	}
	orxConfig_PopSection();
}

orxSTATUS orxFASTCALL StandAlone::Init() {
	mainViewport = orxViewport_CreateFromConfig("Viewport");
	camera = orxViewport_GetCamera(mainViewport);

	combatViewport = orxViewport_CreateFromConfig("CombatViewport");
	combatCam = orxViewport_GetCamera(combatViewport);
	orxViewport_Enable(combatViewport, orxFALSE);

	shopViewport = orxViewport_CreateFromConfig("ShopViewport");
	shopCam = orxViewport_GetCamera(shopViewport);
	orxViewport_Enable(shopViewport, orxFALSE);

	orxConfig_Load("Map1.ini");
	orxObject_CreateFromConfig("Map1");
	paintTiles("Terrain", 0);
	paintTiles("Colliders", -0.1f);
	paintTiles("Shrubs", -0.2f);

	orxConfig_Load("Player.ini");

	player = new Player("Bob", MAGIC);

	currentViewport = mainViewport;
	currentCamera = camera;
	explorationScene = new Exploration(player, camera);
	currentScene = explorationScene;
	currentScene->activate();

	shopScene = new Shop(player);

//	environment = new Environment();
//
//	orxConfig_Load("UI.ini");
//	scoreLabel = orxObject_CreateFromConfig("ScoreLabel");
//
//	orxConfig_Load("Items.ini");
//
	orxCLOCK* upClock = orxClock_FindFirst(-1.0f, orxCLOCK_TYPE_CORE);
	orxClock_Register(upClock, Update, orxNULL, orxMODULE_ID_MAIN, orxCLOCK_PRIORITY_NORMAL);

	orxEvent_AddHandler(orxEVENT_TYPE_PHYSICS, StandAlone::EventHandler);
	orxEvent_AddHandler(orxEVENT_TYPE_INPUT, StandAlone::EventHandler);

	return orxSTATUS_SUCCESS;
}

orxSTATUS orxFASTCALL StandAlone::Run() {
	return orxSTATUS_SUCCESS;
}

void orxFASTCALL StandAlone::Exit() {
	return;
}

orxOBJECT* StandAlone::GetObjectByName(orxSTRING objName) {
	for (orxOBJECT* obj = orxOBJECT(orxStructure_GetFirst(orxSTRUCTURE_ID_OBJECT));
		 obj != orxNULL;
		 obj = orxOBJECT(orxStructure_GetNext(obj))) {
		if (orxString_Compare(orxObject_GetName(obj), objName) == 0) {
			return obj;
		}
	}
	return orxNULL;
}

void orxFASTCALL StandAlone::Update(const orxCLOCK_INFO* clockInfo, void* context) {
	SceneType nextScene = currentScene->update(clockInfo);
	if (nextScene != currentScene->getSceneType()) {
		orxViewport_Enable(currentViewport, orxFALSE);
		currentScene->deactivate();
		switch (nextScene) {
			case EXPLORATION:
				currentViewport = mainViewport;
				currentCamera = camera;
				explorationScene->loadPlayerData(currentScene->getPlayerData());
				currentScene = explorationScene;
				break;

			case COMBAT:
				currentViewport = combatViewport;
				currentCamera = combatCam;
				if (currentScene->getNextScene() != orxNULL) {
					currentScene = currentScene->getNextScene();
				}
				break;

			case SHOP:
				currentViewport = shopViewport;
				currentCamera = shopCam;
				shopScene->loadPlayerData(currentScene->getPlayerData());
				currentScene = shopScene;
				break;
		}
		orxViewport_Enable(currentViewport, orxTRUE);
		currentScene->activate();
	}
}

//orxVECTOR orxFASTCALL StandAlone::GetMouseWorldPosition() {
//	orxVECTOR worldpos, screenpos;
//
//	orxRender_GetWorldPosition(orxMouse_GetPosition(&screenpos), orxNULL, &worldpos);
//	worldpos.fZ = 0;
//
//	return worldpos;
//}

orxSTATUS orxFASTCALL StandAlone::EventHandler(const orxEVENT* currentEvent) {
	switch(currentEvent->eType) {
		case orxEVENT_TYPE_INPUT:
			break;
		case orxEVENT_TYPE_PHYSICS:
			break;
		default:
			break;
	}

	return orxSTATUS_SUCCESS;
}
