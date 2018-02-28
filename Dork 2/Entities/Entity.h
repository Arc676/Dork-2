//
//  Entity.h
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

#ifndef Entity_h
#define Entity_h

#include "orx.h"
#include "Weapon.h"
#include "Level.h"

class Entity {
protected:
	// entity data (in world)
	orxOBJECT* entity;
	orxVECTOR position;

	const int motionSpeed = 60;

	// entity data (in backend)
	int HP;
	int speed;
	int strength;
	int defense;
	Weapon* weapon = Weapon::copyOf(NOWEAPON);
	int gold = 0;
	Level level = Level(0);
	EntityType type;
public:
	/**
	 * Randomly choose whether an entity can dodge another
	 * based on stats
	 * @param att attacking entity
	 * @param blo blocking entity
	 * @return whether the blocker successfully dodges the attacker
	 */
	static orxBOOL dodge(Entity* att, Entity* blo);

	/**
	 * Calculate maximum possible damage that can be dealt based
	 * on entity stats and weapons
	 * @param att attacking entity
	 * @param blo blocking entity
	 * @return maximum damage that can be dealt in one turn
	 */
	static int maxDamage(Entity* att, Entity* blo);

	/**
	 * Apply effects of an attack
	 * @param att attacking entity
	 * @param blo blocking entity
	 * @return damage dealt by attacker
	 */
	static int entityAttack(Entity* att, Entity* blo);

	/**
	 * Get name of entity type
	 * @param type relevant type
	 * @return human readable form of entity type
	 */
	static orxSTRING typeToString(EntityType type);

	/**
	 * Get a given entity type's weakness
	 * @param type relevant type
	 * @return entity type that is effective against that type
	 */
	static EntityType weaknessForType(EntityType type);

	/**
	 * Attempt to resume the entity's animation
	 */
	virtual void resumeAnimation() = 0;

	/**
	 * Pauses the entity's animation
	 */
	virtual void pauseAnimation();

	orxVECTOR getPosition();
	void setPosition(orxVECTOR);
	void despawn();

	virtual orxSTRING getName() = 0;

	orxOBJECT* getEntity();

	int getHP();
	void alterHP(int);

	int getSpeed();
	void alterSpeed(int);

	int getStrength();
	void alterStrength(int);

	int getDefense();
	void alterDefense(int);

	int getGold();
	void transaction(int);

	Level getLevel();

	EntityType getType();
	Weapon* getWeapon();
	void equipWeapon(Weapon*);
};

#endif
