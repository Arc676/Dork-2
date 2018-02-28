//
//  Potion.h
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

#ifndef Potion_h
#define Potion_h

#include "orx.h"
#include <vector>

#include "Enums.h"

class Potion {
	// static instances of each potion
	static Potion* quickheal2;
	static Potion* quickheal5;
	static Potion* quickheal10;
	static Potion* quickheal20;
	static Potion* quickheal50;

	static Potion* strboost;
	static Potion* defboost;
	static Potion* speedboost;

	/**
	 * Obtains the name of a potion
	 * @param type relevant potion type
	 * @return Human readable potion name
	 */
	static orxSTRING typeToString(PotionType type);

	// potion data
	int price;
	PotionType type;
	double amount;

	/**
	 * Copy a potion
	 * @return a new Potion pointer with the same properties
	 */
	Potion* copy();
public:
	// all the potions
	static std::vector<Potion*> allPotions;
	
	/**
	 * Construct a new potion
	 * @param type potion type
	 * @param effect amount by which the relevant stat is improved
	 * @param price potion price
	 */
	Potion(PotionType type, double effect, int price);

	int getPrice();
	double getAmount();
	PotionType getType();
	orxSTRING getName();

	/**
	 * Get the abbreviation used in config for a given potion type
	 * @param type relevant potion type
	 * @return abbreviation used to represent potion in config files
	 */
	static orxSTRING configCodeForType(PotionType type);

	/**
	 * Get a copy of a given potion
	 * @param type desired potion type
	 * @return a copy of the desired potion
	 */
	static Potion* getCopyOf(PotionType type);
};

#endif
