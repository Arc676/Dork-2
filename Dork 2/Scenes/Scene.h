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
protected:
	// UI text objects
	orxBOOL hasText = orxFALSE;
	orxOBJECT* uiTextObject = orxNULL;
	orxOBJECT* uiTextSprite = orxNULL;
	static const orxVECTOR textMargin;

	// scene data
	Player* player = orxNULL;
	orxBOOL canSave = orxFALSE;
	SceneType nextSceneType;

	// music settings
	static orxBOOL playMusic;
	orxSOUND* music = orxNULL;

	/**
	 * Gets whether a key was pressed while only
	 * triggering on the first key down event
	 * @param key Desired key
	 * @return Whether the key has been pressed (only first key down)
	 */
	static orxBOOL getKeyDown(orxSTRING key);

	/**
	 * Load text to display in mini alert
	 * @param text Text to display
	 */
	virtual void loadUIText(orxSTRING text);

	/**
	 * Dismiss the alert
	 */
	virtual void dismissUIText();

	/**
	 * Initializes UI text objects
	 * @param pos Render position for alerts
	 */
	void initializeUITextAt(orxVECTOR pos);

	/**
	 * Move the UI text objects
	 * @param pos New render position for alerts
	 */
	void moveUITextTo(orxVECTOR pos);

	orxBOOL paused = orxFALSE;
	int pauseMenuSelection = 0;

	/**
	 * Set location of pause menu in world space
	 * @param pos New position for pause menu
	 */
	void setPauseMenuPosition(orxVECTOR pos);

	/**
	 * Load a new player
	 * @param player Player to load into scene
	 */
	virtual void loadPlayerData(Player* player);

	/**
	 * Toggles whether music should be played
	 */
	void toggleMusic();

	Scene();
public:
	/**
	 * Get the currently loaded player
	 * @return Loaded player
	 */
	Player* getPlayerData();

	/**
	 * Tells the scene that it is now the active
	 * scene
	 * @param player Player data to load on activation
	 */
	virtual void activate(Player* player);

	/**
	 * Tells the scene that it is no longer
	 * the active scene
	 */
	virtual void deactivate();
	
	/**
	 * Update the scene
	 * @param clockInfo Clock information provided by Orx
	 * @return Next scene to display based on what happens in the update
	 */
	virtual SceneType update(const orxCLOCK_INFO* clockInfo);

	/**
	 * Gets the current scene's type
	 * @return scene type
	 */
	virtual SceneType getSceneType() = 0;

	/**
	 * Utility function to create a vector
	 * @param x X component
	 * @param y Y component
	 * @param z Z component
	 * @return A vector with the given Cartesian components
	 */
	static orxVECTOR createVector(orxFLOAT x, orxFLOAT y, orxFLOAT z);

	virtual orxSTATUS EventHandler(const orxEVENT*);
};

#endif
