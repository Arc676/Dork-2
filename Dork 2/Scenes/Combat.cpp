//
//  Combat.cpp
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

#include "Combat.h"

Move Combat::moves[2][2] = {
	{ATTACK, SPECIAL_MOVE},
	{USE_ITEM, RUN}
};

const orxVECTOR Combat::scaleUp = Scene::createVector(2, 2, 0);
const orxVECTOR Combat::scaleNormal = Scene::createVector(1, 1, 0);

Combat::Combat() {
	selector = orxObject_CreateFromConfig("Selector");
	orxVECTOR pos = Scene::createVector(-1400, 596, -0.2);
	orxObject_SetPosition(selector, &pos);

	playerStats = new StatViewer(Scene::createVector(-1550, 270, 0));
	enemyStats = new StatViewer(Scene::createVector(-1000, 150, 0));
	music = orxSound_CreateFromConfig("FightMusic");
	memset(modifiers, 0, sizeof(modifiers));

	potionName = orxObject_CreateFromConfig("SV");
	pos = Scene::createVector(-1080, 440, 0);
	orxObject_SetPosition(potionName, &pos);
	orxObject_Enable(potionName, orxFALSE);

	pos.fY += 20;
	potionEffect = orxObject_CreateFromConfig("SV");
	orxObject_SetPosition(potionEffect, &pos);
	orxObject_Enable(potionEffect, orxFALSE);

	pos.fY += 40;
	potionHelp = orxObject_CreateFromConfig("PotionHelp");
	orxObject_SetPosition(potionHelp, &pos);
	orxObject_EnableRecursive(potionHelp, orxFALSE);

	pos = Scene::createVector(-1140, 480, 0);
	allPotions = std::vector<orxOBJECT*>(POTIONCOUNT);
	for (int i = 0; i < POTIONCOUNT; i++) {
		orxOBJECT* potion = orxObject_CreateFromConfig(Potion::configCodeForType((PotionType)i));
		orxObject_SetPosition(potion, &pos);
		orxObject_Enable(potion, orxFALSE);
		allPotions[i] = potion;
	}

	cui = orxObject_CreateFromConfig("CombatUI");
	setPauseMenuPosition(Scene::createVector(-1150.0, 400.0, 0));
	initializeUITextAt(Scene::createVector(-1600, 560, -0.1));
	orxObject_Enable(uiTextSprite, orxTRUE);
}

void Combat::loadPlayerData(Player* player) {
	Scene::loadPlayerData(player);
	playerStats->loadEntity(player);
}

void Combat::loadEnemyData(Enemy* enemy) {
	this->enemy = enemy;
	enemyStats->loadEntity(enemy);
}

void Combat::loadUIText(orxSTRING text) {
	orxObject_EnableRecursive(cui, orxFALSE);
	orxObject_Enable(selector, orxFALSE);
	Scene::loadUIText(text);
}

void Combat::dismissUIText() {
	Scene::dismissUIText();
	orxObject_Enable(uiTextSprite, orxTRUE);
	orxObject_EnableRecursive(cui, orxTRUE);
	orxObject_Enable(selector, orxTRUE);
}

void Combat::activate(Player* player) {
	Scene::activate(player);
	
	playerPos = player->getPosition();
	player->setPosition(Scene::createVector(-1230, 450, 0));
	orxObject_SetScale(player->getEntity(), &scaleUp);

	enemy->setPosition(Scene::createVector(-1100, 200, 0));
	orxObject_SetScale(enemy->getEntity(), &scaleUp);

	orxObject_SetTargetAnim(player->getEntity(), "IdleUAnim");
	orxCHAR anim[30];
	orxString_Print(anim, "IdleDAnim%s", enemy->getName());
	orxObject_SetTargetAnim(enemy->getEntity(), anim);

	hasPotions = playerHasPotions();
}

void Combat::deactivate() {
	enemy->despawn();
	player->setPosition(playerPos);
	orxObject_SetScale(player->getEntity(), &scaleNormal);
	Scene::deactivate();
}

orxBOOL Combat::playerHasPotions() {
	for (int i = 0; i < POTIONCOUNT; i++) {
		if (player->amountOfPotionOwned((PotionType)i) > 0) {
			return orxTRUE;
		}
	}
	return orxFALSE;
}

