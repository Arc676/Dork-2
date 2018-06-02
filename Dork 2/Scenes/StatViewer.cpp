//
//  StatViewer.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 30/11/2017.
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

#include "StatViewer.h"

StatViewer::StatViewer(orxVECTOR pos) {
	int margin = 30;

	labelName = orxObject_CreateFromConfig("SV");
	orxObject_SetPosition(labelName, &pos);

	labelType = orxObject_CreateFromConfig("SV");
	pos.fY += margin;
	orxObject_SetPosition(labelType, &pos);

	labelHP = orxObject_CreateFromConfig("SV");
	pos.fY += margin;
	orxObject_SetPosition(labelHP, &pos);

	labelSpeed = orxObject_CreateFromConfig("SV");
	pos.fY += margin;
	orxObject_SetPosition(labelSpeed, &pos);

	labelStr = orxObject_CreateFromConfig("SV");
	pos.fY += margin;
	orxObject_SetPosition(labelStr, &pos);

	labelDef = orxObject_CreateFromConfig("SV");
	pos.fY += margin;
	orxObject_SetPosition(labelDef, &pos);

	labelGold = orxObject_CreateFromConfig("SV");
	pos.fY += margin;
	orxObject_SetPosition(labelGold, &pos);

	labelLvl = orxObject_CreateFromConfig("SV");
	pos.fY += margin;
	orxObject_SetPosition(labelLvl, &pos);

	labelWeapon = orxObject_CreateFromConfig("SV");
	pos.fY += margin;
	orxObject_SetPosition(labelWeapon, &pos);
}

void StatViewer::loadEntity(Entity* entity) {
	this->entity = entity;
	reloadData();
}

void StatViewer::reloadData() {
	orxCHAR text[30];

	orxObject_SetTextString(labelName, entity->getName());

	orxString_Print(text, "HP: %d", entity->getHP());
	orxObject_SetTextString(labelHP, text);

	orxString_Print(text, "Type: %s", Entity::typeToString(entity->getType()));
	orxObject_SetTextString(labelType, text);

	orxString_Print(text, "Speed: %d", entity->getSpeed());
	orxObject_SetTextString(labelSpeed, text);

	orxString_Print(text, "Strength: %d", entity->getStrength());
	orxObject_SetTextString(labelStr, text);

	orxString_Print(text, "Defense: %d", entity->getDefense());
	orxObject_SetTextString(labelDef, text);

	orxString_Print(text, "Gold: %d", entity->getGold());
	orxObject_SetTextString(labelGold, text);

	orxString_Print(text, "Level %d (+%d XP)", entity->getLevel().getLevel(), entity->getLevel().getXP());
	orxObject_SetTextString(labelLvl, text);

	orxString_Print(text, "Weapon: %s", entity->getWeapon()->getName());
	orxObject_SetTextString(labelWeapon, text);
}
