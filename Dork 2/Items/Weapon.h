//
//  Weapon.h
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 20/11/2017.
//      <alesvinciguerra@gmail.com>
//Copyright (C) 2017-8 Arc676/Alessandro Vinciguerra
//  Edited by Tyrel Clayton on 10/06/2018
//Copyright (C) 2018 Tyresius92/Tyrel Clayton

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
	static Weapon* sickle;
	static Weapon* axe;
	static Weapon* dagger;
	static Weapon* rapier; 
	static Weapon* sai; 
	static Weapon* whip; 
	static Weapon* spear;
	static Weapon* bow; 
	static Weapon* crossbow; 
	static Weapon* boomerang; 
	static Weapon* orb; 
	static Weapon* tome; 
	static Weapon* staff;
	static Weapon* relic; 

	static Weapon* noWeapon;

	/**
	 * Copy a weapon
	 * @return A new Weapon pointer with the same properties
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
	 * @param type The kind of weapon
	 * @return Human readable name for the weapon
	 */
	static orxSTRING getWeaponName(WeaponType type);

	/**
	 * Get a copy of a weapon
	 * @param type Desired weapon type
	 * @return Copy of weapon with the desired type
	 */
	static Weapon* copyOf(WeaponType type);

	/**
	 * Get entity type associated with a given weapon
	 * @param type Type of weapon
	 * @return The associated entity type
	 */
	static EntityType getTypeForWeapon(WeaponType type);

	/**
	 * Construct a new weapon
	 * @param type Type of weapon
	 * @param str Strength modifier
	 * @param def Defense modifier
	 * @param speed Speed modifier
	 * @param price Weapon price
	 */
	Weapon(WeaponType type, double str, double def, double speed, int price);

	orxSTRING getName();
	double getStrMod();
	double getDefMod();
	double getSpeedMod();
	int getPrice();
	EntityType getType();
	WeaponType getWeaponType();
};

#endif
