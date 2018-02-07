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

class Level {
	int level = 0;
	int xp = 0;
public:
	Level(int, int);

	int getLevel();
	int getXP();

	int getXPToNextLevel();
	int gainXP(Level);
};

#endif
