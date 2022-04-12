
#include "othello.h"
#include "colors.h"
#include <iostream>
#include <iomanip>
using namespace std;
using namespace main_savitch_14;

Othello::Othello(){
    //TODO
    ;
}

// Have the next player make a specified move:
void Othello::make_move(const std::string& move){
    //TODO 6A
    string Umove ="";
    for (size_t i = 0; i < move.size(); i++){
        if(move.at(i) >= 'a' && move.at(i) <= 'z'){
            Umove += tolower(move.at(i));
        } else {
            Umove += move.at(i);
        }
    }

    if(Umove == "e3"){
        board[2][4].set_state(2);
        board[3][4].flip();
    } else if(Umove == "f4"){
        board[3][5].set_state(2);
        board[3][4].flip();
    } else if(Umove == "c5"){
        board[4][2].set_state(2);
        board[4][3].flip();
    } else if(Umove == "d6"){
        board[5][3].set_state(2);
        board[4][3].flip();
    } else {
        cout << "ERROR: Invalid Move" << endl;
    }
    //call Parent
    game::make_move(move);
    return;
}
// Restart the game from the beginning:
void Othello::restart(){
    //TODO 6A
    //Reset All Pieces
    for (size_t i = 0; i < 8; i++){
        for (size_t j = 0; j < 8; j++){
            board[i][j].set_state(0);
        }  
    }
    
    //Place First Piece
    board[3][3].set_state(2); //Top Left Middle
    board[3][4].set_state(1); //Top Right Middle
    board[4][3].set_state(1); //Bot Left Middle
    board[4][4].set_state(2); //Bot Right Middle


    //call Parent
    game::restart();
    return;
}


//!!REQUIRED FUNCTIONS
// Return a pointer to a copy of myself:
Othello* Othello::clone()const{
    //TODO
    return NULL;
}
// Compute all the moves that the next player can make:
void Othello::compute_moves(std::queue<std::string>& moves)const{
    //TODO
    return;
}
// Display the status of the current game:
void Othello::display_status()const{
    //TODO
    cout << B_WHITE << BLUE << "             Welcome to " << BOLD << "Othello!" << RESET << B_WHITE << "             " << RESET << endl;
    cout << B_WHITE << ".                                           ." << RESET << endl;

    //Top Letters
    char tmp = 'A';
    cout << B_WHITE << "     ";
    for (size_t k = 0; k < 8; k++){
        cout << "   " << BOLD << BLUE << tmp;
        tmp++;
    }
    cout << "  " <<  "      " << RESET << endl;
    
    //Top Line
    cout << B_WHITE << "      " << B_CYAN;
    for (size_t k = 0; k < 8; k++) cout << "|---";
    cout << "|" << B_WHITE << "      " << RESET << endl;
    
    //Bulk with Pieces
    for (size_t i = 1; i < 9; i++){
        //Piece Row
        cout << B_WHITE << BOLD << BLUE;
        cout << "   " << i << "  ";
        cout << RESET << B_CYAN << "|";
        for (size_t j = 0; j < 8; j++){
            cout << " " << board[i - 1][j] << " |";
        }
        cout << B_WHITE << "      " << RESET << endl;

        //Bottom Lines
        cout << B_WHITE << "      " << B_CYAN;
        for (size_t k = 0; k < 8; k++) cout << "|---";
        cout << "|" << B_WHITE << "      " << RESET << endl;
    }
    cout << B_WHITE << ".                                           ." << RESET << endl;
    cout << "Moves - e3 f4 c5 d6" << endl;
    return;
}
// Evaluate a board position:. NOTE: positive values are good for the computer.
int Othello::evaluate()const{
    //TODO
    return 1;
}
// Return true if the current game is finished:
bool Othello::is_game_over()const{
    //TODO
    return false;
}
// Return true if the given move is legal for the next player:
bool Othello::is_legal(const std::string& move)const{
    //TODO 6A
    string Umove ="";
    for (size_t i = 0; i < move.size(); i++){
        if(move.at(i) >= 'a' && move.at(i) <= 'z'){
            Umove += tolower(move.at(i));
        } else {
            Umove += move.at(i);
        }
    }
    
    if(Umove == "e3" || move == "f4" || move == "c5" || move == "d6"){
        return true;
    }else{
        return false;
    }
}
//!!END