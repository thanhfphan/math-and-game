all:
	g++ main.cpp -o main -Wall `sdl2-config --cflags --libs`
run:
	./main.exe