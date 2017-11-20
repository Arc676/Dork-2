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

Enemy::Enemy(EnemyType type, int HP, int speed, int str, int def, Weapon* w, int gold, double level) : type(type) {
	this->HP = HP;
	this->speed = speed;
	this->strength = str;
	this->defense = def;
	weapon = w;
	this->gold = gold;
	this->level = level;
}

Enemy* Enemy::createRandomEnemy(EnemyType type, double playerLvl) {
	double level = (double)arc4random_uniform(5 * (playerLvl + 1)) / 10 + 0.5 * playerLvl;
	WeaponType weaponOnSpawn = preferredWeapons[type];
	if (arc4random_uniform(100) < 40) {
		weaponOnSpawn = (WeaponType)arc4random_uniform(WEAPONCOUNT);
	}
	Weapon* weapon = Weapon::copyOf(weaponOnSpawn);
	Enemy* e = new Enemy(
		type,
		arc4random_uniform(healthBounds[(int)type]) + arc4random_uniform(level / 4) + level / 3,
		arc4random_uniform(speeds[(int)type]/2 + level/2) + speeds[(int)type],
		arc4random_uniform(strengthBounds[(int)type]) + level * 0.6,
		arc4random_uniform(defenseBounds[(int)type]) + level * 0.6,
		weapon,
		arc4random_uniform(rewardBounds[(int)type]) + level * 0.5,
		level
	);
	return e;
}

EnemyType Enemy::getType() {
	return type;
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
