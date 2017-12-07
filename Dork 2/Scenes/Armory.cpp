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
	selectorArrow = orxObject_CreateFromConfig("Selector");
	defaultPos = {-1300, 750, 0};
	orxObject_SetPosition(selectorArrow, &defaultPos);
	orxObject_CreateFromConfig("ArmoryHelp");

	tickMarks = std::vector<orxOBJECT*>(WEAPONCOUNT);
	allWeapons = std::vector<Weapon*>(WEAPONCOUNT);
	orxVECTOR pos = {-1000, 750, 0};
	orxVECTOR wpos = {-1200, 750, 0};
	for (int i = 0; i < WEAPONCOUNT; i++) {
		orxOBJECT* tick = orxObject_CreateFromConfig("TickMark");
		orxObject_SetPosition(tick, &pos);
		tickMarks[i] = tick;

		orxOBJECT* weapon = orxObject_CreateFromConfig(Weapon::getWeaponName((WeaponType)i));
		orxObject_SetPosition(weapon, &wpos);

		pos.fY += 60;
		wpos.fY += 60;

		allWeapons[i] = Weapon::copyOf((WeaponType)i);
	}

	orxOBJECT* exit = orxObject_CreateFromConfig("Exit");
	orxObject_SetPosition(exit, &wpos);

	loadPlayerData(player);

	pos = {-950, 750, 0};
	weaponName = orxObject_CreateFromConfig("SV");
	orxObject_SetPosition(weaponName, &pos);

	pos.fY += 20;
	weaponType = orxObject_CreateFromConfig("SV");
	orxObject_SetPosition(weaponType, &pos);

	pos.fY += 20;
	weaponPrice = orxObject_CreateFromConfig("SV");
	orxObject_SetPosition(weaponPrice, &pos);

	pos.fY += 20;
	weaponStr = orxObject_CreateFromConfig("SV");
	orxObject_SetPosition(weaponStr, &pos);

	pos.fY += 20;
	weaponDef = orxObject_CreateFromConfig("SV");
	orxObject_SetPosition(weaponDef, &pos);

	pos.fY += 20;
	weaponSpeed = orxObject_CreateFromConfig("SV");
	orxObject_SetPosition(weaponSpeed, &pos);

	statViewer = new StatViewer(player, {-1590, 1000, 0});
	selectionLimit = WEAPONCOUNT;

	setPauseMenuPosition({-1150, 1000, 0});
}

void Armory::loadPlayerData(Player* player) {
	Scene::loadPlayerData(player);
	for (int i = 0; i < WEAPONCOUNT; i++) {
		orxObject_Enable(tickMarks[i], player->ownsWeapon((WeaponType)i));
	}
}

void Armory::loadItemData() {
	Weapon* w = allWeapons[currentSelection];
	orxCHAR text[30];

	orxString_Print(text, "Weapon: %s", w->getName());
	orxObject_SetTextString(weaponName, text);

	orxString_Print(text, "Type: %s", Entity::typeToString(w->getType()));
	orxObject_SetTextString(weaponType, text);

	orxString_Print(text, "Price: %d", w->getPrice());
	orxObject_SetTextString(weaponPrice, text);

	orxString_Print(text, "Strength: +%d%%", (int)(w->getStrMod() * 100));
	orxObject_SetTextString(weaponStr, text);

	orxString_Print(text, "Defense: +%d%%", (int)(w->getDefMod() * 100));
	orxObject_SetTextString(weaponDef, text);

	double spd = w->getSpeedMod();
	orxString_Print(text, "Speed: %s%d%%", (spd < 0 ? "-" : "+"), (int)abs(spd * 100));
	orxObject_SetTextString(weaponSpeed, text);
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