SceneType Combat::makeMove(Move move) {
	SceneType toReturn = COMBAT;
	orxCHAR uiText[200];
	switch (move) {
		case RUN:
			orxString_Print(uiText, "Ran away.");
			toReturn = EXPLORATION;
			break;
		case ATTACK:
		{
			orxBOOL hasMods = orxFALSE;
			for (int i = 0; i < 3; i++) {
				if (modifiers[i] != 0) {
					hasMods = orxTRUE;
					break;
				}
			}
			orxCHAR mods[100];
			memset(mods, 0, sizeof(mods));
			if (hasMods) {
				player->alterSpeed(modifiers[0]);
				player->alterStrength(modifiers[1]);
				player->alterDefense(modifiers[2]);
				orxString_Print(mods, "Obtained %d speed, %d strength, %d defense for this turn.\n",
								modifiers[0], modifiers[1], modifiers[2]);
			}

			Entity* firstAttacker = player;
			Entity* secondAttacker = enemy;
			if (enemy->getSpeed() > player->getSpeed()) {
				firstAttacker = enemy;
				secondAttacker = player;
			}

			orxCHAR attacks[100];
			int dmg = Entity::entityAttack(firstAttacker, secondAttacker);
			orxString_Print(attacks, "%s dealt %d damage.",
							firstAttacker->getName(), dmg);
			if (secondAttacker->getHP() > 0) {
				dmg = Entity::entityAttack(secondAttacker, firstAttacker);
				orxString_Print(attacks, "%s\n%s dealt %d damage.",
								attacks, secondAttacker->getName(), dmg);
			}

			if (hasMods) {
				player->alterSpeed(-modifiers[0]);
				player->alterStrength(-modifiers[1]);
				player->alterDefense(-modifiers[2]);
				memset(modifiers, 0, sizeof(modifiers));
			}
			if (specialMoveCooldown > 0) {
				specialMoveCooldown--;
			}

			orxString_Print(uiText, "%s%s", mods, attacks);
		}
			break;
		case SPECIAL_MOVE:
		{
			if (specialMoveCooldown > 0) {
				orxObject_AddSound(selector, "ErrorSound");
				orxString_Print(uiText, "Special move requires %d more turns to cool down.",
								specialMoveCooldown);
				loadUIText(uiText);
				return COMBAT;
			}
			int level = player->getLevel().getLevel();
			switch (player->getType()) {
				case MAGIC:
				{
					int dHP = 10 * (level + 1);
					int dv = 7 * (level + 2);
					player->alterSpeed(-dv);
					player->alterHP(dHP);
					int dmg = Entity::entityAttack(enemy, player);
					player->alterSpeed(dv);
					specialMoveCooldown = orxMAX(6, level);
					orxString_Print(uiText,
									"-%d speed until next turn. Healed %d HP.\n%s dealt %d damage.\nCooldown: %d",
									dv, dHP, enemy->getName(), dmg, specialMoveCooldown);
				}
					break;
				case SPEED:
				{
					int dstr = 2 * (level + 1);
					int ddef = (level + 2);
					int dmg = Entity::entityAttack(enemy, player);
					modifiers[1] += dstr;
					modifiers[2] -= ddef;
					specialMoveCooldown = orxMAX(8, level);
					orxString_Print(uiText,
									"+%d strength and -%d defense next turn.\n%s dealt %d damage.\nCooldown: %d",
									dstr, ddef, enemy->getName(), dmg, specialMoveCooldown);
				}
					break;
				case MELEE:
				{
					int ddef = 4 * (level + 1);
					int dv = 2 * (level + 2);
					int dmg = Entity::entityAttack(enemy, player);
					modifiers[0] -= dv;
					modifiers[2] += ddef;
					specialMoveCooldown = orxMAX(7, level);
					orxString_Print(uiText,
									"-%d speed and +%d defense next turn.\n%s dealt %d damage.\nCooldown: %d",
									dv, ddef, enemy->getName(), dmg, specialMoveCooldown);
				}
					break;
				case RANGE:
				{
					int dstr = 5 * (level + 1);
					int dv = 3 * (level + 2);
					int dmg = Entity::entityAttack(enemy, player);
					modifiers[0] -= dv;
					modifiers[1] += dstr;
					specialMoveCooldown = orxMAX(8, level);
					orxString_Print(uiText,
									"-%d speed and +%d strength next turn.\n%s dealt %d damage.\nCooldown: %d",
									dv, dstr, enemy->getName(), dmg, specialMoveCooldown);
				}
					break;
				default:
					break;
			}
		}
			break;
		case USE_ITEM:
			if (hasPotions) {
				isSelectingPotion = orxTRUE;

				orxObject_Enable(potionName, orxTRUE);
				orxObject_Enable(potionEffect, orxTRUE);
				orxObject_Enable(allPotions[selectedPotion], orxTRUE);
				orxObject_EnableRecursive(potionHelp, orxTRUE);
				if (player->amountOfPotionOwned(selectedPotion) == 0) {
					selectPotion(1);
				}
				updatePotionDescription();
			} else {
				orxObject_AddSound(selector, "ErrorSound");
			}
			return COMBAT;
	}
	if (enemy->getHP() <= 0) {
		player->defeat(enemy);
		orxString_Print(uiText, "%s\n%s defeated the %s!",
						uiText, player->getName(), enemy->getName());
		toReturn = EXPLORATION;
	} else if (player->getHP() <= 0) {
		orxString_Print(uiText, "%s\n%s died.", uiText, player->getName());
		toReturn = MAIN_MENU;
	}
	playerStats->reloadData();
	enemyStats->reloadData();
	loadUIText(uiText);
	return toReturn;
}

