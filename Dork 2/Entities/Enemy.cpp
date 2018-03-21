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
#include "Scene.h"

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
	orxSTRING strDir = (orxSTRING)"";
	switch (dir) {
		case 0:
			direction = Scene::createVector(1, 0, 0);
			strDir = (orxSTRING)"Right";
			break;
		case 1:
			direction = Scene::createVector(0, 1, 0);
			strDir = (orxSTRING)"Down";
			break;
		case 2:
			direction = Scene::createVector(-1, 0, 0);
			strDir = (orxSTRING)"Left";
			break;
		case 3:
			direction = Scene::createVector(0, -1, 0);
			strDir = (orxSTRING)"Up";
			break;
		default:
			break;
	}
	orxString_Print(animation, "Walk%sAnim%s", strDir, getName());
	resumeAnimation();
	distanceTravelled = 0;
}

void Enemy::resumeAnimation() {
	orxObject_SetTargetAnim(entity, animation);
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

int Enemy::randomStat(int base, float maxMod) {
	return (int)(orxMath_GetRandomFloat(maxMod / 2, maxMod) * base);
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
						 Enemy::randomStat(20 + level * 2, healthBounds[(int)type]),
						 Enemy::randomStat(player->getSpeed(), speeds[(int)type]),
						 Enemy::randomStat(player->getStrength(), strengthBounds[(int)type]),
						 Enemy::randomStat(player->getDefense(), defenseBounds[(int)type]),
						 weapon,
						 orxMath_GetRandomU32(0, rewardBounds[(int)type] * (level + 1)),
						 enemyLvl,
						 pos
						 );
	return e;
}

void Enemy::update(float dt) {
	if (distanceTravelled > 100) {
		newRandomDirection();
	}
	orxObject_GetPosition(entity, &position);
	orxFLOAT distance = orxVector_GetDistance(&position, &prevPosition);
	if (distance < motionSpeed * lastDt * 0.5) {
		newRandomDirection();
	}
	orxVector_Copy(&prevPosition, &position);
	orxVECTOR movement;
	orxVector_Mulf(&movement, &direction, motionSpeed * dt);
	orxVector_Add(&position, &position, &movement);
	orxObject_SetWorldPosition(entity, &position);
	distanceTravelled += orxVector_GetSize(&movement);
	lastDt = dt;
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
