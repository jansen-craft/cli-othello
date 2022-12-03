/**
 * @file spaces.hpp
 * @author Jansen Craft
 * @brief Spaces/Cell Class Declaration FIle for Othello game
 * @date 2022-04-11
 */

#include "iostream"
using namespace std;

class Spaces{
	public:
		Spaces(){state = 0;} //TODO CHANGE THIS TO 0

		//Accessor
		char get_state()const{return state;}

		//Mutator
		void set_state(int userEntry);

		//Flip State
		void flip();

		//Overloaded Output Operator
        friend std::ostream& operator <<(std::ostream& outs, Spaces s);

	private:
		int state; // 0, 1, 2 = empty, red, blue
};
