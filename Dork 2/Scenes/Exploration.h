//
//  Exploration.h
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

#ifndef Exploration_h
#define Exploration_h

#include <list>

#include "Scene.h"

class Exploration : public Scene {
	orxCAMERA* camera;
	const orxVECTOR UITextOffset = Scene::createVector(-500, 160, 0.9);

	std::list<Enemy*> existingEnemies;
	orxFLOAT timeSinceEnemySpawn = 0;

	/**
	 * Spawns a new random enemy in a random location (between
	 * the edge of the player's view and a few hundred pixels outside
	 * of that)
	 */
	void spawnEnemy();

	/**
	 * Tells entities in the scene whether animations
	 * should be playing
	 * @param enable whether animations should be enabled
	 */
	void enableAnimation(orxBOOL enable);
public:
	/**
	 * Construct new Exploration scene
	 * @param player current player
	 * @param cam reference to the camera
	 */
	Exploration(Player* player, orxCAMERA* cam);

	virtual void activate();

	/**
	 * Resets the world state by clearing enemies
	 * and resetting music and position
	 * @param player player to load into reset world
	 */
	void resetWorld(Player* player);

	/**
	 * Restarts the music from the beginning
	 */
	void resetMusic();

	virtual SceneType update(const orxCLOCK_INFO*);
	virtual SceneType getSceneType();

	virtual orxSTATUS EventHandler(const orxEVENT*);
};

#endif
