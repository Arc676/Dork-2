# Makefile for Dork 2
# On Mac, use the Xcode project
# On Linux, use this Makefile to compile Dork 2
# On Windows, use the Visual Studio project
# You need to have a compiled version of Orx for your platform in the lib/ folder
# You may need to change the compiler if you don't have g++ in your PATH
ODIR=obj
OUTDIR=Build
OUTPUT=$(OUTDIR)/Dork\ 2

CC=g++
FLAGS=-std=c++11 -c -o $(ODIR)/$(@F)
LD=-I inc/ -I Dork\ 2/App -I Dork\ 2/Backend -I Dork\ 2/Scenes -I Dork\ 2/Entities -I Dork\ 2/Items -L lib/
LIB=-l orx

OBJS=Main.o StandAlone.o Enemy.o Entity.o Player.o Potion.o Weapon.o Armory.o Combat.o Exploration.o Shop.o Scene.o MainMenu.o Purchasing.o StatViewer.o Level.o
_OBJS=$(patsubst %, $(ODIR)/%, $(OBJS))

ifdef DEBUG
	FLAGS += -g -O0
endif

dork2: $(_OBJS)
	mkdir -p $(OUTDIR) $(ODIR)
	$(CC) $(LD) $(_OBJS) $(LIB) -o $(OUTPUT)
	cp -u Assets/Sound/* $(OUTDIR)
	cp -u Assets/Sprites/* $(OUTDIR)
	cp -u bin/*.ini $(OUTDIR)

$(ODIR)/MainMenu.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Scenes/MainMenu.cpp

$(ODIR)/Purchasing.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Scenes/Purchasing.cpp

$(ODIR)/StatViewer.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Scenes/StatViewer.cpp

$(ODIR)/Enemy.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Entities/Enemy.cpp

$(ODIR)/Potion.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Items/Potion.cpp

$(ODIR)/Weapon.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Items/Weapon.cpp

$(ODIR)/Armory.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Scenes/Armory.cpp

$(ODIR)/Combat.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Scenes/Combat.cpp

$(ODIR)/Exploration.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Scenes/Exploration.cpp

$(ODIR)/Scene.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Scenes/Scene.cpp

$(ODIR)/Shop.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Scenes/Shop.cpp

$(ODIR)/Entity.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Entities/Entity.cpp

$(ODIR)/Main.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/App/Main.cpp

$(ODIR)/Player.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Entities/Player.cpp

$(ODIR)/StandAlone.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/App/StandAlone.cpp

$(ODIR)/Level.o:
	$(CC) $(FLAGS) $(LD) Dork\ 2/Backend/Level.cpp

clean:
	rm -f $(ODIR)/*.o $(OUTPUT)

squeakyclean:
	rm -rf $(OUTDIR) $(ODIR)
