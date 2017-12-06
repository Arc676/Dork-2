//
//  Armory.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 26/11/2017.
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

#include "Armory.h"

Armory::Armory(Player* player) : Purchasing() {
	loadPlayerData(player);
	selectorArrow = orxObject_CreateFromConfig("Selector");
	defaultPos = {-1300, 750, 0};
	orxObject_SetPosition(selectorArrow, &defaultPos);
	orxObject_CreateFromConfig("ArmoryHelp");

	tickMarks = std::vector<orxOBJECT*>(WEAPONCOUNT);
	orxVECTOR pos = {-900, 750, 0};
	for (int i = 0; i < WEAPONCOUNT; i++) {
		orxOBJECT* tick = orxObject_CreateFromConfig("TickMark");
		orxObject_SetPosition(tick, &pos);
		orxObject_Enable(tick, player->ownsWeapon((WeaponType)i));
		tickMarks[i] = tick;
		pos.fY += 60;
	}

	statViewer = new StatViewer(player, {-1590, 1000, 0});
	selectionLimit = WEAPONCOUNT;

	setPauseMenuPosition({-1150, 1000, 0});
}

orxBOOL Armory::makePurchase() {
	Weapon* weapon = Weapon::copyOf((WeaponType)currentSelection);
	if (player->getGold() >= weapon->getPrice() && !player->ownsWeapon((WeaponType)currentSelection)) {
		player->transaction(-weapon->getPrice());
		player->setWeaponOwnership((WeaponType)currentSelection, true);
		orxObject_Enable(tickMarks[currentSelection], orxTRUE);
		statViewer->reloadData();
		return orxTRUE;
	}
	return orxFALSE;
}

SceneType Armory::getSceneType() {
	return ARMORY;
}
