run: a.out
	./a.out

a.out: main.o game.o
	g++ main.o game.o -o a.out

main.o: main.cpp
	g++ -c main.cpp

game.o: game.cpp
	g++ -c game.cpp

clean: 
	rm *.o a.out
