CC=g++
STD=-std=c++17
CFLAGS=-Wall -Wextra
INC_PATH=-I"./libs/" -I/usr/include/lua5.3
SRC=$(shell find src -name '*.cpp')
LFLAGS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -llua5.3 -ltinyxml2
EXEC=game_engine.out

build:
	$(CC) $(CFLAGS) $(STD) $(INC_PATH) $(SRC) $(LFLAGS) -o $(EXEC)

run:
	./$(EXEC)

clean:
	rm $(EXEC)