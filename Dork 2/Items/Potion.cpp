//
//  Potion.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 20/11/2017.
///      <alesvinciguerra@gmail.com>
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

#include "Potion.h"

Potion* Potion::quickheal2 = new Potion(QUICKHEAL_2, 2, 5);
Potion* Potion::quickheal5 = new Potion(QUICKHEAL_5, 5, 10);
Potion* Potion::quickheal10 = new Potion(QUICKHEAL_10, 10, 18);
Potion* Potion::quickheal20 = new Potion(QUICKHEAL_20, 20, 35);
Potion* Potion::quickheal50 = new Potion(QUICKHEAL_50, 50, 60);

Potion* Potion::strboost = new Potion(STRBOOST, 0.1, 10);
Potion* Potion::defboost = new Potion(DEFBOOST, 0.1, 15);
Potion* Potion::speedboost = new Potion(SPEEDBOOST, 0.1, 12);

std::vector<Potion*> Potion::allPotions = {
	quickheal2,
	quickheal5,
	quickheal10,
	quickheal20,
	quickheal50,
	speedboost,
	strboost,
	defboost
};

Potion* Potion::getCopyOf(PotionType type) {
	switch (type) {
		case QUICKHEAL_2:
			return quickheal2->copy();
		case QUICKHEAL_5:
			return quickheal5->copy();
		case QUICKHEAL_10:
			return quickheal10->copy();
		case QUICKHEAL_20:
			return quickheal20->copy();
		case QUICKHEAL_50:
			return quickheal50->copy();
		case DEFBOOST:
			return defboost->copy();
		case SPEEDBOOST:
			return speedboost->copy();
		case STRBOOST:
			return strboost->copy();
		default:
			return orxNULL;
	}
}

Potion* Potion::copy() {
	return new Potion(type, amount, price);
}

Potion::Potion(PotionType type, double amt, int price) : type(type), amount(amt), price(price) {}

double Potion::getAmount() {
	return amount;
}

int Potion::getPrice() {
	return price;
}

PotionType Potion::getType() {
	return type;
}

orxSTRING Potion::getName() {
	return Potion::typeToString(type);
}

orxSTRING Potion::typeToString(PotionType type) {
	switch (type) {
		case QUICKHEAL_2:
		case QUICKHEAL_5:
		case QUICKHEAL_10:
		case QUICKHEAL_20:
		case QUICKHEAL_50:
			return (orxSTRING)"Quick heal";
		case SPEEDBOOST:
			return (orxSTRING)"Speed boost";
		case STRBOOST:
			return (orxSTRING)"Strength boost";
		case DEFBOOST:
			return (orxSTRING)"Defense boost";
		default:
			return (orxSTRING)"Unknown potion type";
	}
}

orxSTRING Potion::configCodeForType(PotionType type) {
	switch (type) {
		case QUICKHEAL_2:
			return (orxSTRING)"qh2";
		case QUICKHEAL_5:
			return (orxSTRING)"qh5";
		case QUICKHEAL_10:
			return (orxSTRING)"qh10";
		case QUICKHEAL_20:
			return (orxSTRING)"qh20";
		case QUICKHEAL_50:
			return (orxSTRING)"qh50";
		case SPEEDBOOST:
			return (orxSTRING)"SpeedBoost";
		case STRBOOST:
			return (orxSTRING)"StrengthBoost";
		case DEFBOOST:
			return (orxSTRING)"DefenseBoost";
		default:
			return (orxSTRING)"";
	}
}
