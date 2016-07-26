CC=g++
CFLAGS=
LDFLAGS=-lglu32 -lmingw32 -lsfml-main -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lfmodex
EXEC=release/lsm.exe

SRC = $(wildcard src/*.cpp)
OBJ = $(subst src,obj, $(SRC:.cpp=.o))

all: $(EXEC)

obj/%.o: src/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)
	
$(EXEC): $(OBJ)
	$(CC) -o $(EXEC) $^ $(LDFLAGS)
