#include "game.h"
#include "Spaces.h"
using namespace std;
using namespace main_savitch_14;
//Othello Class
class Othello:public game{
    public:
        Othello();


		// Have the next player make a specified move:
		void make_move(const std::string& move);
		// Restart the game from the beginning:
		void restart();


		// Return a pointer to a copy of myself:
		Othello* clone()const;
		// Compute all the moves that the next player can make:
		void compute_moves(std::queue<std::string>& moves)const;
		// Display the status of the current game:
		void display_status()const;
		// Evaluate a board position:
		// NOTE: positive values are good for the computer.
		int evaluate()const;
		// Return true if the current game is finished:
		bool is_game_over()const;
		// Return true if the given move is legal for the next player:
		bool is_legal(const std::string& move)const;
        //!!END

    private:
        Spaces board[8][8];
        /* a two-dimensional array of Spaces, pieces, or pointers1 to Spaces or pieces, where the Spaces are another class which you have written */
};