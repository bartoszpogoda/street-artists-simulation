all: street-artists-simulation

street-artists-simulation: main.cpp
	g++ -std=c++11 -Wall -g main.cpp fork.cpp philosopher.cpp visualisation.cpp -o philosophers -lncurses -pthread
