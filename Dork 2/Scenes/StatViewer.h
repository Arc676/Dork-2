//
//  StatViewer.h
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 30/11/2017.
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

#ifndef StatViewer_h
#define StatViewer_h

#include "orx.h"

#include "Entity.h"

class StatViewer {
	Entity* entity;

	orxOBJECT* labelName;
	orxOBJECT* labelHP;
	orxOBJECT* labelSpeed;
	orxOBJECT* labelStr;
	orxOBJECT* labelDef;
	orxOBJECT* labelGold;
	orxOBJECT* labelLvl;
	orxOBJECT* labelWeapon;
public:
	StatViewer(Entity*, orxVECTOR);

	void destroy();

	void loadEntity(Entity*);
	void reloadData();
};

#endif
