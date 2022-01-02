all:
	g++ main.cpp mathhelper.cpp -o main -Wall `sdl2-config --cflags --libs`
run:
	./main.exe
macos: 
	g++ main.cpp -std=c++11 mathhelper.cpp -o main -Wall -I/opt/homebrew/include -D_THREAD_SAFE -L/opt/homebrew/lib -lSDL2