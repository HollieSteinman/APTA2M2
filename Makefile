.default: all

all: azul

clean:
	rm -f azul *.o

azul: azul.o Utils.o Tile.o Bag.o Factory.o Mosaic.o GameManager.o Player.o AI.o

	g++ -Wall -Werror -std=c++14 -g -O0 -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
