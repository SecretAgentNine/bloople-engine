all: compile link

compile:
	g++ -I./source/ -I/usr/include/SDL2/ -I/usr/include/SDL_image/ -std=c++11 -c source/*.cpp
	mv *.o obj/

link:
	g++ -std=c++11 -o game -pthread obj/main.o obj/game_logic.o obj/components.o obj/message_bus.o obj/framework.o obj/tinyxml2.o -lSDL2_mixer -lSDL2_image -lSDL2

framework:
	g++ -I./source -I/usr/include/SDL2 -I/usr/include/SDL_image/ -std=c++11 -c source/framework.cpp
	mv *.o obj/
	make link

message_bus:
	g++ -I./source -I/usr/include/SDL2 -I/usr/include/SDL_image/ -std=c++11 -c source/message_bus.cpp
	mv *.o obj/
	make link

components:
	g++ -I./source -I/usr/include/SDL2 -I/usr/include/SDL_image/ -std=c++11 -c source/components.cpp
	mv *.o obj/
	make link

main:
	g++ -I./source -I/usr/include/SDL2 -I/usr/include/SDL_image/ -std=c++11 -c source/main.cpp
	mv *.o obj/
	make link

game_logic:
	g++ -I./source -I/usr/include/SDL2 -I/usr/include/SDL_image/ -std=c++11 -c source/game_logic.cpp
	mv *.o obj/
	make link

upload:
	git add source/*
	git commit
	git push
