//
//  Enums.h
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

#ifndef Enums_h
#define Enums_h

#define WEAPONCOUNT 7
enum WeaponType : int {
	SWORD = 0,
	CLUB,
	STAFF,
	SICKLE,
	DAGGER,
	AXE,
	SPEAR,
	NOWEAPON
};

enum EntityType : int {
	MAGIC = 0,
	RANGE,
	MELEE,
	SPEED,
	NOTYPE
};

#define POTIONCOUNT 8
enum PotionType {
	QUICKHEAL_2 = 0,
	QUICKHEAL_5,
	QUICKHEAL_10,
	QUICKHEAL_20,
	QUICKHEAL_50,

	SPEEDBOOST,
	STRBOOST,
	DEFBOOST,
};

enum SceneType {
	MAIN_MENU,
	EXPLORATION,
	COMBAT,
	SHOP,
	ARMORY
};

// for use in combat
// represents player choice from UI
enum Move {
	ATTACK,
	SPECIAL_MOVE,
	RUN,
	USE_ITEM
};

#endif
