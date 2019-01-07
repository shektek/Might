CC=g++ -g
CFLAGS=-std=c++11 -I.
LDFLAGS=-lncurses -lSDL2main -lSDL2 -lSDL2_image
SRCDIR = ./
DEPS = $(SRCDIR)Point2D.h $(SRCDIR)Tile.h $(SRCDIR)Unit.h $(SRCDIR)ArrangementStrategy.h $(SRCDIR)Army.h $(SRCDIR)BattleMap.h $(SRCDIR)RenderConsole.h $(SRCDIR)ControlConsole.h $(SRCDIR)GameMaster.h $(SRCDIR)Player.h $(SRCDIR)RenderConsoleColours.h $(SRCDIR)OrdinalPosition.h $(SRCDIR)AppHost.h $(SRCDIR)ArmyFactory.h $(SRCDIR)ConsoleHost.h $(SRCDIR)NavigableGrid.h $(SRCDIR)sdl/RenderSDL.h $(SRCDIR)sdl/SDLHost.h
OBJDIR = ./obj/
OBJ = $(OBJDIR)Point2D.o $(OBJDIR)Tile.o $(OBJDIR)Unit.o $(OBJDIR)Army.o $(OBJDIR)BattleMap.o $(OBJDIR)main.o $(OBJDIR)RenderConsole.o $(OBJDIR)ControlConsole.o $(OBJDIR)GameMaster.o $(OBJDIR)Player.o $(OBJDIR)ConsoleHost.o $(OBJDIR)ArmyFactory.o $(OBJDIR)NavigableGrid.o $(OBJDIR)sdl/RenderSDL.o $(OBJDIR)sdl/SDLHost.o
BINDIR = ./bin/
PROJECT = might

$(OBJDIR)%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

$(BINDIR)$(PROJECT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)

clean:
	rm -f $(OBJ)
