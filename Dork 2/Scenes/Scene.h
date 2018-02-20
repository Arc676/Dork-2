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

// pause menu selections
#define PAUSE_MENU_ITEM_COUNT 3
#define PAUSE_SAVE 0
#define PAUSE_TOGGLE_MUSIC 1
#define PAUSE_RESUME 2
#define PAUSE_EXIT 3

#include "orx.h"

#include "Enums.h"
#include "Player.h"

class Scene {
	// pause menu objects
	orxOBJECT* pauseSelector = orxNULL;
	orxOBJECT* pauseMenu = orxNULL;

	// UI text objects
	orxBOOL hasText = orxFALSE;
	orxOBJECT* uiTextObject = orxNULL;
	orxOBJECT* uiTextSprite = orxNULL;
	const orxVECTOR textMargin = {10, 10, 0};
protected:
	// scene data
	Scene* nextScene = orxNULL;
	Player* player = orxNULL;
	orxBOOL canSave = orxFALSE;
	SceneType nextSceneType;

	// music settings
	static orxBOOL playMusic;
	orxSOUND* music = orxNULL;

	/**
	 * Gets whether a key was pressed while only
	 * triggering on the first key down event
	 * @param orxSTRING desired key
	 * @return whether the key has been pressed (only first key down)
	 */
	static orxBOOL getKeyDown(orxSTRING);

	/**
	 * Load text to display in mini alert
	 * @param orxSTRING text to display
	 */
	void loadUIText(orxSTRING);

	/**
	 * Dismiss the alert
	 */
	void dismissUIText();

	/**
	 * Whether the scene is currently showing
	 * an alert
	 * @return whether an alert is present
	 */
	orxBOOL currentlyHasText();

	/**
	 * Initializes UI text objects
	 * @param orxVECTOR render position for alerts
	 */
	void initializeUITextAt(orxVECTOR);

	/**
	 * Move the UI text objects
	 * @param orxVECTOR new render position for alerts
	 */
	void moveUITextTo(orxVECTOR);

	orxBOOL paused = orxFALSE;
	int pauseMenuSelection = 0;

	/**
	 * Set location of pause menu in world space
	 * @param orxVECTOR new position for pause menu
	 */
	void setPauseMenuPosition(orxVECTOR);

	void toggleMusic();

	Scene();

	/**
	 * Destroy the pause menu
	 */
	void destroy();
public:
	/**
	 * Load a new player
	 * @param Player* player to load into scene
	 */
	virtual void loadPlayerData(Player*);

	/**
	 * Get the currently loaded player
	 * @return loaded player
	 */
	Player* getPlayerData();

	/**
	 * Tells the scene that it is now the active
	 * scene
	 */
	virtual void activate();

	/**
	 * Tells the scene that it is no longer
	 * the active scene
	 */
	virtual void deactivate();
	
	/**
	 * Update the scene
	 * @param orxCLOCK_INFO* clock information provided by Orx
	 * @return next scene to display based on what happens in the update
	 */
	virtual SceneType update(const orxCLOCK_INFO*);

	/**
	 * Gets the current scene's type
	 * @return scene type
	 */
	virtual SceneType getSceneType() = 0;

	/**
	 * Get the next scene to display
	 * @return pointer to next scene
	 */
	Scene* getNextScene();

	virtual orxSTATUS EventHandler(const orxEVENT*);
};

#endif
