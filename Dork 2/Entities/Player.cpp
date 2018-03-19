//
//  Player.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 21/11/2017.
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

#include "Player.h"
#include "Scene.h"

Player::Player(orxSTRING name, EntityType type) : name(name) {
	this->type = type;
	HP = 30;
	speed = 10;
	strength = 15;
	defense = 15;

	orxInput_Load(orxSTRING_EMPTY);
	entity = orxObject_CreateFromConfig("Player");

	position = Scene::createVector(1632, 1792, 0);
	orxObject_SetPosition(entity, &position);

	ownedPotions = std::vector<int>(POTIONCOUNT);
	ownedWeapons = std::vector<bool>(WEAPONCOUNT);
}

orxSTRING Player::getName() {
	return name;
}

int Player::amountOfPotionOwned(PotionType type) {
	return ownedPotions[type];
}

void Player::changePotionAmount(PotionType type, int delta) {
	ownedPotions[type] += delta;
}

bool Player::ownsWeapon(WeaponType type) {
	return ownedWeapons[type];
}

void Player::setWeaponOwnership(WeaponType type, bool owns) {
	ownedWeapons[type] = owns;
}

void Player::defeat(Enemy* enemy) {
	gold += enemy->getGold();
	enemy->transaction(-enemy->getGold());

	int prevLv = level.getLevel();
	int levelGain = level.gainXP(enemy->getLevel());
	if (levelGain > 0) {
		HP += levelGain * 2;
		for (int lv = prevLv + 1; lv <= level.getLevel(); lv++) {
			if (lv % ((int)floor(log10(lv * lv)) + 3) == 0) {
				speed++;
				strength++;
				defense++;
			}
		}
	}
}

void Player::update(bool up, bool down, bool left, bool right, float dt) {
	orxObject_GetPosition(entity, &position);
	if (up) {
		position.fY -= motionSpeed * dt;
		orxObject_SetTargetAnim(entity, "WalkUpAnim");
	} else if (down) {
		position.fY += motionSpeed * dt;
		orxObject_SetTargetAnim(entity, "WalkDownAnim");
	} else if (left) {
		position.fX -= motionSpeed * dt;
		orxObject_SetTargetAnim(entity, "WalkLeftAnim");
	} else if (right) {
		position.fX += motionSpeed * dt;
		orxObject_SetTargetAnim(entity, "WalkRightAnim");
	} else {
		orxObject_SetTargetAnim(entity, orxNULL);
	}
	orxObject_SetPosition(entity, &position);
}

orxSTATUS Player::read(orxSTRING filename) {
	if (!orxConfig_HasSection("PlayerData")) {
		orxCHAR path[30];
		orxString_Print(path, "Dork2/%s", name);
		orxConfig_Load(orxFile_GetApplicationSaveDirectory(path));
	}
	if (orxConfig_HasSection("PlayerData") && orxConfig_PushSection("PlayerData")) {
		HP = orxConfig_GetU32("HP");
		speed = orxConfig_GetU32("Speed");
		strength = orxConfig_GetU32("Str");
		defense = orxConfig_GetU32("Def");
		weapon = Weapon::copyOf((WeaponType)orxConfig_GetU32("Weapon"));
		gold = orxConfig_GetU32("Gold");
		level = Level(orxConfig_GetU32("XP"));
		type = (EntityType)orxConfig_GetU32("Type");
		name = (orxSTRING)orxConfig_GetString("Name");

		ownedPotions = std::vector<int>(POTIONCOUNT);
		for (int i = 0; i < POTIONCOUNT; i++) {
			ownedPotions[i] = orxConfig_GetListU32("OwnedPotions", i);
		}
		ownedWeapons = std::vector<bool>(WEAPONCOUNT);
		for (int i = 0; i < WEAPONCOUNT; i++) {
			ownedWeapons[i] = orxConfig_GetListBool("OwnedWeapons", i);
		}
		orxConfig_ClearSection("PlayerData");
		return orxSTATUS_SUCCESS;
	}
	orxObject_SetLifeTime(entity, 0);
	return orxSTATUS_FAILURE;
}

orxSTATUS Player::write() {
	if (orxConfig_PushSection("PlayerData")) {
		orxConfig_SetU32("MotionSpeed", motionSpeed);
		orxConfig_SetU32("HP", HP);
		orxConfig_SetU32("Speed", speed);
		orxConfig_SetU32("Str", strength);
		orxConfig_SetU32("Def", defense);
		orxConfig_SetU32("Weapon", weapon->getWeaponType());
		orxConfig_SetU32("Gold", gold);
		orxConfig_SetU32("XP", level.getTotalXP());
		orxConfig_SetString("Name", name);

		const orxSTRING potions[POTIONCOUNT];
		for (int i = 0; i < POTIONCOUNT; i++) {
			orxCHAR str[5];
			orxString_Print(str, "%d", ownedPotions[i]);
			potions[i] = str;
		}
		orxConfig_SetListString("OwnedPotions", potions, POTIONCOUNT);

		const orxSTRING weapons[WEAPONCOUNT];
		for (int i = 0; i < WEAPONCOUNT; i++) {
			weapons[i] = ownedWeapons[i] ? (orxSTRING)"1" : (orxSTRING)"0";
		}
		orxConfig_SetListString("OwnedWeapons", weapons, WEAPONCOUNT);

		orxConfig_PopSection();
		orxCHAR path[30];
		orxString_Print(path, "Dork2/%s", name);
		return orxConfig_Save(orxFile_GetApplicationSaveDirectory(path), orxFALSE, sectionFilter);
	}
	return orxSTATUS_FAILURE;
}

orxBOOL Player::sectionFilter(const orxSTRING _zSectionName, const orxSTRING _zKeyName, const orxSTRING _zFileName, orxBOOL _bUseEncryption) {
	return orxString_Compare(_zSectionName, "PlayerData") == 0;
}

void Player::resumeAnimation() {}
