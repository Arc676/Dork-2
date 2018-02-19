//
//  Weapon.h
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

#ifndef Weapon_h
#define Weapon_h

#include "orx.h"
#include <vector>

#include "Enums.h"

class Weapon {
	// static instances of each weapon
	static Weapon* sword;
	static Weapon* club;
	static Weapon* staff;
	static Weapon* sickle;
	static Weapon* axe;
	static Weapon* dagger;
	static Weapon* spear;

	static Weapon* noWeapon;

	/**
	 * Copy a weapon
	 * @return a new Weapon pointer with the same properties
	 */
	Weapon* copy();

	// weapon properties
	double strMod;
	double defMod;
	double speedMod;
	int price;
	WeaponType weapon;
public:
	// all weapons
	static std::vector<Weapon*> allWeapons;
	
	/**
	 * Get name of weapon
	 * @param WeaponType the kind of weapon
	 * @return human readable name for the weapon
	 */
	static orxSTRING getWeaponName(WeaponType);

	/**
	 * Get a copy of a weapon
	 * @param WeaponType desired weapon type
	 * @return copy of weapon with the desired type
	 */
	static Weapon* copyOf(WeaponType);

	/**
	 * Get entity type associated with a given weapon
	 * @param WeaponType type of weapon
	 * @return the associated entity type
	 */
	static EntityType getTypeForWeapon(WeaponType);

	/**
	 * Construct a new weapon
	 * @param WeaponType type of weapon
	 * @param double strength modifier
	 * @param double defense modifier
	 * @param double speed modifier
	 * @param int weapon price
	 */
	Weapon(WeaponType, double, double, double, int);

	orxSTRING getName();
	double getStrMod();
	double getDefMod();
	double getSpeedMod();
	int getPrice();
	EntityType getType();
	WeaponType getWeaponType();
};

#endif