void Combat::consumePotions() {
	Potion* p = Potion::getCopyOf(selectedPotion);
	orxCHAR text[100];
	orxCHAR effect[50];
	double delta;
	switch (selectedPotion) {
		case SPEEDBOOST:
			delta = player->getSpeed() * orxMath_Pow(p->getAmount(), desiredQuantity);
			modifiers[0] += delta;
			orxString_Print(effect, "Increased speed by %.2f this turn.", delta);
			break;
		case STRBOOST:
			delta = player->getStrength() * orxMath_Pow(p->getAmount(), desiredQuantity);
			modifiers[1] += delta;
			orxString_Print(effect, "Increased strength by %.2f this turn.", delta);
			break;
		case DEFBOOST:
			delta = player->getDefense() * orxMath_Pow(p->getAmount(), desiredQuantity);
			modifiers[2] += delta;
			orxString_Print(effect, "Increased defense by %.2f this turn.", delta);
			break;
		case QUICKHEAL_2:
		case QUICKHEAL_5:
		case QUICKHEAL_10:
		case QUICKHEAL_20:
		case QUICKHEAL_50:
			delta = p->getAmount() * desiredQuantity;
			player->alterHP(delta);
			orxString_Print(effect, "Gained %d HP.", (int)delta);
			break;
		default:
			break;
	}
	orxString_Print(text, "Used %d vial(s) of %s.\n%s", desiredQuantity, p->getName(), effect);
	loadUIText(text);
	player->changePotionAmount(selectedPotion, -desiredQuantity);
	playerStats->reloadData();
}

SceneType Combat::update(const orxCLOCK_INFO* clockInfo) {
	if (isSelectingPotion) {
		orxBOOL switchPotion = orxFALSE;
		int prevQuantity = desiredQuantity;
		int direction = 1;
		if (getKeyDown((orxSTRING)"Pause")) {
			isSelectingPotion = orxFALSE;
		} else if (getKeyDown((orxSTRING)"Enter")) {
			consumePotions();
			hasPotions = playerHasPotions();
			isSelectingPotion = orxFALSE;
			desiredQuantity = 1;
		} else if (getKeyDown((orxSTRING)"GoDown") &&
				   desiredQuantity > 1) {
			desiredQuantity--;
		} else if (getKeyDown((orxSTRING)"GoUp") &&
				   desiredQuantity < player->amountOfPotionOwned(selectedPotion)) {
			desiredQuantity++;
		} else if (getKeyDown((orxSTRING)"GoLeft")) {
			switchPotion = orxTRUE;
			direction = -1;
		} else if (getKeyDown((orxSTRING)"GoRight")) {
			switchPotion = orxTRUE;
		}
		if (switchPotion) {
			desiredQuantity = 1;
			selectPotion(direction);
			updatePotionDescription();
			orxObject_AddSound(selector, "SelectorSound");
		} else if (desiredQuantity != prevQuantity) {
			updatePotionDescription();
			orxObject_AddSound(selector, "TickSound");
		} else if (!isSelectingPotion) {
			orxObject_Enable(potionName, orxFALSE);
			orxObject_Enable(potionEffect, orxFALSE);
			orxObject_Enable(allPotions[selectedPotion], orxFALSE);
			orxObject_EnableRecursive(potionHelp, orxFALSE);
		}
	} else {
		orxBOOL hadText = hasText;
		SceneType type = Scene::update(clockInfo);
		if (type != COMBAT) {
			return type;
		}
		if (paused || hadText) {
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
				nextSceneType = makeMove(moves[y][x]);
				return COMBAT;
			}
			selChanged = orxFALSE;
		}
		if (selChanged) {
			orxObject_SetPosition(selector, &pos);
			orxObject_AddSound(selector, "SelectorSound");
		}
	}
	return nextSceneType;
}

void Combat::selectPotion(int direction) {
	orxObject_Enable(allPotions[selectedPotion], orxFALSE);
	do {
		int newval = ((int)selectedPotion + (POTIONCOUNT + direction)) % POTIONCOUNT;
		selectedPotion = (PotionType)newval;
	} while (player->amountOfPotionOwned(selectedPotion) == 0);
	orxObject_Enable(allPotions[selectedPotion], orxTRUE);
}

void Combat::updatePotionDescription() {
	Potion* p = Potion::allPotions[selectedPotion];

	orxCHAR text[30];
	orxString_Print(text, "Potion: %s", p->getName());
	orxObject_SetTextString(potionName, text);

	switch (p->getType()) {
		case QUICKHEAL_2:
		case QUICKHEAL_5:
		case QUICKHEAL_10:
		case QUICKHEAL_20:
		case QUICKHEAL_50:
			orxString_Print(text, "Heals: %d (%dx) -> %d",
							(int)p->getAmount(), desiredQuantity, (int)(p->getAmount() * desiredQuantity));
			break;
		case STRBOOST:
		case SPEEDBOOST:
		case DEFBOOST:
			orxString_Print(text, "Effect: +%d%% (%dx) -> +%d%%",
							(int)(p->getAmount() * 100), desiredQuantity,
							(int)(pow(1 + p->getAmount(), desiredQuantity) * 100 - 100));
			break;
		default:
			break;
	}
	orxObject_SetTextString(potionEffect, text);
}

SceneType Combat::getSceneType() {
	return COMBAT;
}
