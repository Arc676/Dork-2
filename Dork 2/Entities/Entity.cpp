//
//  Entity.cpp
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

#include "Entity.h"
#include "Weapon.h"

int Entity::dodge(Entity* blo, Entity* att) {
	if (blo->getSpeed() < att->getSpeed()) {
		return 0;
	}
	int lim = 2 * (blo->getSpeed() * (1 + blo->getWeapon()->getSpeedMod()));
	while (lim > 100) lim *= (float)(arc4random_uniform(8) + 1) / 10;
	if (arc4random_uniform(100) < arc4random_uniform(lim)) {
		return 1;
	}
	return 0;
}

int Entity::maxDamage(Entity* attacker, Entity* blocker){
	int str = attacker->strength;
	if (Entity::weaknessForType(blocker->type) == attacker->type) str *= 1.1;
	int def = blocker->defense;
	if (Entity::weaknessForType(attacker->type) == blocker->type) def *= 1.1;
	return str * (1 + attacker->weapon->getStrMod()) - (def * (1 + blocker->weapon->getDefMod()))/4;
}

int Entity::enemyAttacks(Entity* enemy, Entity* player){
	int maxDmg = maxDamage(enemy, player);
	if (maxDmg <= 0) {
		maxDmg = 1;
	}
	int damageTaken = arc4random_uniform(maxDmg);
	if (dodge(player, enemy)) {
		damageTaken = 0;
	}
	player->HP -= damageTaken;
	return damageTaken;
}

EntityType Entity::weaknessForType(EntityType type) {
	switch (type) {
		case MAGIC:
			return SPEED;
		case SPEED:
			return MELEE;
		case RANGE:
			return MAGIC;
		case MELEE:
			return RANGE;
		default:
			return NOTYPE;
	}
}

std::string Entity::typeToString(EntityType type) {
	switch (type) {
		case MAGIC:
			return "Magic";
		case RANGE:
			return "Range";
		case SPEED:
			return "Speed";
		case MELEE:
			return "Melee";
		default:
			return "No type";
	}
}

Weapon* Entity::getWeapon() {
	return weapon;
}

orxVECTOR Entity::getPosition() {
	return position;
}

int Entity::getHP() {
	return HP;
}

int Entity::getSpeed() {
	return speed;
}

int Entity::getStrength() {
	return strength;
}

int Entity::getDefense() {
	return defense;
}

double Entity::getLevel() {
	return level;
}

EntityType Entity::getType() {
	return type;
}
