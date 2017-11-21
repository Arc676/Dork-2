//
//  Player.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 21/11/2017.
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

#include "Player.h"

Player::Player(const std::string& name, EntityType type) : name(name) {
	this->type = type;
	HP = 30;
	speed = 10;
	strength = 15;
	defense = 15;

	entity = orxObject_CreateFromConfig("Player");
	orxObject_GetPosition(entity, &position);

	ownedPotions = std::vector<int>(POTIONCOUNT);
	ownedWeapons = std::vector<bool>(WEAPONCOUNT);
}

std::string Player::getName() {
	return name;
}
