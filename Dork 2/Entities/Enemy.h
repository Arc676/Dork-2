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
class Scene;

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
	// constants for generating random enemies
	static const float healthBounds[8];
	static const float speeds[8];
	static const float strengthBounds[8];
	static const float defenseBounds[8];
	static const float rewardBounds[8];
	static const WeaponType preferredWeapons[8];

	EnemyType enemyType;

	/**
	 * Create a random stat
	 * @param base base value for stat
	 * @param scale maximum amount by which the stat could be scaled up from the base
	 * @return random stat based on and scaled from the base stat
	 */
	static int randomStat(int base, float scale);

	// movement and animation data
	orxVECTOR prevPosition;
	orxVECTOR direction;
	orxCHAR animation[40];
	orxFLOAT distanceTravelled = 0;
	orxFLOAT lastDt = 0;
public:
	/**
	 * Get enemy name
	 * @param type type of relevant enemy
	 * @return human readable name for enemy
	 */
	static orxSTRING typeToString(EnemyType type);

	/**
	 * Get the entity type associated with an enemy
	 * @param type the type of enemy
	 * @return the associated entity type
	 */
	static EntityType entityTypeForEnemy(EnemyType type);

	/**
	 * Creates a random enemy
	 * @param type desired enemy type
	 * @param player the current player
	 * @param pos the spawn position of the enemy
	 * @return pointer to the newly spawned enemy
	 */
	static Enemy* createRandomEnemy(EnemyType type, Player* player, orxVECTOR pos);

	/**
	 * Construct new enemy
	 * @param type type of enemy
	 * @param HP enemy's HP on spawn
	 * @param speed enemy's speed stat on spawn
	 * @param str enemy's strength stat on spawn
	 * @param def enemy's defense stat on spawn
	 * @param w weapon with which enemy spawns
	 * @param gold gold carried by enemy
	 * @param lv enemy's level
	 * @param pos enemy's spawn position
	 */
	Enemy(EnemyType type, int HP, int speed, int str, int def, Weapon* w, int gold, Level lv, orxVECTOR pos);

	virtual orxSTRING getName();
	EnemyType getEnemyType();

	/**
	 * Update enemy
	 * @param dt amount of time passed since last update
	 */
	void update(float dt);

	/**
	 * Randomly choose a new direction for the enemy to travel in
	 */
	void newRandomDirection();

	virtual void resumeAnimation();
};

#endif
