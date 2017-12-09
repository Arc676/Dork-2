//
//  Potion.h
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

#ifndef Potion_h
#define Potion_h

#include "orx.h"
#include <vector>

#include "Enums.h"

class Potion {
	static Potion* quickheal2;
	static Potion* quickheal5;
	static Potion* quickheal10;
	static Potion* quickheal20;
	static Potion* quickheal50;

	static Potion* strboost;
	static Potion* defboost;
	static Potion* speedboost;

	static orxSTRING typeToString(PotionType);

	int price;
	PotionType type;
	double amount;

	Potion* copy();
public:
	static std::vector<Potion*> allPotions;
	
	Potion(PotionType, double, int);

	int getPrice();
	double getAmount();
	PotionType getType();
	orxSTRING getName();

	static orxSTRING configCodeForType(PotionType);

	static Potion* getCopyOf(PotionType);
};

#endif
