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
	orxObject_CreateFromConfig("ShopHelp");
}

void Shop::activate() {}
void Shop::deactivate() {}

orxBOOL Shop::getKeyDown(orxSTRING key) {
	return orxInput_IsActive(key) && orxInput_HasNewStatus(key);
}

orxBOOL Shop::makePurchase() {
	Potion* potion = Potion::getCopyOf((PotionType)currentSelection);
	if (player->getGold() >= quantity * potion->getPrice()) {
		player->transaction(quantity * potion->getPrice());
		player->getPotions()[currentSelection] += quantity;
		return orxTRUE;
	}
	return orxFALSE;
}

SceneType Shop::update(const orxCLOCK_INFO* clockInfo) {
	orxVECTOR pos;
	orxBOOL selectionChanged = orxTRUE;
	orxObject_GetPosition(selectorArrow, &pos);
	if (getKeyDown((orxSTRING)"GoDown") && currentSelection < POTIONCOUNT) {
		pos.fY += 60;
		orxObject_SetPosition(selectorArrow, &pos);
		quantity = 1;
		currentSelection++;
	} else if (getKeyDown((orxSTRING)"GoUp") && currentSelection > 0) {
		pos.fY -= 60;
		orxObject_SetPosition(selectorArrow, &pos);
		quantity = 1;
		currentSelection--;
	} else if (getKeyDown((orxSTRING)"GoLeft") && quantity > 0) {
		quantity--;
	} else if (getKeyDown((orxSTRING)"GoRight")) {
		quantity++;
	} else if (getKeyDown((orxSTRING)"Enter")) {
		if (currentSelection == POTIONCOUNT) {
			return EXPLORATION;
		}
		makePurchase();
		// play a sound depending on success
	} else {
		selectionChanged = orxFALSE;
	}
	return SHOP;
}

SceneType Shop::getSceneType() {
	return SHOP;
}
