//
//  Armory.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 26/11/2017.
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

#include "Armory.h"

Armory::Armory(Player* player) : Purchasing() {
	orxVECTOR pos = Scene::createVector(-1200, 1060, 0);
	orxObject_SetPosition(itemSelector, &pos);

	orxObject_CreateFromConfig("ArmoryHelp");

	tickMark = orxObject_CreateFromConfig("TickMark");
	orxObject_SetPosition(tickMark, &pos);

	items = std::vector<orxOBJECT*>(WEAPONCOUNT);
	for (int i = 0; i < WEAPONCOUNT; i++) {
		orxOBJECT* weapon = orxObject_CreateFromConfig(Weapon::getWeaponName((WeaponType)i));
		items[i] = weapon;
		orxObject_SetPosition(weapon, &pos);
		orxObject_Enable(weapon, orxFALSE);
	}

	pos.fY += 70;
	orxOBJECT* exit = orxObject_CreateFromConfig("Exit");
	orxObject_SetPosition(exit, &pos);

	pos.fX -= 58;
	orxObject_SetPosition(exitArrow, &pos);

	loadPlayerData(player);

	pos = Scene::createVector(-1240, 850, 0);
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

	statViewer = new StatViewer(player, Scene::createVector(-1590, 1000, 0));
	selectionLimit = WEAPONCOUNT - 1;

	setPauseMenuPosition(Scene::createVector(-1150, 1000, 0));
	initializeUITextAt(Scene::createVector(-1600, 1160, -0.1));
}

void Armory::loadPlayerData(Player* player) {
	Purchasing::loadPlayerData(player);
	orxObject_Enable(tickMark, player->ownsWeapon(SWORD));
	WeaponType type = player->getWeapon()->getWeaponType();
	equipWeapon(type);
}

void Armory::equipWeapon(WeaponType type) {
	lastEquipped = (int)type;
	orxObject_Enable(tickMark, type == currentSelection);
}

void Armory::loadItemData() {
	Weapon* w = Weapon::allWeapons[currentSelection];
	orxCHAR text[30];

	orxString_Print(text, "Weapon: %s%s", w->getName(), (lastEquipped == currentSelection ? " (Equipped)" : ""));
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

	orxObject_Enable(tickMark, player->ownsWeapon((WeaponType)currentSelection));

	Purchasing::loadItemData();
}

int Armory::makePurchase() {
	Weapon* weapon = Weapon::copyOf((WeaponType)currentSelection);
	WeaponType type = (WeaponType)currentSelection;
	if (player->ownsWeapon((WeaponType)currentSelection)) {
		if (player->getWeapon()->getWeaponType() == type) {
			type = NOWEAPON;
		}
		equipWeapon(type);
		player->equipWeapon(Weapon::copyOf(type));
		statViewer->reloadData();

		orxCHAR text[40];
		orxString_Print(text, "%squipped %s", (type == NOWEAPON ? "Un-e" : "E"), weapon->getName());
		loadUIText(text);

		return type == NOWEAPON ? WEAPON_UNEQUIPPED : WEAPON_EQUIPPED;
	} else if (player->getGold() >= weapon->getPrice()) {
		player->transaction(-weapon->getPrice());
		player->setWeaponOwnership((WeaponType)currentSelection, true);
		orxObject_Enable(tickMark, orxTRUE);

		equipWeapon(type);
		player->equipWeapon(Weapon::copyOf(type));
		statViewer->reloadData();

		orxCHAR text[40];
		orxString_Print(text, "Purchased %s", weapon->getName());
		loadUIText(text);

		return PURCHASE_SUCCESSFUL;
	}
	return PURCHASE_FAILED;
}

SceneType Armory::getSceneType() {
	return ARMORY;
}
