//
//  Entity.hpp
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

#ifndef Entity_h
#define Entity_h

#include "orx.h"
#include "Weapon.h"
#include <string>

class Entity {
protected:
	orxOBJECT* entity;
	orxVECTOR position;

	int HP;
	int speed;
	int strength;
	int defense;
	Weapon* weapon;
	int gold;
	double level;
	EntityType type;
public:
	static int dodge(Entity*, Entity*);
	static int maxDmg(Entity*, Entity*);

	static std::string typeToString(EntityType);
	static EntityType weaknessForType(EntityType);

	virtual std::string getName() = 0;
	int getHP();
	int getSpeed();
	int getStrength();
	int getDefense();
	double getLevel();
	EntityType getType();
	Weapon* getWeapon();
};

#endif
