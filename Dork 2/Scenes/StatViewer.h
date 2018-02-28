//
//  StatViewer.h
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 30/11/2017.
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

#ifndef StatViewer_h
#define StatViewer_h

#include "orx.h"

#include "Entity.h"

class StatViewer {
	// entity whose stats are being shown
	Entity* entity;

	// text fields
	orxOBJECT* labelName;
	orxOBJECT* labelType;
	orxOBJECT* labelHP;
	orxOBJECT* labelSpeed;
	orxOBJECT* labelStr;
	orxOBJECT* labelDef;
	orxOBJECT* labelGold;
	orxOBJECT* labelLvl;
	orxOBJECT* labelWeapon;
public:
	/**
	 * Construct new StatViewer
	 * @param entity entity whose stats to show
	 * @param pos render position of stat viewer
	 */
	StatViewer(Entity* entity, orxVECTOR pos);

	/**
	 * Destroy the stat viewer and all
	 * child objects
	 */
	void destroy();

	/**
	 * Load stats for a new entity
	 * @param entity entity whose stats to load
	 */
	void loadEntity(Entity* entity);

	/**
	 * Refreshes the entity's stats in the
	 * text fields
	 */
	void reloadData();
};

#endif
