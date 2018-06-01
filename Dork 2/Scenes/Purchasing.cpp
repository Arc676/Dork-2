//
//  Purchasing.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 01/12/2017.
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

#include "Purchasing.h"

Purchasing::Purchasing() : Scene() {
	itemSelector = orxObject_CreateFromConfig("LRArrows");
	exitArrow = orxObject_CreateFromConfig("Selector");
}

void Purchasing::activate(Player* player) {
	Scene::activate(player);
	currentSelection = 0;
	selectedField = 0;
	statViewer->reloadData();
	loadItemData();
}

void Purchasing::loadItemData() {
	// hide previously selected item, show currently selected one
	// current selection will be previous selection next time
	orxObject_Enable(items[prevSel], orxFALSE);
	orxObject_Enable(items[currentSelection], orxTRUE);
	prevSel = currentSelection;
}

void Purchasing::loadPlayerData(Player* player) {
	Scene::loadPlayerData(player);
	if (statViewer != orxNULL) {
		statViewer->loadEntity(player);
	}
}

orxBOOL Purchasing::changeSelection(int delta) {
	if (canChangeSelection(delta)) {
		currentSelection += delta;
		return orxTRUE;
	}
	return orxFALSE;
}

orxBOOL Purchasing::canChangeSelection(int delta) {
	if (currentSelection + delta > selectionLimit) {
		return orxFALSE;
	}
	if (currentSelection + delta < 0) {
		return orxFALSE;
	}
	return orxTRUE;
}

orxBOOL Purchasing::canChangeField(int delta) {
	if (selectedField + delta < 0) {
		return orxFALSE;
	}
	if (selectedField + delta > fieldLimit) {
		return orxFALSE;
	}
	return orxTRUE;
}

orxBOOL Purchasing::changeField(int delta) {
	if (canChangeField(delta)) {
		orxVECTOR pos;
		orxObject_GetPosition(itemSelector, &pos);
		selectedField += delta;
		pos.fY += delta * 70;
		orxObject_SetPosition(itemSelector, &pos);
		return orxTRUE;
	}
	return orxFALSE;
}

SceneType Purchasing::update(const orxCLOCK_INFO* clockInfo) {
	orxBOOL hadText = hasText;
	SceneType type = Scene::update(clockInfo);
	if (type != getSceneType()) {
		return type;
	}
	if (paused || hadText) {
		return getSceneType();
	}
	int prevSelection = currentSelection;
	if (getKeyDown((orxSTRING)"Enter")) {
		if (selectedField == fieldLimit) {
			orxVECTOR pos;
			orxObject_GetPosition(itemSelector, &pos);
			pos.fY -= 70 * selectedField;
			orxObject_SetPosition(itemSelector, &pos);
			return EXPLORATION;
		} else if (selectedField == fieldLimit - 1) {
			int result = makePurchase();
			if (result == PURCHASE_SUCCESSFUL) {
				orxObject_AddSound(player->getEntity(), "Kaching");
			} else if (result == PURCHASE_FAILED) {
				orxObject_AddSound(player->getEntity(), "ErrorSound");
			}
			loadItemData();
		}
	} else if (getKeyDown((orxSTRING)"GoDown")) {
		changeField(1);
	} else if (getKeyDown((orxSTRING)"GoUp")) {
		changeField(-1);
	} else if (selectedField != fieldLimit) {
		orxBOOL success = orxTRUE;
		if (getKeyDown((orxSTRING)"GoRight")) {
			success = changeSelection(1);
		} else if (getKeyDown((orxSTRING)"GoLeft")) {
			success = changeSelection(-1);
		}
		if (!success) {
			orxObject_AddSound(player->getEntity(), "ErrorSound");
		}
	}
	if (currentSelection != prevSelection) {
		orxObject_AddSound(player->getEntity(), "SelectorSound");
		loadItemData();
	}
	orxObject_Enable(itemSelector, selectedField != fieldLimit);
	orxObject_Enable(exitArrow, selectedField == fieldLimit);
	return getSceneType();
}
