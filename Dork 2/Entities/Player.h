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
	 * @param orxSTRING player name
	 * @param EntityType player's entity type
	 */
	Player(orxSTRING, EntityType);
	virtual orxSTRING getName();

	/**
	 * Gets how many potions of a given type the player
	 * owns
	 * @param PotionType type of potion
	 * @return number of owned potions of that type
	 */
	int amountOfPotionOwned(PotionType);

	/**
	 * Alter the amount of a potion owned by the player
	 * @param PotionType relevant potion type
	 * @param int amount by which the owned amount should be changed
	 */
	void changePotionAmount(PotionType, int);

	/**
	 * Get whether the player owns a given weapon
	 * @param WeaponType relevant weapon type
	 * @return whether the player owns that weapon
	 */
	bool ownsWeapon(WeaponType);

	/**
	 * Set whether player owns a given weapon
	 * @param WeaponType relevant weapon type
	 * @param bool whether the player owns the weapon
	 */
	void setWeaponOwnership(WeaponType, bool);

	/**
	 * Defeat an enemy
	 * @param Enemy* defeated enemy
	 */
	void defeat(Enemy*);

	/**
	 * Update player
	 * @param bool up key pressed?
	 * @param bool down key pressed?
	 * @param bool left key pressed?
	 * @param bool right key pressed?
	 * @param float amount of time since last update
	 */
	void update(bool, bool, bool, bool, float);

	/**
	 * Read player data from disk
	 * @param orxSTRING player name
	 * @return whether the read succeeded
	 */
	orxSTATUS read(orxSTRING);

	/**
	 * Write player data to disk
	 * @return whether the write succeeded
	 */
	orxSTATUS write();
};

#endif
