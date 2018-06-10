//
//  Weapon.cpp
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

#include "Weapon.h"

Weapon* Weapon::sword = new Weapon(
	SWORD, 0.7, 0.35, 0, 200
);
Weapon* Weapon::club = new Weapon(
	CLUB, 0.15, 0.15, -0.05, 10
);
Weapon* Weapon::sickle = new Weapon(
	SICKLE, 0.3, 0.2, 0, 60
);
Weapon* Weapon::axe = new Weapon(
	AXE, 0.3, 0.1, -0.05, 50
);
Weapon* Weapon::dagger = new Weapon(
	DAGGER, 0.25, 0.15, 0.05, 40
);
Weapon* Weapon::rapier = new Weapon(
	RAPIER, 0.4, 0.25, 0.05, 175
);
Weapon* Weapon::sai = new Weapon(
	SAI, 0.2, 0.2, 0.1, 100
);
Weapon* Weapon::whip = new Weapon(
	WHIP, 0.3, 0.1, 0.05, 60
);
Weapon* Weapon::spear = new Weapon(
	SPEAR, 0.4, 0.1, -0.2, 35
);
Weapon* Weapon::bow = new Weapon(
	BOW, 0.15, 0.2, 0, 50
);
Weapon* Weapon::crossbow = new Weapon(
	CROSSBOW, 0.5, 0.2, -0.05, 100
);
Weapon* Weapon::boomerang = new Weapon(
	BOOMERANG, 0.3, 0.2, 0, 125
);
Weapon* Weapon::orb = new Weapon(
	ORB, 0.3, 0.2, 0, 70
);
Weapon* Weapon::tome = new Weapon(
	TOME, 0.4, 0.3, 0.05, 100
);
Weapon* Weapon::staff = new Weapon(
	STAFF, 0.6, 0.4, -0.05, 150
);
Weapon* Weapon::relic = new Weapon(
	RELIC, 0.2, 0.1, 0, 40
);

std::vector<Weapon*> Weapon::allWeapons = {
	sword,
	club,
	sickle,
	axe,
	dagger,
	rapier, 
	sai, 
	whip, 
	spear, 
	bow, 
	crossbow, 
	boomerang,
	orb, 
	tome,
	staff, 
	relic
};

Weapon* Weapon::noWeapon = new Weapon(
	NOWEAPON, 0, 0, 0, 0
);

Weapon::Weapon(WeaponType weaponType, double str, double def, double speed, int price) : weapon(weaponType), strMod(str), defMod(def), speedMod(speed), price(price) {}

orxSTRING Weapon::getWeaponName(WeaponType type) {
	switch (type) {
		case SWORD:
			return (orxSTRING)"Sword";
		case CLUB:
			return (orxSTRING)"Club";
		case SICKLE:
			return (orxSTRING)"Sickle";
		case AXE:
			return (orxSTRING)"Axe";
		case DAGGER:
			return (orxSTRING)"Dagger";
		case RAPIER:
			return (orxSTRING)"Rapier";
		case SAI:
			return (orxSTRING)"Sai";
		case WHIP: 
			return (orxSTRING)"Whip";
		case SPEAR:
			return (orxSTRING)"Spear";
		case BOW: 
			return (orxSTRING)"Bow";
		case CROSSBOW:
			return (orxSTRING)"Crossbow"; 
		case BOOMERANG:
			return (orxSTRING)"Boomerang";
		case ORB:
			return (orxSTRING)"Orb";
		case TOME: 
			return (orxSTRING)"Tome"; 
		case STAFF:
			return (orxSTRING)"Staff";
		case RELIC: 
			return (orxSTRING)"Relic"; 
		case NOWEAPON:
			return (orxSTRING)"No weapon";
		default:
			return (orxSTRING)"Unknown weapon";
	}
}

EntityType Weapon::getTypeForWeapon(WeaponType weaponType) {
	switch (weaponType) {
		case SWORD:
		case CLUB:
		case SICKLE:
		case AXE:
			return MELEE;
		case DAGGER:
		case RAPIER:
		case SAI:
		case WHIP:
			return SPEED;
		case SPEAR:
		case BOW: 
		case CROSSBOW:
		case BOOMERANG: 
			return RANGE;
		case ORB:
		case TOME:
		case STAFF:
		case RELIC:
			return MAGIC;
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
		case CLUB:
			return Weapon::club->copy();
		case SICKLE:
			return Weapon::sickle->copy();
		case AXE:
			return Weapon::axe->copy();
		case DAGGER:
			return Weapon::dagger->copy();
		case RAPIER: 
			return Weapon::rapier->copy();
		case SAI: 
			return Weapon::sai->copy();
		case WHIP: 
			return Weapon::whip->copy();
		case SPEAR:
			return Weapon::spear->copy();
		case BOW:
			return Weapon::bow->copy();
		case CROSSBOW: 
			return Weapon::crossbow->copy();
		case BOOMERANG:
			return Weapon::boomerang->copy();
		case ORB:
			return Weapon::orb->copy();
		case TOME:
			return Weapon::tome->copy(); 
		case STAFF:
			return Weapon::staff->copy();
		case RELIC: 
			return Weapon::relic->copy();
		default:
			return Weapon::noWeapon->copy();
	}
}

orxSTRING Weapon::getName() {
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

WeaponType Weapon::getWeaponType() {
	return weapon;
}

EntityType Weapon::getType() {
	return Weapon::getTypeForWeapon(weapon);
}
