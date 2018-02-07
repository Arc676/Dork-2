//
//  Level.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 02/07/2018.
//      <alesvinciguerra@gmail.com>
//Copyright (C) 2018 Arc676/Alessandro Vinciguerra

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

#include "Level.h"

Level::Level(int xp) : xp(xp) {
	level = calculateLevel();
}

void Level::operator=(const Level& lv) {
	xp = lv.xp;
}

int Level::getXP() {
	return xp - orxMath_Pow((double)level / xpFactor, 2);
}

int Level::getTotalXP() {
	return xp;
}

int Level::getLevel() {
	return level;
}

int Level::calculateLevel() {
	return xpFactor * orxMath_Sqrt((double)xp);
}

int Level::getXPToNextLevel(int lv) {
	return orxMath_Pow((lv + 1) / xpFactor, 2);
}

int Level::getXPToNextLevel() {
	return Level::getXPToNextLevel(getLevel()) - xp;
}

int Level::gainXP(Level lv) {
	int prevLv = level;
	xp += 50 * lv.xp / (xp + 100);
	level = calculateLevel();
	return level - prevLv;
}
