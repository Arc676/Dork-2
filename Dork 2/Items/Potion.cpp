//
//  Potion.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 20/11/2017.
///      <alesvinciguerra@gmail.com>
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

#include "Potion.h"

std::string Potion::typeToString(PotionType type) {
	switch (type) {
		case QUICKHEAL_2:
			return "Quick heal (2 pts)";
		case QUICKHEAL_5:
			return "Quick heal (5 pts)";
		case QUICKHEAL_10:
			return "Quick heal (10 pts)";
		case QUICKHEAL_20:
			return "Quick heal (20 pts)";
		case QUICKHEAL_50:
			return "Quick heal (50 pts)";
		case SPEEDBOOST:
			return "Speed boost";
		case STRBOOST:
			return "Strength boost";
		case DEFBOOST:
			return "Defense boost";
		default:
			return "Unknown potion type";
	}
}
