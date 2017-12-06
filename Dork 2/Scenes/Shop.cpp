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

Shop::Shop(Player* player) : Purchasing() {
	loadPlayerData(player);
	selectorArrow = orxObject_CreateFromConfig("Selector");
	defaultPos = {-1300, -650, 0};
	orxObject_SetPosition(selectorArrow, &defaultPos);
	orxObject_CreateFromConfig("ShopHelp");

	potionCounts = std::vector<orxOBJECT*>(POTIONCOUNT);
	allPotions = std::vector<Potion*>(POTIONCOUNT);
	orxVECTOR pos = {-1000, -650, 0};
	orxVECTOR ppos = {-1200, -650, 0};
	for (int i = 0; i < POTIONCOUNT; i++) {
		orxCHAR config[30];
		orxSTRING configName = Potion::configCodeForType((PotionType)i);
		orxString_Print(config, "%sCount", configName);
		orxOBJECT* count = orxObject_CreateFromConfig(config);
		orxObject_SetPosition(count, &pos);

		orxCHAR text[5];
		orxString_Print(text, "%d", player->amountOfPotionOwned((PotionType)i));
		orxObject_SetTextString(count, text);
		potionCounts[i] = count;

		orxOBJECT* potion = orxObject_CreateFromConfig(configName);
		orxObject_SetPosition(potion, &ppos);

		pos.fY += 60;
		ppos.fY += 60;

		allPotions[i] = Potion::getCopyOf((PotionType)i);
	}

	statViewer = new StatViewer(player, {-1590, -400, 0});
	selectionLimit = POTIONCOUNT;

	setPauseMenuPosition({-1100, -400.0, 0});
}

orxBOOL Shop::makePurchase() {
	Potion* potion = Potion::getCopyOf((PotionType)currentSelection);
	if (player->getGold() >= quantity * potion->getPrice()) {
		player->transaction(-quantity * potion->getPrice());
		player->changePotionAmount((PotionType)currentSelection, quantity);
		statViewer->reloadData();
		return orxTRUE;
	}
	return orxFALSE;
}

SceneType Shop::update(const orxCLOCK_INFO* clockInfo) {
	if (paused) {
		return Purchasing::update(clockInfo);
	}
	if (getKeyDown((orxSTRING)"GoLeft") && quantity > 0) {
		quantity--;
	} else if (getKeyDown((orxSTRING)"GoRight")) {
		quantity++;
	} else {
		if ((getKeyDown((orxSTRING)"GoDown") && currentSelection < POTIONCOUNT) ||
			(getKeyDown((orxSTRING)"GoUp") && currentSelection > 0)) {
			quantity = 1;
		}
		return Purchasing::update(clockInfo);
	}
	return SHOP;
}

SceneType Shop::getSceneType() {
	return SHOP;
}
