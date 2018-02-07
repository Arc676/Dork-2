//
//  Scene.h
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

#ifndef Scene_h
#define Scene_h

//pause menu
#define PAUSE_MENU_ITEM_COUNT 3
#define PAUSE_SAVE 0
#define PAUSE_TOGGLE_MUSIC 1
#define PAUSE_RESUME 2
#define PAUSE_EXIT 3

#include "orx.h"

#include "Enums.h"
#include "Player.h"

class Scene {
	orxOBJECT* pauseSelector = orxNULL;
	orxOBJECT* pauseMenu = orxNULL;

	orxBOOL hasText = orxFALSE;
	orxOBJECT* uiTextObject = orxNULL;
	orxOBJECT* uiTextSprite = orxNULL;
	const orxVECTOR textMargin = {10, 10, 0};
protected:
	Scene* nextScene = orxNULL;
	Player* player = orxNULL;
	orxBOOL canSave = orxFALSE;
	SceneType nextSceneType;

	static orxBOOL playMusic;
	orxSOUND* music = orxNULL;

	static orxBOOL getKeyDown(orxSTRING);

	void loadUIText(orxSTRING);
	void dismissUIText();
	orxBOOL currentlyHasText();
	void initializeUITextAt(orxVECTOR);
	void moveUITextTo(orxVECTOR);

	orxBOOL paused = orxFALSE;
	int pauseMenuSelection = 0;
	void setPauseMenuPosition(orxVECTOR);

	void toggleMusic();

	Scene();
	void destroy();
public:
	virtual void loadPlayerData(Player*);
	Player* getPlayerData();

	virtual void activate();
	virtual void deactivate();
	
	virtual SceneType update(const orxCLOCK_INFO*);
	virtual SceneType getSceneType() = 0;
	Scene* getNextScene();

	virtual orxSTATUS EventHandler(const orxEVENT*);
};

#endif
