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

	entity = orxObject_CreateFromConfig(getName().c_str());
	orxVector_Copy(&(this->position), &position);
	orxObject_SetPosition(entity, &position);
	orxObject_SetUserData(entity, this);
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
	double level = orxMath_GetRandomU32(0, 5 * (playerLvl + 1) - 1) / 10 + 0.5 * playerLvl;
	WeaponType weaponOnSpawn = preferredWeapons[type];
	if (orxMath_GetRandomU32(0, 99) < 40) {
		weaponOnSpawn = (WeaponType)orxMath_GetRandomU32(0, WEAPONCOUNT - 1);
	}
	Weapon* weapon = Weapon::copyOf(weaponOnSpawn);
	Enemy* e = new Enemy(
		type,
		orxMath_GetRandomU32(0, healthBounds[(int)type] - 1) + orxMath_GetRandomU32(0, level / 4) + level / 3,
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
	//
}

EnemyType Enemy::getType() {
	return type;
}

EntityType Enemy::getEntityType() {
	return Enemy::entityTypeForEnemy(type);
}

std::string Enemy::getName() {
	return Enemy::typeToString(type);
}

std::string Enemy::typeToString(EnemyType type) {
	switch (type) {
		case GOBLIN:
			return "Goblin";
		case GHOST:
			return "Ghost";
		case ORC:
			return "Orc";
		case IMP:
			return "Imp";
		case OGRE:
			return "Ogre";
		case GHOUL:
			return "Ghoul";
		case TROLL:
			return "Troll";
		default:
			return "Unknown enemy type";
	}
}
