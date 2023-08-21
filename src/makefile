run: a.out
	./a.out

a.out: main.o game.o player.o
	g++ main.o game.o player.o -o a.out

main.o: main.cpp
	g++ -c main.cpp

game.o: game.cpp
	g++ -c game.cpp

player.o: player.cpp
	g++ -c player.cpp

clean: 
	rm *.o
