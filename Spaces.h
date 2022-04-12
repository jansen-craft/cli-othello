#include "iostream"
using namespace std;

class Spaces{
	public:
		Spaces(){state = 1;} //TODO CHANGE THIS TO 0

		//Accessor
		char get_state()const{return state;}

		//Mutator
		void set_state(int userEntry);

		//Flip State
		void flip();

        friend std::ostream& operator <<(std::ostream& outs, Spaces s);

	private:
		int state;
		/*
		0 - empty
		1 - black
		2 - white
		*/
};