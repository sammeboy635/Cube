main: glad.o gl.o
	g++ src/main.cpp lib/gl.o -lglfw -o main
	
glad.o: 
	gcc -o lib/glad.o -Wall -c incl/glad/glad.c
gl.o: 
	gcc -o lib/gl.o -Wall -c incl/glad/gl.c