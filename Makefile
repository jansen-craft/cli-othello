CC = g++
FLAGS = -Wall

othello: samplemain.o othello.o game.o spaces.o 
	$(CC) $(FLAGS) $^ -o $@

samplemain.o: samplemain.cpp othello.hpp
	$(CC) $(FLAGS) -c $<

othello.o: othello.cpp othello.hpp colors.hpp
	$(CC) $(FLAGS) -c $<

game.o: game.cpp game.hpp
	$(CC) $(FLAGS) -c $<

spaces.o: spaces.cpp spaces.hpp colors.hpp
	$(CC) $(FLAGS) -c $<

clean:
	@-rm -f *.o
	@-rm -f othello
