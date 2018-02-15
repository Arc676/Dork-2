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

	//potion related functions
	orxBOOL playerHasPotions();
	void consumePotions();
	void selectPotion(int);
	void updatePotionDescription();

	SceneType makeMove(Move);
public:
	Combat(Player*, Enemy*);

	virtual void activate();
	virtual void deactivate();

	virtual SceneType update(const orxCLOCK_INFO*);
	virtual SceneType getSceneType();
};

#endif
