#!/usr/bin/env sh

function build(){
	g++ -std=c++11 -c main.cpp \
	-I./libs/glfw-3.3.6.bin.MACOS/include -I./libs/glew-2.2.0/include && \
	g++ -v -o main.exec main.o libs/glfw-3.3.6.bin.MACOS/lib-arm64/libglfw3.a
}

function run(){
	./main.exec
}

function clean(){
	rm main.o main.exec
}

# build and run
function start(){
	echo "not implement yet"
}

case $1 in
build)
	build
	;;
run)
	run
	;;
clean)
	clean
	;;
start)
	start
	;;
*)
	echo "./bin.sh [build|run|start|clean]"
	;;
esac