//
//  Potion.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 20/11/2017.
///      <alesvinciguerra@gmail.com>
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

#include "Potion.h"

Potion* Potion::quickheal2 = new Potion(QUICKHEAL_2, 2, 5);
Potion* Potion::quickheal5 = new Potion(QUICKHEAL_5, 5, 10);
Potion* Potion::quickheal10 = new Potion(QUICKHEAL_10, 10, 18);
Potion* Potion::quickheal20 = new Potion(QUICKHEAL_20, 20, 35);
Potion* Potion::quickheal50 = new Potion(QUICKHEAL_50, 50, 60);

Potion* Potion::strboost = new Potion(STRBOOST, 1.1, 10);
Potion* Potion::defboost = new Potion(DEFBOOST, 1.1, 15);
Potion* Potion::speedboost = new Potion(SPEEDBOOST, 1.1, 12);

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
		default:
			return nullptr;
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

std::string Potion::getName() {
	return Potion::typeToString(type);
}

std::string Potion::typeToString(PotionType type) {
	switch (type) {
		case QUICKHEAL_2:
			return "Quick heal (2 pts)";
		case QUICKHEAL_5:
			return "Quick heal (5 pts)";
		case QUICKHEAL_10:
			return "Quick heal (10 pts)";
		case QUICKHEAL_20:
			return "Quick heal (20 pts)";
		case QUICKHEAL_50:
			return "Quick heal (50 pts)";
		case SPEEDBOOST:
			return "Speed boost";
		case STRBOOST:
			return "Strength boost";
		case DEFBOOST:
			return "Defense boost";
		default:
			return "Unknown potion type";
	}
}
