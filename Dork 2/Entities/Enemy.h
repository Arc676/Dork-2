//
//  Enemy.h
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 20/11/2017.
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

#ifndef Enemy_h
#define Enemy_h

#include "Entity.h"

class Player;

#define ENEMYCOUNT 7
enum EnemyType {
	GOBLIN,
	GHOST,
	ORC,
	IMP,
	OGRE,
	GHOUL,
	TROLL
};

class Enemy : public Entity {
	static const float healthBounds[8];
	static const float speeds[8];
	static const float strengthBounds[8];
	static const float defenseBounds[8];
	static const float rewardBounds[8];
	static const WeaponType preferredWeapons[8];
	EnemyType enemyType;

	static int randomStat(int, float);

	orxVECTOR direction;
	orxCHAR animation[40];
	orxFLOAT distanceTravelled = 0;
public:
	static orxSTRING typeToString(EnemyType);
	static EntityType entityTypeForEnemy(EnemyType);

	static Enemy* createRandomEnemy(EnemyType, Player*, orxVECTOR);

	Enemy(EnemyType, int, int, int, int, Weapon*, int, Level, orxVECTOR);

	virtual orxSTRING getName();
	EnemyType getEnemyType();

	void update(float);
	void newRandomDirection();
	void resetAnimation();
};

#endif
