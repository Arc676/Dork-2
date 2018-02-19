//
//  StandAlone.h
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 17/11/2017.
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

#ifndef StandAlone_h
#define StandAlone_h

#include "orx.h"

#include "MainMenu.h"
#include "Exploration.h"
#include "Combat.h"
#include "Shop.h"
#include "Armory.h"

#include "Player.h"

class StandAlone {
public:
	static StandAlone* Instance();

	static void paintTiles(const orxSTRING);
	
	static orxSTATUS orxFASTCALL Init();
	static orxSTATUS orxFASTCALL Run();

	static void orxFASTCALL Exit();

	static void orxFASTCALL Update(const orxCLOCK_INFO*, void*);

	static orxSTATUS orxFASTCALL EventHandler(const orxEVENT*);
protected:
	StandAlone();
	StandAlone(const StandAlone&);
	StandAlone& operator= (const StandAlone&);
private:
	static StandAlone* m_Instance;

	// reference to player
	static Player* player;

	// references to scenes, viewports, and cameras for each
	// scene in game
	static Scene* currentScene;
	static orxVIEWPORT* currentViewport;
	static orxCAMERA* currentCamera;

	static orxVIEWPORT* mainMenuViewport;
	static orxCAMERA* mainMenuCamera;
	static MainMenu* mainMenuScene;

	static orxVIEWPORT* explorationViewport;
	static orxCAMERA* explorationCamera;
	static Exploration* explorationScene;

	static orxVIEWPORT* combatViewport;
	static orxCAMERA* combatCam;

	static orxVIEWPORT* shopViewport;
	static orxCAMERA* shopCam;
	static Shop* shopScene;

	static orxVIEWPORT* armoryViewport;
	static orxCAMERA* armoryCam;
	static Armory* armoryScene;
};

#endif
