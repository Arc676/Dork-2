//
//  Enemy.cpp
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

#include "Enemy.h"
#include "Player.h"

const float Enemy::healthBounds[]   = {0.7, 2, 0.5, 0.8, 1.4, 1, 1.7};
const float Enemy::speeds[]         = {1, 4, 0.5, 1.2, 2, 1.4, 0.3};
const float Enemy::strengthBounds[] = {1, 2.6, 1, 1, 1.7, 1.5, 1.7};
const float Enemy::defenseBounds[]  = {1, 2, 0.6, 0.3, 0.8, 1, 1};
const float Enemy::rewardBounds[]   = {3, 10, 2, 3, 4, 7, 7};

const WeaponType Enemy::preferredWeapons[] = {
	SPEAR,
	DAGGER,
	STAFF,
	SWORD,
	DAGGER,
	SPEAR,
	CLUB
};

Enemy::Enemy(EnemyType type, int HP, int speed, int str, int def, Weapon* w, int gold, Level level, orxVECTOR position) : enemyType(type) {
	this->HP = HP;
	this->speed = speed;
	this->strength = str;
	this->defense = def;
	weapon = w;
	this->gold = gold;
	this->level = level;
	this->type = Enemy::entityTypeForEnemy(type);

	entity = orxObject_CreateFromConfig(getName());
	orxVector_Copy(&(this->position), &position);
	orxObject_SetPosition(entity, &position);
	orxObject_SetUserData(entity, this);

	newRandomDirection();
}

void Enemy::newRandomDirection() {
	int dir = orxMath_GetRandomS32(0, 3);
	orxCHAR anim[30];
	orxSTRING strDir = (orxSTRING)"";
	switch (dir) {
		case 0:
			direction = {1, 0, 0};
			strDir = (orxSTRING)"Right";
			break;
		case 1:
			direction = {0, 1, 0};
			strDir = (orxSTRING)"Down";
			break;
		case 2:
			direction = {-1, 0, 0};
			strDir = (orxSTRING)"Left";
			break;
		case 3:
			direction = {0, -1, 0};
			strDir = (orxSTRING)"Up";
			break;
		default:
			break;
	}
	orxString_Print(anim, "Walk%sAnim%s", strDir, getName());
	orxObject_SetTargetAnim(entity, anim);
}

EntityType Enemy::entityTypeForEnemy(EnemyType type) {
	switch (type) {
		case GOBLIN:
			return RANGE;
		case GHOST:
			return SPEED;
		case ORC:
			return MAGIC;
		case IMP:
			return MELEE;
		case OGRE:
			return SPEED;
		case GHOUL:
			return RANGE;
		case TROLL:
			return MELEE;
		default:
			return NOTYPE;
	}
}

Enemy* Enemy::createRandomEnemy(EnemyType type, Player* player, orxVECTOR pos) {
	int playerXP = player->getLevel().getTotalXP();
	Level enemyLvl = Level(
						orxMath_GetRandomU32(playerXP / 2, 4 * (playerXP + 100))
						);
	double level = (double)enemyLvl.getLevel();
	WeaponType weaponOnSpawn = preferredWeapons[type];
	if (orxMath_GetRandomU32(0, 99) < 40) {
		weaponOnSpawn = (WeaponType)orxMath_GetRandomU32(0, WEAPONCOUNT - 1);
	}
	Weapon* weapon = Weapon::copyOf(weaponOnSpawn);
	Enemy* e = new Enemy(
		type,
		orxMath_GetRandomU32(1, healthBounds[(int)type] - 1) + orxMath_GetRandomU32(0, level / 4) + level / 3,
		orxMath_GetRandomU32(0, speeds[(int)type] - 1) + level * 0.5,
		orxMath_GetRandomU32(0, strengthBounds[(int)type] - 1) + level * 0.6,
		orxMath_GetRandomU32(0, defenseBounds[(int)type] - 1) + level * 0.6,
		weapon,
		orxMath_GetRandomU32(0, rewardBounds[(int)type] - 1) + level * 0.5,
		enemyLvl,
		pos
	);
	return e;
}

void Enemy::update(float dt) {
	if (distanceTravelled > 100) {
		newRandomDirection();
		distanceTravelled = 0;
	}
	orxObject_GetPosition(entity, &position);
	orxVECTOR movement;
	orxVector_Mulf(&movement, &direction, motionSpeed * dt);
	orxVector_Add(&position, &position, &movement);
	orxObject_SetWorldPosition(entity, &position);
	distanceTravelled += orxVector_GetSize(&movement);
}

EnemyType Enemy::getEnemyType() {
	return enemyType;
}

orxSTRING Enemy::getName() {
	return Enemy::typeToString(enemyType);
}

orxSTRING Enemy::typeToString(EnemyType type) {
	switch (type) {
		case GOBLIN:
			return (orxSTRING)"Goblin";
		case GHOST:
			return (orxSTRING)"Ghost";
		case ORC:
			return (orxSTRING)"Orc";
		case IMP:
			return (orxSTRING)"Imp";
		case OGRE:
			return (orxSTRING)"Ogre";
		case GHOUL:
			return (orxSTRING)"Ghoul";
		case TROLL:
			return (orxSTRING)"Troll";
		default:
			return (orxSTRING)"Unknown enemy type";
	}
}
