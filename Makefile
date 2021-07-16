CC = gcc

all: 
	$(CC) main.c -o golife -I include -L lib -l raylib -l kernel32 -l gdi32 -l winmm -l opengl32