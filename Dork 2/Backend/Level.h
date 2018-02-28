//
//  Level.h
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

#ifndef Level_h
#define Level_h

#include "orx.h"

class Level {
	// scale factor for determining level from XP
	constexpr static const double xpFactor = 0.05;

	// level data
	int level = 0;
	int xp = 0;
public:
	/**
	 * Construct new Level object
	 * @param xp total XP
	 */
	Level(int xp);

	/**
	 * Copy assignment for Level
	 * @param lv level object to copy
	 */
	void operator= (const Level& lv);

	/**
	 * Calculates level associated with current XP level
	 * @return level obtained with current amount of XP
	 */
	int calculateLevel();

	int getLevel();
	int getXP();
	int getTotalXP();

	/**
	 * Calculate XP associated with a given level
	 * @param lv desired level
	 * @return XP level required to reach that level
	 */
	static int getXPToNextLevel(int lv);

	/**
	 * Determine XP required to reach next level
	 * @return XP required for next level
	 */
	int getXPToNextLevel();

	/**
	 * Increases XP level based on Level of a defeated enemy
	 * @param lv enemy level
	 * @return number of levels gained
	 */
	int gainXP(Level lv);
};

#endif
