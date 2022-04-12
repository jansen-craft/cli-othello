/**
 * @file Spaces.cc
 * @author Jansen Craft
 * @brief Spaces/Cell Class Definition FIle for Othello game
 * @date 2022-04-11
 */

#include "Spaces.h"
#include "colors.h"
using namespace std;

//SPACES Mutator
void Spaces::set_state(int userEntry){
    if(userEntry >= 0 && userEntry <= 2){
        state = userEntry;
    } else {
        cout << "Error(Spaces): Invalid State" << endl;
    }
    return;
}

//SPACES Flip State
void Spaces::flip(){
    if(state == 2){ //White
        state = 1;
    } else if (state == 1){ //Black
        state = 2;
    } else if (state == 0){ //Empty
        cout << "Error(Spaces): Cannot flip empty Spaces" << endl;
    }
    return;
}

//SPACES overloaded output operator
ostream& operator <<(ostream& outs, Spaces s){
    if(s.get_state() == 2){ //White Space
        cout << WHITE << "@" << GREEN;
    } else if (s.get_state() == 1){ //Black Space
        cout << BLACK << "@" << GREEN;
    } else if (s.get_state() == 0){ //Empty Space
        cout << " ";
    }
  return outs;
}