# Makefile for Dork 2
# If you're running Mac, you can build using Xcode
# If you're running Linux, this Makefile should help you
# You need to have a compiled version of Orx for your platform in the lib/ folder
CC=/home/ale/Downloads/bin/x86_64-w64-mingw32-g++
FLAGS=-std=c++11 -c
LD=-I inc/ -I Dork\ 2/App -I Dork\ 2/Backend -I Dork\ 2/Scenes -I Dork\ 2/Entities -I Dork\ 2/Items  -L lib/
LIB=-l orx
OBJS=Main.o StandAlone.o Enemy.o Entity.o Player.o Potion.o Weapon.o Armory.o Combat.o Exploration.o Shop.o

dork2: $(OBJS)
	$(CC) $(LD) $(OBJS) $(LIB) -o Build/Dork\ 2
	cp -u Music/* Build
	cp -u Sprites/* Build
	cp -u bin/*.ini Build

Enemy.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Entities/Enemy.cpp

Potion.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Items/Potion.cpp

Weapon.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Items/Weapon.cpp

Armory.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Scenes/Armory.cpp

Combat.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Scenes/Combat.cpp

Exploration.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Scenes/Exploration.cpp

Shop.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Scenes/Shop.cpp

Entity.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Entities/Entity.cpp

Main.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/App/Main.cpp

Player.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Entities/Player.cpp

StandAlone.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/App/StandAlone.cpp

clean:
	rm Build/Dork\ 2 *.o
