//
//  Combat.h
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

#ifndef Combat_h
#define Combat_h

#include "Scene.h"
#include "Enemy.h"
#include "Potion.h"
#include "StatViewer.h"

class Combat : public Scene {
	//moves on UI
	static Move moves[2][2];

	//entity-related data
	Enemy* enemy;
	orxVECTOR playerPos;

	//scaling
	static const orxVECTOR scaleUp;
	static const orxVECTOR scaleNormal;

	//combat mechanics and entity stats
	int modifiers[3];
	StatViewer* playerStats;
	StatViewer* enemyStats;

	//UI data
	orxOBJECT* selector;
	orxOBJECT* cui;
	int x = 0, y = 0;
	int specialMoveCooldown = 0;

	//potion related metadata
	orxBOOL hasPotions = false;
	orxBOOL isSelectingPotion = false;
	PotionType selectedPotion = QUICKHEAL_2;
	int desiredQuantity = 1;

	//potion related (UI)
	std::vector<orxOBJECT*> allPotions;
	orxOBJECT* potionName;
	orxOBJECT* potionEffect;
	orxOBJECT* potionHelp;

	/**
	 * Whether the player has any potions to consume
	 * @return Whether the player owns any potions
	 */
	orxBOOL playerHasPotions();

	/**
	 * Consume selected potion
	 */
	void consumePotions();

	/**
	 * Change the potion selection
	 * @param dir Direction for potion switching (+1 for right, -1 for left)
	 */
	void selectPotion(int dir);

	/**
	 * Updates the potion data in the text
	 * fields
	 */
	void updatePotionDescription();

	/**
	 * Make the move selected by the player
	 * @param move Selected move
	 * @return The next scene to show depending on the outcome of the action
	 */
	SceneType makeMove(Move move);
protected:
	virtual void loadUIText(orxSTRING);
	virtual void dismissUIText();
	virtual void loadPlayerData(Player*);
public:
	/**
	 * Construct new combat scene
	 */
	Combat();

	/**
	 * Loads entity data for the given enemy
	 * @param enemy Relevant enemy
	 */
	void loadEnemyData(Enemy* enemy);

	virtual void activate(Player* player);
	virtual void deactivate();

	virtual SceneType update(const orxCLOCK_INFO*);
	virtual SceneType getSceneType();
};

#endif
