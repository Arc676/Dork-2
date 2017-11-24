//
//  Shop.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 24/11/2017.
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

#include "Shop.h"

Shop::Shop(Player* player) {
	loadPlayerData(player);
	selectorArrow = orxObject_CreateFromConfig("Selector");
	orxVECTOR pos = {100, 100, 0};
	orxObject_SetPosition(selectorArrow, &pos);
}

void Shop::activate() {}
void Shop::deactivate() {}

orxBOOL Shop::getKeyDown(orxSTRING key) {
	return orxInput_IsActive(key) && orxInput_HasNewStatus(key);
}

void Shop::makePurchase() {
	//
}

SceneType Shop::update(const orxCLOCK_INFO* clockInfo) {
	orxVECTOR pos;
	orxBOOL selectionChanged = orxTRUE;
	orxObject_GetPosition(selectorArrow, &pos);
	if (getKeyDown((orxSTRING)"GoDown") && currentSelection < POTIONCOUNT + 1) {
		pos.fY -= 60;
		quantity = 1;
	} else if (getKeyDown((orxSTRING)"GoUp") && currentSelection >= 0) {
		pos.fY += 60;
		quantity = 1;
	} else if (getKeyDown((orxSTRING)"GoLeft") && quantity > 0) {
		quantity--;
	} else if (getKeyDown((orxSTRING)"GoRight")) {
		quantity++;
	} else if (getKeyDown((orxSTRING)"Enter")) {
		if (currentSelection == POTIONCOUNT) {
			return EXPLORATION;
		}
		//
	} else {
		selectionChanged = orxFALSE;
	}
	if (selectionChanged) {
		orxObject_SetPosition(selectorArrow, &pos);
	}
	return SHOP;
}

SceneType Shop::getSceneType() {
	return SHOP;
}
