//
//  Combat.cpp
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

#include "Combat.h"

Move Combat::moves[2][2] = {
	{ATTACK, SPECIAL_MOVE},
	{USE_ITEM, RUN}
};

Combat::Combat(Player* player, Enemy* enemy) : Scene(), enemy(enemy) {
	loadPlayerData(player);
	selector = orxObject_CreateFromConfig("Selector");
	orxVECTOR pos = {-1400, 500, 0};
	orxObject_SetPosition(selector, &pos);

	playerStats = new StatViewer(player, {-1500, 300, 0});
	enemyStats = new StatViewer(enemy, {-1000, 150, 0});
//	music = orxSound_CreateFromConfig("FightMusic"); //doesn't exist yet

	orxVECTOR ppos = {-1150.0, 400.0, 0};
	orxObject_SetPosition(pauseSelector, &ppos);
}

void Combat::activate() {
	playerPos = player->getPosition();
	player->setPosition({-1200, 450, 0});
	enemy->setPosition({-1100, 200, 0});

	orxObject_SetTargetAnim(player->getEntity(), "IdleUAnim");
	orxCHAR anim[30];
	orxString_Print(anim, "IdleDAnim%s", enemy->getName());
	orxObject_SetTargetAnim(enemy->getEntity(), anim);

	Scene::activate();
}

void Combat::deactivate() {
	orxObject_SetLifeTime(selector, 0);
	enemy->despawn();
	playerStats->destroy();
	enemyStats->destroy();
	player->setPosition(playerPos);
	Scene::deactivate();
}

SceneType Combat::makeMove(Move move) {
	switch (move) {
		case RUN:
			return EXPLORATION;
		case ATTACK:
//			player.speed += modifiers[0];
//			player.strength += modifiers[1];
//			player.defense += modifiers[2];
			Entity::entityAttack(player, enemy);
			if (enemy->getHP() > 0){
				Entity::entityAttack(enemy, player);
			}
//			player.speed -= modifiers[0];
//			player.strength -= modifiers[1];
//			player.defense -= modifiers[2];
			if (specialMoveCooldown > 0) {
				specialMoveCooldown--;
			}
			break;
		case SPECIAL_MOVE:
			if (specialMoveCooldown > 0) {
				break;
			}
			switch (player->getType()) {
				case MAGIC:
					break;
				case SPEED:
					break;
				case MELEE:
					break;
				case RANGE:
					break;
				default:
					break;
			}
			Entity::entityAttack(enemy, player);
			break;
		case USE_ITEM:
			break;
	}
	if (enemy->getHP() <= 0) {
		player->defeat(enemy);
		return EXPLORATION;
	} else if (player->getHP() <= 0) {
		return MAIN_MENU;
	}
	playerStats->reloadData();
	enemyStats->reloadData();
	return COMBAT;
}

SceneType Combat::update(const orxCLOCK_INFO* clockInfo) {
	Scene::update(clockInfo);
	if (paused) {
		return COMBAT;
	}
	orxVECTOR pos;
	orxBOOL selChanged = orxTRUE;
	orxObject_GetPosition(selector, &pos);
	if (getKeyDown((orxSTRING)"GoDown") && y < 1) {
		pos.fY += 60;
		y++;
	} else if (getKeyDown((orxSTRING)"GoUp") && y > 0) {
		pos.fY -= 60;
		y--;
	} else if (getKeyDown((orxSTRING)"GoLeft") && x > 0) {
		pos.fX -= 300;
		x--;
	} else if (getKeyDown((orxSTRING)"GoRight") && x < 1) {
		pos.fX += 300;
		x++;
	} else {
		if (getKeyDown((orxSTRING)"Enter")) {
			return makeMove(moves[y][x]);
		}
		selChanged = orxFALSE;
	}
	if (selChanged) {
		orxObject_SetPosition(selector, &pos);
	}
	return COMBAT;
}

SceneType Combat::getSceneType() {
	return COMBAT;
}
