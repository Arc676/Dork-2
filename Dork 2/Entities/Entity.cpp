//
//  Entity.cpp
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

#include "Entity.h"
#include "Weapon.h"

orxBOOL Entity::dodge(Entity* blo, Entity* att) {
	// defending entity must be faster than attacker
	if (blo->getSpeed() < att->getSpeed()) {
		return orxFALSE;
	}
	int lim = 2 * (blo->getSpeed() * (1 + blo->getWeapon()->getSpeedMod()));
	// TODO: this loop is fcking stupid. FIX IT!
	while (lim > 100) lim *= orxMath_GetRandomFloat(1, 9) / 10;
	if (orxMath_GetRandomU32(0, 99) < orxMath_GetRandomU32(0, lim)) {
		return orxTRUE;
	}
	return orxFALSE;
}

int Entity::maxDamage(Entity* attacker, Entity* blocker) {
	// attacks are more or less effective when one entity has a type advantage over the other
	EntityType bweakness = Entity::weaknessForType(blocker->type);
	EntityType aweakness = Entity::weaknessForType(attacker->type);

	int str = attacker->strength;
	int def = blocker->defense;

	if (attacker->type == bweakness) {
		str *= 1.1;
	}
	if (attacker->type == attacker->weapon->getType()) {
		str *= 1.1;
	}
	if (attacker->weapon->getType() == bweakness) {
		str *= 1.2;
	}
	if (blocker->type == aweakness) {
		def *= 1.1;
	}
	if (blocker->type == blocker->weapon->getType()) {
		def *= 1.1;
	}
	if (blocker->weapon->getType() == aweakness) {
		def *= 1.2;
	}
	// strength, boosted by weapon, minus defense, boosted by weapon
	return str * (1 + attacker->weapon->getStrMod()) - (def * (1 + blocker->weapon->getDefMod()))/4;
}

int Entity::entityAttack(Entity* attacker, Entity* blocker) {
	int maxDmg = maxDamage(attacker, blocker);
	if (maxDmg <= 0) {
		maxDmg = 1;
	}
	int damageTaken = orxMath_GetRandomU32(0, maxDmg);
	if (dodge(blocker, attacker)) {
		damageTaken = 0;
	} else {
		blocker->HP -= damageTaken;
	}
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

orxSTRING Entity::typeToString(EntityType type) {
	switch (type) {
		case MAGIC:
			return (orxSTRING)"Magic";
		case RANGE:
			return (orxSTRING)"Range";
		case SPEED:
			return (orxSTRING)"Speed";
		case MELEE:
			return (orxSTRING)"Melee";
		default:
			return (orxSTRING)"No type";
	}
}

Weapon* Entity::getWeapon() {
	return weapon;
}

void Entity::equipWeapon(Weapon* weapon) {
	this->weapon = weapon;
}

orxVECTOR Entity::getPosition() {
	return position;
}

void Entity::setPosition(orxVECTOR pos) {
	orxObject_SetPosition(entity, &pos);
}

void Entity::despawn() {
	orxObject_SetLifeTime(entity, 0);
}

orxOBJECT* Entity::getEntity() {
	return entity;
}

int Entity::getHP() {
	return HP;
}

void Entity::alterHP(int delta) {
	HP += delta;
}

int Entity::getSpeed() {
	return speed;
}

void Entity::alterSpeed(int delta) {
	speed += delta;
}

int Entity::getStrength() {
	return strength;
}

void Entity::alterStrength(int delta) {
	strength += delta;
}

int Entity::getDefense() {
	return defense;
}

void Entity::alterDefense(int delta) {
	defense += delta;
}

int Entity::getGold() {
	return gold;
}

void Entity::transaction(int delta) {
	gold += delta;
}

Level Entity::getLevel() {
	return level;
}

EntityType Entity::getType() {
	return type;
}
