//
//  Enums.h
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

#ifndef Enums_h
#define Enums_h

#define WEAPONCOUNT 7
enum WeaponType {
	SWORD,
	CLUB,
	SCYTHE,
	SICKLE,
	DAGGER,
	AXE,
	LANCE
};

enum EntityType {
	MAGIC,
	RANGE,
	MELEE,
	SPEED,
	NOTYPE
};

#define POTIONCOUNT 8
enum PotionType {//potion save codes in comments
	QUICKHEAL_2, //0
	QUICKHEAL_5, //1
	QUICKHEAL_10, //2
	QUICKHEAL_20, //3
	QUICKHEAL_50, //4

	SPEEDBOOST, //5
	STRBOOST, //6
	DEFBOOST, //7; designated last item
};

#endif
