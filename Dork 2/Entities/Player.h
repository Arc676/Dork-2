//
//  Player.h
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 21/11/2017.
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

#ifndef Player_h
#define Player_h

#include <vector>

#include "Entity.h"
#include "Enemy.h"

class Scene;

class Player : public Entity {
	std::vector<int> ownedPotions;
	std::vector<bool> ownedWeapons;
	orxSTRING name;

	/**
	 * Section filter for persistence (see Orx docs)
	 */
	static orxBOOL sectionFilter(const orxSTRING, const orxSTRING, const orxSTRING, orxBOOL);
public:
	/**
	 * Construct new player
	 * @param name player name
	 * @param type player's entity type
	 */
	Player(orxSTRING name, EntityType type);
	virtual orxSTRING getName();

	/**
	 * Gets how many potions of a given type the player
	 * owns
	 * @param type type of potion
	 * @return number of owned potions of that type
	 */
	int amountOfPotionOwned(PotionType type);

	/**
	 * Alter the amount of a potion owned by the player
	 * @param type relevant potion type
	 * @param delta amount by which the owned amount should be changed
	 */
	void changePotionAmount(PotionType type, int delta);

	/**
	 * Get whether the player owns a given weapon
	 * @param type relevant weapon type
	 * @return whether the player owns that weapon
	 */
	bool ownsWeapon(WeaponType type);

	/**
	 * Set whether player owns a given weapon
	 * @param type relevant weapon type
	 * @param ownership whether the player owns the weapon
	 */
	void setWeaponOwnership(WeaponType type, bool ownership);

	/**
	 * Defeat an enemy
	 * @param e defeated enemy
	 */
	void defeat(Enemy* e);

	/**
	 * Update player
	 * @param u up key pressed?
	 * @param d down key pressed?
	 * @param l left key pressed?
	 * @param r right key pressed?
	 * @param dt amount of time since last update
	 */
	void update(bool u, bool d, bool l, bool r, float dt);

	/**
	 * Read player data from disk
	 * @param name player name
	 * @return whether the read succeeded
	 */
	orxSTATUS read(orxSTRING name);

	/**
	 * Write player data to disk
	 * @return whether the write succeeded
	 */
	orxSTATUS write();

	virtual void resumeAnimation();
};

#endif
