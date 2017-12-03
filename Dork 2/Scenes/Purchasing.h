//
//  Purchasing.h
//  Dork 2
//
//  Created by Alessandro Vinciguerra on 01/12/2017.
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

#ifndef Purchasing_h
#define Purchasing_h

#include "Scene.h"
#include "StatViewer.h"

class Purchasing : public Scene {
protected:
	int currentSelection = 0;
	int selectionLimit;
	orxOBJECT* selectorArrow;
	orxVECTOR defaultPos;
	virtual orxBOOL makePurchase() = 0;

	StatViewer* statViewer;

	Purchasing();
public:
	virtual void activate();

	virtual SceneType update(const orxCLOCK_INFO*);
};

#endif
