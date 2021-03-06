
CC = g++
INCLUDES = -I. -I./Engine -I./Engine/ECS -I./SDL/include/SDL2 -I./SDL_Image/include/SDL2
# LDFLAGS = -L./SDL/lib -L./SDL_Image/lib -lSDL2main -lSDL2 -lSDL2_image
LDFLAGS = -lSDL2main -lSDL2 -lSDL2_image
CFLAGS = -Wall -std=gnu++17  $(INCLUDES)

SRC = $(wildcard Engine/*.cpp)
OBJ = $(patsubst %.cpp,%.o,$(SRC))
DEPS = $(wildcard Engine/*.hpp)

%.o: %.cpp $(DEPS)
	$(CC) $(CFLAGS) -o $@ -c $<

main.exe: $(OBJ)
	$(CC) $^ $(LDFLAGS) -o bin/$@

crun: lclean main.exe
	bin/main.exe

run:
	bin/main.exe

.PHONY: clean
clean:
	del /f /q Engine\*.o bin\main.exe

.PHONY: lclean
lclean:
	rm -f Engine/*.o bin/main.exe
