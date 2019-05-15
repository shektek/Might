CC=g++ -g -Wall
CFLAGS=-std=c++11 -I.
LDFLAGS=-lncurses -lSDL2main -lSDL2 -lSDL2_image
SRCDIR = ./
DEPS = $(SRCDIR)Point2D.h $(SRCDIR)Tile.h $(SRCDIR)Unit.h $(SRCDIR)ArrangementStrategy.h $(SRCDIR)Army.h $(SRCDIR)BattleMap.h $(SRCDIR)GameMaster.h $(SRCDIR)Player.h $(SRCDIR)OrdinalPosition.h $(SRCDIR)AppHost.h $(SRCDIR)ArmyFactory.h $(SRCDIR)Faction.h $(SRCDIR)NavigableGrid.h $(SRCDIR)sdl/ImageCache.h $(SRCDIR)sdl/RenderSDL.h $(SRCDIR)sdl/SDLHost.h $(SRCDIR)sdl/AnimatedImage.h $(SRCDIR)sdl/AnimatedUnit.h
OBJDIR = ./obj/
OBJ = $(OBJDIR)Point2D.o $(OBJDIR)Tile.o $(OBJDIR)Unit.o $(OBJDIR)Army.o $(OBJDIR)BattleMap.o $(OBJDIR)main.o $(OBJDIR)GameMaster.o $(OBJDIR)Player.o $(OBJDIR)ArmyFactory.o $(OBJDIR)Faction.o $(OBJDIR)NavigableGrid.o $(OBJDIR)sdl/ImageCache.o $(OBJDIR)sdl/RenderSDL.o $(OBJDIR)sdl/SDLHost.o $(OBJDIR)sdl/AnimatedImage.o $(OBJDIR)/sdl/AnimatedUnit.o
BINDIR = ./bin/
PROJECT = might

$(OBJDIR)%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

$(BINDIR)$(PROJECT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJ)
