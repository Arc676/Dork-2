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

void Purchasing::activate() {
	currentSelection = 0;
	exitSelected = orxFALSE;
	statViewer->reloadData();
	loadItemData();
	Scene::activate();
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

SceneType Purchasing::update(const orxCLOCK_INFO* clockInfo) {
	orxBOOL hadText = Scene::currentlyHasText();
	SceneType type = Scene::update(clockInfo);
	if (type != getSceneType()) {
		return type;
	}
	if (paused || hadText) {
		return getSceneType();
	}
	int prevSelection = currentSelection;
	if (getKeyDown((orxSTRING)"Enter")) {
		if (exitSelected) {
			return EXPLORATION;
		} else {
			int result = makePurchase();
			if (result == PURCHASE_SUCCESSFUL) {
				orxObject_AddSound(player->getEntity(), "Kaching");
			} else if (result == PURCHASE_FAILED) {
				orxObject_AddSound(player->getEntity(), "ErrorSound");
			}
		}
	} else if (getKeyDown((orxSTRING)"GoDown") && !exitSelected) {
		exitSelected = orxTRUE;
	} else if (getKeyDown((orxSTRING)"GoUp") && exitSelected) {
		exitSelected = orxFALSE;
	} else if (!exitSelected) {
		if (getKeyDown((orxSTRING)"GoRight") && currentSelection < selectionLimit) {
			currentSelection++;
		} else if (getKeyDown((orxSTRING)"GoLeft") && currentSelection > 0) {
			currentSelection--;
		}
	}
	if (currentSelection != prevSelection) {
		orxObject_AddSound(player->getEntity(), "SelectorSound");
		loadItemData();
	}
	orxObject_Enable(itemSelector, !exitSelected);
	orxObject_Enable(exitArrow, exitSelected);
	return getSceneType();
}
