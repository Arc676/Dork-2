//
//  Enemy.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 20/11/2017.
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

#include "Enemy.h"

const int Enemy::healthBounds[]   = {20, 60, 10, 24, 40, 30, 50};
const int Enemy::speeds[]         = {10, 40, 4,  12, 20, 14, 2};
const int Enemy::strengthBounds[] = {15, 40, 15, 15, 25, 22, 25};
const int Enemy::defenseBounds[]  = {15, 30, 10, 5,  12, 15, 15};
const int Enemy::rewardBounds[]   = {3,  10, 2,  3,  4,  7,  7};

const WeaponType Enemy::preferredWeapons[] = {
	LANCE,
	DAGGER,
	AXE,
	SWORD,
	DAGGER,
	LANCE,
	CLUB
};

Enemy::Enemy(EnemyType type, int HP, int speed, int str, int def, Weapon* w, int gold, double level, orxVECTOR position) : type(type) {
	this->HP = HP;
	this->speed = speed;
	this->strength = str;
	this->defense = def;
	weapon = w;
	this->gold = gold;
	this->level = level;

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
			return MAGIC;
		case GHOST:
			return SPEED;
		case ORC:
			return RANGE;
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

Enemy* Enemy::createRandomEnemy(EnemyType type, double playerLvl, orxVECTOR pos) {
	double level = orxMath_GetRandomFloat(0, 5 * (playerLvl + 1) - 2) / 10 + 0.5 * playerLvl;
	WeaponType weaponOnSpawn = preferredWeapons[type];
	if (orxMath_GetRandomU32(0, 99) < 40) {
		weaponOnSpawn = (WeaponType)orxMath_GetRandomU32(0, WEAPONCOUNT - 1);
	}
	Weapon* weapon = Weapon::copyOf(weaponOnSpawn);
	Enemy* e = new Enemy(
		type,
		orxMath_GetRandomU32(1, healthBounds[(int)type] - 1) + orxMath_GetRandomU32(0, level / 4) + level / 3,
		orxMath_GetRandomU32(0, speeds[(int)type]/2 + level/2 - 1) + speeds[(int)type],
		orxMath_GetRandomU32(0, strengthBounds[(int)type] - 1) + level * 0.6,
		orxMath_GetRandomU32(0, defenseBounds[(int)type] - 1) + level * 0.6,
		weapon,
		orxMath_GetRandomU32(0, rewardBounds[(int)type] - 1) + level * 0.5,
		level,
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

EnemyType Enemy::getType() {
	return type;
}

EntityType Enemy::getEntityType() {
	return Enemy::entityTypeForEnemy(type);
}

orxSTRING Enemy::getName() {
	return Enemy::typeToString(type);
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
