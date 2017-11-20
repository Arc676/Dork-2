//
//  Enemy.cpp
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

#include "Enemy.h"

EnemyType Enemy::getType() {
	return type;
}

std::string Enemy::typeToString(EnemyType type) {
	switch (type) {
		case GOBLIN:
			return "Goblin";
		case GHOST:
			return "Ghost";
		case ORC:
			return "Orc";
		case IMP:
			return "Imp";
		case OGRE:
			return "Ogre";
		case GHOUL:
			return "Ghoul";
		case TROLL:
			return "Troll";
		default:
			return "Unknown enemy type";
	}
}
