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

Purchasing::Purchasing() : Scene() {}

void Purchasing::activate() {
	currentSelection = 0;
	statViewer->reloadData();
	loadItemData();
	Scene::activate();
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
	if (getKeyDown((orxSTRING)"GoRight") && currentSelection < selectionLimit) {
		currentSelection++;
	} else if (getKeyDown((orxSTRING)"GoLeft") && currentSelection > 0) {
		currentSelection--;
	} else if (getKeyDown((orxSTRING)"Enter")) {
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
	}
	if (currentSelection != prevSelection) {
		orxObject_AddSound(player->getEntity(), "SelectorSound");
		loadItemData();
	}
	return getSceneType();
}
