//
//  Scene.h
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

#ifndef Scene_h
#define Scene_h

#include "orx.h"

#include "Enums.h"
#include "Player.h"

class Scene {
protected:
	Scene* nextScene = orxNULL;
	Player* player;

	orxBOOL getKeyDown(orxSTRING key) {
		return orxInput_IsActive(key) && orxInput_HasNewStatus(key);
	}
public:
	void loadPlayerData(Player* player) {
		this->player = player;
	};
	Player* getPlayerData() {
		return player;
	}

	virtual void activate() = 0;
	virtual void deactivate() = 0;
	
	virtual SceneType update(const orxCLOCK_INFO*) = 0;
	virtual SceneType getSceneType() = 0;
	Scene* getNextScene() {
		return nextScene;
	};
};

#endif
