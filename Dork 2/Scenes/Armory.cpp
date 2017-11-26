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

Armory::Armory(Player* player) {
	loadPlayerData(player);
	selectorArrow = orxObject_CreateFromConfig("Selector");
	orxVECTOR pos = {-1300, 50, -0.3};
	orxObject_SetPosition(selectorArrow, &pos);
	orxObject_CreateFromConfig("ShopHelp");
}

void Armory::activate() {}
void Armory::deactivate() {}

orxBOOL Armory::makePurchase() {
	Weapon* weapon = Weapon::copyOf((WeaponType)currentSelection);
	if (player->getGold() >= weapon->getPrice() && !player->getWeapons()[currentSelection]) {
		player->transaction(-weapon->getPrice());
		player->getWeapons()[currentSelection] = true;
		return orxTRUE;
	}
	return orxFALSE;
}

SceneType Armory::update(const orxCLOCK_INFO* clockInfo) {
	orxVECTOR pos;
	orxObject_GetPosition(selectorArrow, &pos);
	if (getKeyDown((orxSTRING)"GoDown") && currentSelection < WEAPONCOUNT) {
		pos.fY += 60;
		orxObject_SetPosition(selectorArrow, &pos);
		currentSelection++;
	} else if (getKeyDown((orxSTRING)"GoUp") && currentSelection > 0) {
		pos.fY -= 60;
		orxObject_SetPosition(selectorArrow, &pos);
		currentSelection--;
	} else if (getKeyDown((orxSTRING)"Enter")) {
		if (currentSelection == POTIONCOUNT) {
			return EXPLORATION;
		}
		if (makePurchase()) {
			orxObject_AddSound(player->getEntity(), "Kaching");
		}
	}
	return ARMORY;
}

SceneType Armory::getSceneType() {
	return ARMORY;
}
