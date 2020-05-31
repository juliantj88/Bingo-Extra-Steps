.default: all

all: azul

clean:
	rm -f azul *.o

azul: main.o PlayerBoard.o Player.o GameBoard.o GameEngine.o LinkedList.o GameEngineAI.o
	g++ -Wall -Werror -std=c++14 -g -O -o $@ $^

%.o: %.cpp
	g++ -Wall -Werror -std=c++14 -g -O -c $^
