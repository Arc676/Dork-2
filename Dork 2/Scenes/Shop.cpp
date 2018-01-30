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
	selectorArrow = orxObject_CreateFromConfig("Selector");
	defaultPos = {-1300, -650, 0};
	orxObject_SetPosition(selectorArrow, &defaultPos);
	orxObject_CreateFromConfig("ShopHelp");

	potionCounts = std::vector<orxOBJECT*>(POTIONCOUNT);
	orxVECTOR pos = {-1000, -650, 0};
	orxVECTOR ppos = {-1200, -650, 0};
	for (int i = 0; i < POTIONCOUNT; i++) {
		orxOBJECT* count = orxObject_CreateFromConfig("SV");
		orxObject_SetPosition(count, &pos);
		potionCounts[i] = count;

		orxOBJECT* potion = orxObject_CreateFromConfig(Potion::configCodeForType((PotionType)i));
		orxObject_SetPosition(potion, &ppos);

		pos.fY += 60;
		ppos.fY += 60;
	}

	orxOBJECT* exit = orxObject_CreateFromConfig("Exit");
	orxObject_SetPosition(exit, &ppos);
	
	loadPlayerData(player);

	pos = {-950, -650, 0};
	potionName = orxObject_CreateFromConfig("SV");
	orxObject_SetPosition(potionName, &pos);

	pos.fY += 20;
	potionPrice = orxObject_CreateFromConfig("SV");
	orxObject_SetPosition(potionPrice, &pos);

	pos.fY += 20;
	potionEffect = orxObject_CreateFromConfig("SV");
	orxObject_SetPosition(potionEffect, &pos);

	statViewer = new StatViewer(player, {-1590, -400, 0});
	selectionLimit = POTIONCOUNT;

	setPauseMenuPosition({-1100, -400.0, 0});
}

void Shop::loadPlayerData(Player* player) {
	Scene::loadPlayerData(player);
	orxCHAR text[5];
	for (int i = 0; i < POTIONCOUNT; i++) {
		orxString_Print(text, "%d", player->amountOfPotionOwned((PotionType)i));
		orxObject_SetTextString(potionCounts[i], text);
	}
	if (statViewer != orxNULL) {
		statViewer->loadEntity(player);
	}
}

void Shop::loadItemData() {
	Potion* p = Potion::allPotions[currentSelection];
	orxCHAR text[30];

	orxString_Print(text, "Potion: %s", p->getName());
	orxObject_SetTextString(potionName, text);

	int price = p->getPrice();
	orxString_Print(text, "Price: %d (%dx) = %d", price, quantity, (price * quantity));
	orxObject_SetTextString(potionPrice, text);

	switch (p->getType()) {
		case QUICKHEAL_2:
		case QUICKHEAL_5:
		case QUICKHEAL_10:
		case QUICKHEAL_20:
		case QUICKHEAL_50:
			orxString_Print(text, "Heals: +%d", (int)p->getAmount());
			break;
		case DEFBOOST:
		case SPEEDBOOST:
		case STRBOOST:
			orxString_Print(text, "Boost: +%d%%", (int)(p->getAmount() * 100));
			break;
		default:
			break;
	}
	orxObject_SetTextString(potionEffect, text);
}

int Shop::makePurchase() {
	Potion* potion = Potion::getCopyOf((PotionType)currentSelection);
	if (player->getGold() >= quantity * potion->getPrice()) {
		player->transaction(-quantity * potion->getPrice());
		player->changePotionAmount((PotionType)currentSelection, quantity);
		statViewer->reloadData();

		orxCHAR text[5];
		orxString_Print(text, "%d", player->amountOfPotionOwned((PotionType)currentSelection));
		orxObject_SetTextString(potionCounts[currentSelection], text);
		return PURCHASE_SUCCESSFUL;
	}
	return PURCHASE_FAILED;
}

SceneType Shop::update(const orxCLOCK_INFO* clockInfo) {
	if (paused || hasText) {
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
