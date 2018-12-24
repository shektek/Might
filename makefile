CC=g++
CFLAGS=-std=c++11 -I.
LDFLAGS=-lncurses
SRCDIR = ./
DEPS = $(SRCDIR)Point2D.h $(SRCDIR)Tile.h $(SRCDIR)Unit.h $(SRCDIR)ArrangementStrategy.h $(SRCDIR)Army.h $(SRCDIR)BattleMap.h $(SRCDIR)RenderConsole.h $(SRCDIR)ControlConsole.h $(SRCDIR)GameMaster.h $(SRCDIR)Player.h $(SRCDIR)RenderConsoleColours.h
OBJDIR = ./obj/
OBJ = $(OBJDIR)Point2D.o $(OBJDIR)Tile.o $(OBJDIR)Unit.o $(OBJDIR)Army.o $(OBJDIR)BattleMap.o $(OBJDIR)main.o $(OBJDIR)RenderConsole.o $(OBJDIR)ControlConsole.o $(OBJDIR)GameMaster.o $(OBJDIR)Player.o
BINDIR = ./bin/
PROJECT = might

$(OBJDIR)%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS)

$(BINDIR)$(PROJECT): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
