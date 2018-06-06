all: street-artists-simulation

street-artists-simulation: main.cpp
	g++ -std=c++11 -Wall -g main.cpp artist.cpp cleaner.cpp hotel.cpp paintsupply.cpp randomness.cpp supplier.cpp visualisation.cpp wall.cpp wallsegment.cpp -o philosophers -lncurses -pthread
