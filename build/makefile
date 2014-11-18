# Compilateur
#CC = ../../../MinGW/bin/mingw32-gcc.exe
CC = gcc
# Flags de compilation
CFLAGS = --std=c99 -Wall -ggdb -g3 -W
# Flags de biblioteque
LDFLAGS = -lmingw32 -lSDL2main -lSDL2  -lSDL2_ttf -lSDL2_image -lglew32 -lopengl32
#LDFLAGS = -lSDL2  -lSDL2_ttf -lSDL2_image -lGLEW -lGL
# Nom de l'executable
Exe = OPENGL.exe

# Fichiers
SRC=$(wildcard ../src/*.c)
OBJ=$(SRC:.c=.o)


all : $(Exe)

$(Exe): $(OBJ)
	@$(CC) -o $@ $^ $(LDFLAGS) $(CFLAGS)

%.o: %.c
	@$(CC) -o $@ -c $< $(CFLAGS)

clean: 
	@del ..\src\*.o

mproper: clean
	@del $(Exe)
