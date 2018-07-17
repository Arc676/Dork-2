//
//  Shop.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 24/11/2017.
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

#include "Shop.h"

Shop::Shop() : Purchasing() {
	orxVECTOR pos = Scene::createVector(-1200, -370, 0);
	orxObject_SetPosition(itemSelector, &pos);

	orxObject_CreateFromConfig("ShopHelp");

	items = std::vector<orxOBJECT*>(POTIONCOUNT);
	for (int i = 0; i < POTIONCOUNT; i++) {
		orxOBJECT* potion = orxObject_CreateFromConfig(Potion::configCodeForType((PotionType)i));
		items[i] = potion;
		orxObject_SetPosition(potion, &pos);
		orxObject_Enable(potion, orxFALSE);
	}

	pos.fY += 140;
	orxOBJECT* exit = orxObject_CreateFromConfig("Exit");
	orxObject_SetPosition(exit, &pos);

	pos.fX -= 58;
	orxObject_SetPosition(exitArrow, &pos);

	int margin = 30;

	pos = Scene::createVector(-1240, -500, 0);
	potionName = orxObject_CreateFromConfig("SV");
	orxObject_SetPosition(potionName, &pos);

	pos.fY += margin;
	potionPrice = orxObject_CreateFromConfig("SV");
	orxObject_SetPosition(potionPrice, &pos);

	pos.fY += margin;
	potionEffect = orxObject_CreateFromConfig("SV");
	orxObject_SetPosition(potionEffect, &pos);

	pos.fY += 120;
	pos.fX -= 40;
	potionQty = orxObject_CreateFromConfig("SV");
	orxObject_SetTextString(potionQty, "Quantity: 1");
	orxObject_SetPosition(potionQty, &pos);

	statViewer = new StatViewer(Scene::createVector(-1590, -400, 0));
	selectionLimit = POTIONCOUNT - 1;

	fieldLimit = 2;

	setPauseMenuPosition(Scene::createVector(-1100, -400.0, 0));
	initializeUITextAt(Scene::createVector(-1600, -240, -0.1));
}

void Shop::loadItemData() {
	Potion* p = Potion::allPotions[currentSelection];
	orxCHAR text[100];

	orxString_Print(text, "Potion: %s (%d owned)", p->getName(), player->amountOfPotionOwned((PotionType)currentSelection));
	orxObject_SetTextString(potionName, text);

	int price = p->getPrice();
	orxString_Print(text, "Unit Price: %d", price);
	orxObject_SetTextString(potionPrice, text);

	orxString_Print(text, "Quantity: %d\n(Total %d)", quantity, (price * quantity));
	orxObject_SetTextString(potionQty, text);

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

	Purchasing::loadItemData();
}

int Shop::makePurchase() {
	Potion* potion = Potion::getCopyOf((PotionType)currentSelection);
	if (player->getGold() >= quantity * potion->getPrice()) {
		player->transaction(-quantity * potion->getPrice());
		player->changePotionAmount((PotionType)currentSelection, quantity);
		statViewer->reloadData();

		orxCHAR text[100];
		orxString_Print(text, "Purchased %d vial(s) of %s", quantity, potion->getName());
		loadUIText(text);
		return PURCHASE_SUCCESSFUL;
	}
	return PURCHASE_FAILED;
}

orxBOOL Shop::canChangeSelection(int delta) {
	if (selectedField == SHOP_POTION) {
		return Purchasing::canChangeSelection(delta);
	}
	if (quantity + delta < 1) {
		return orxFALSE;
	}
	return orxTRUE;
}

orxBOOL Shop::changeSelection(int delta) {
	if (selectedField == SHOP_QTY) {
		if (canChangeSelection(delta)) {
			quantity += delta;
			orxObject_AddSound(player->getEntity(), "TickSound");
			loadItemData();
			return orxTRUE;
		}
		return orxFALSE;
	}
	orxBOOL res = Purchasing::changeSelection(delta);
	if (res) {
		quantity = 1;
	}
	return res;
}

void Shop::deactivate() {
	quantity = 1;
	Purchasing::deactivate();
}

SceneType Shop::getSceneType() {
	return SHOP;
}
