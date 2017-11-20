//
//  Weapon.cpp
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

#include "Weapon.h"

Weapon* Weapon::sword = new Weapon(
	SWORD, 0.4, 0.4, 0, 700
);
Weapon* Weapon::club = new Weapon(
	CLUB, 0.15, 0.15, -0.05, 100
);
Weapon* Weapon::scythe = new Weapon(
	SCYTHE, 0.5, 0.3, -0.05, 1000
);
Weapon* Weapon::sickle = new Weapon(
	SICKLE, 0.4, 0.2, 0, 400
);
Weapon* Weapon::axe = new Weapon(
	AXE, 0.3, 0.1, -0.05, 600
);
Weapon* Weapon::dagger = new Weapon(
	DAGGER, 0.3, 0.15, 0.05, 200
);
Weapon* Weapon::lance = new Weapon(
	LANCE, 0.4, 0.1, -0.1, 700
);

Weapon::Weapon(WeaponType weaponType, double str, double def, double speed, int price) : weapon(weaponType), strMod(str), defMod(def), speedMod(speed), price(price) {}

std::string Weapon::getWeaponName(WeaponType type) {
	switch (type) {
		case SWORD:
			return "Sword";
		case CLUB:
			return "Club";
		case SCYTHE:
			return "Scythe";
		case SICKLE:
			return "Sickle";
		case DAGGER:
			return "Dagger";
		case AXE:
			return "Axe";
		case LANCE:
			return "Lance";
		default:
			return "Unknown weapon";
	}
}

EntityType Weapon::getTypeForWeapon(WeaponType weaponType) {
	switch (weaponType) {
		case SWORD:
			return MELEE;
		case CLUB:
			return MELEE;
		case SCYTHE:
			return MELEE;
		case SICKLE:
			return MELEE;
		case DAGGER:
			return SPEED;
		case AXE:
			return MELEE;
		case LANCE:
			return RANGE;
		default:
			return NOTYPE;
	}
}

Weapon* Weapon::copy() {
	return new Weapon(weapon, strMod, defMod, speedMod, price);
}

Weapon* Weapon::copyOf(WeaponType type) {
	switch (type) {
		case SWORD:
			return Weapon::sword->copy();
		default:
			return nullptr;
	}
}

std::string Weapon::getName() {
	return Weapon::getWeaponName(weapon);
}

double Weapon::getStrMod() {
	return strMod;
}

double Weapon::getDefMod() {
	return defMod;
}

double Weapon::getSpeedMod() {
	return speedMod;
}

int Weapon::getPrice() {
	return price;
}

EntityType Weapon::getType() {
	return Weapon::getTypeForWeapon(weapon);
}
