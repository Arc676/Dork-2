//
//  Player.cpp
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 21/11/2017.
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

#include "Player.h"

Player::Player(orxSTRING name, EntityType type) : name(name) {
	this->type = type;
	HP = 30;
	speed = 10;
	strength = 15;
	defense = 15;

	orxInput_Load(orxSTRING_EMPTY);
	entity = orxObject_CreateFromConfig("Player");

	position = {96, 96, 0};
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
	int prevLv = (int)level;
	gold += enemy->getGold();
	level += 0.5 * enemy->getLevel();
	int levelGain = (int)level - prevLv;
	if (levelGain > 0){
		int healthGained = 0;
		for (int i = 0; i < levelGain; i++){
			healthGained += 2;
		}
		HP += healthGained;
		orxBOOL gainedStats = orxFALSE;
		for (int lv = (int)prevLv + 1; lv <= prevLv + levelGain; lv++){
			if (lv % ((int)floor(log10(lv * lv)) + 3) == 0){
				speed++;
				strength++;
				defense++;
				gainedStats = orxTRUE;
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
