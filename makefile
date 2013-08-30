all:
	g++  -o ConwaysGameofLife *.cpp `sdl-config --cflags --libs`
