program:main.cpp glad.o
	g++ -o program main.cpp glad.o -lglfw3 -lGL -lX11 -lpthread -lXrandr -lXi -ldl -lSDL2 -lSDL2_image

glad.o: glad.c
	gcc -c glad.c -o glad.o

clean:
	rm -rf glad.o program
