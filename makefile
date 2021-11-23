main: glad.o gl.o screen.o logger.o callback.o
	g++ -g src/main.cpp lib/gl.o lib/screen.o lib/callback.o lib/logger.o -lglfw -o main
	
glad.o: 
	gcc -o lib/glad.o -Wall -g -c incl/glad/glad.c
gl.o: 
	gcc -o lib/gl.o -Wall -g -c incl/glad/gl.c
screen.o:
	g++ -o lib/screen.o -Wall -g -c src/util/screen.cpp
logger.o:
	g++ -o lib/logger.o -Wall -g -c src/util/logger.cpp
callback.o:
	g++ -o lib/callback.o -Wall -g -c src/util/callback.cpp