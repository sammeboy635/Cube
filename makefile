main: glad.o
	g++ src/main.cpp lib/glad.o -lglfw -o main
	
glad.o: 
	gcc -o lib/glad.o -Wall -c incl/glad/glad.c