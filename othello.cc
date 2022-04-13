/**
 * @file othello.cc
 * @author Jansen Craft
 * @brief Othello Class Definition FIle for Othello game. Child of game class
 * @date 2022-04-11
 */

#include "othello.h"
#include "colors.h"
#include <iostream>
#include <iomanip>
using namespace std;
using namespace main_savitch_14;

Othello::Othello(){
    //Set all Pieces empty
    for (size_t i = 0; i < 8; i++){
        for (size_t j = 0; j < 8; j++){
            board[i][j].set_state(0);
        }  
    }
    
    //Place First Pieces
    board[3][3].set_state(2); //Top Left Middle
    board[3][4].set_state(1); //Top Right Middle
    board[4][3].set_state(1); //Bot Left Middle
    board[4][4].set_state(2); //Bot Right Middle
}

// Have the next player make a specified move:
void Othello::make_move(const std::string& move){
    //TODO 6A
    string Umove ="";
    for (size_t i = 0; i < move.size(); i++){
        if(move.at(i) >= 'a' && move.at(i) <= 'z'){
            Umove += toupper(move.at(i));
        } else {
            Umove += move.at(i);
        }
    }

    if(Umove == "C4"){
        board[3][2].set_state(1);
        board[3][3].flip();
    } else if(Umove == "D3"){
        board[2][3].set_state(1);
        board[3][3].flip();
    } else if(Umove == "E6"){
        board[5][4].set_state(1);
        board[4][4].flip();
    } else if(Umove == "F5"){
        board[4][5].set_state(1);
        board[4][4].flip();
    } else {
        cout << "ERROR: Invalid Move" << endl;
    }
    //Call Parent
    game::make_move(move);
    return;
}
// Restart the game from the beginning:
void Othello::restart(){
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


    //Call Parent
    game::restart();
    return;
}

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
    //Header
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
    cout << "Moves - c4 d3 e6 f5" << endl;
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
    //Return immediately false if not two characters
    if(move.length() != 2){
        return false;
    }

    //Turn it all to uppercase
    string Umove ="";
    for (size_t i = 0; i < move.size(); i++){
        if(move.at(i) >= 'a' && move.at(i) <= 'z'){
            Umove += toupper(move.at(i));
        } else {
            Umove += move.at(i);
        }
    }

    //Return false if first char is not between A&H
    if(Umove.at(0) < 'A' || Umove.at(0) > 'H') return false;
    //Return false if second char is not between 1&8
    if(Umove.at(1) < '1' || Umove.at(1) > '8') return false;
    //If it reaches here the move must be on the board somewhere

    //Turn A-H into Index Column
    int col = (Umove.at(0) - 'A');
    //Turn 1-8 into Index Row
    int row = (Umove.at(1) - '1');

    int colTMP = col;
    int rowTMP = row;

    bool foundWhite = 0;
    cout << "r:" << row << " c:" << col << endl; //REMOVE
    if(board[row][col].get_state() != 0) return false; //IF not empty then this is not a move

    //Check if the move is legal

    //Up
    rowTMP--;
    while(colTMP >= 0 && colTMP <= 7 && rowTMP >= 0 && rowTMP <= 7){
        if(board[rowTMP][colTMP].get_state() == 2) foundWhite = 1; //Found First White
        if(foundWhite == 1 && board[rowTMP][colTMP].get_state() == 1) return true; //All white then Black
        if(foundWhite == 0 && board[rowTMP][colTMP].get_state() == 1) break; //Black with no White Before
        if(board[rowTMP][colTMP].get_state() == 0) break; //Not possible for this direction
        rowTMP--;
    }
    colTMP = col;
    rowTMP = row;
    //Right
    colTMP++;
    while(colTMP >= 0 && colTMP <= 7 && rowTMP >= 0 && rowTMP <= 7){
        if(board[rowTMP][colTMP].get_state() == 2) foundWhite = 1; //Found First White
        if(foundWhite == 1 && board[rowTMP][colTMP].get_state() == 1) return true; //All white then Black
        if(foundWhite == 0 && board[rowTMP][colTMP].get_state() == 1) break; //Black with no White Before
        if(board[rowTMP][colTMP].get_state() == 0) break; //Not possible for this direction
        colTMP++;
    }
    colTMP = col;
    rowTMP = row;
    //Down
    rowTMP++;
    while(colTMP >= 0 && colTMP <= 7 && rowTMP >= 0 && rowTMP <= 7){
        if(board[rowTMP][colTMP].get_state() == 2) foundWhite = 1; //Found First White
        if(foundWhite == 1 && board[rowTMP][colTMP].get_state() == 1) return true; //All white then Black
        if(foundWhite == 0 && board[rowTMP][colTMP].get_state() == 1) break; //All Black with no White Before
        if(board[rowTMP][colTMP].get_state() == 0) break; //Not possible for this direction
        rowTMP++;
    }
    colTMP = col;
    rowTMP = row;
    //Left
    colTMP--;
    while(colTMP >= 0 && colTMP <= 7 && rowTMP >= 0 && rowTMP <= 7){
        if(board[rowTMP][colTMP].get_state() == 2) foundWhite = 1; //Found First White
        if(foundWhite == 1 && board[rowTMP][colTMP].get_state() == 1) return true; //All white then Black
        if(foundWhite == 0 && board[rowTMP][colTMP].get_state() == 1) break; //All Black with no White Before
        if(board[rowTMP][colTMP].get_state() == 0) break; //Not possible for this direction
        colTMP--;
    }
    colTMP = col;
    rowTMP = row;
    //Up-Right
    colTMP++;
    rowTMP--;
    while(colTMP >= 0 && colTMP <= 7 && rowTMP >= 0 && rowTMP <= 7){
        if(board[rowTMP][colTMP].get_state() == 2) foundWhite = 1; //Found First White
        if(foundWhite == 1 && board[rowTMP][colTMP].get_state() == 1) return true; //All white then Black
        if(foundWhite == 0 && board[rowTMP][colTMP].get_state() == 1) break; //All Black with no White Before
        if(board[rowTMP][colTMP].get_state() == 0) break; //Not possible for this direction
        colTMP++;
        rowTMP--;
    }
    colTMP = col;
    rowTMP = row;
    //Down-Left
    colTMP--;
    rowTMP++;
    while(colTMP >= 0 && colTMP <= 7 && rowTMP >= 0 && rowTMP <= 7){
        if(board[rowTMP][colTMP].get_state() == 2) foundWhite = 1; //Found First White
        if(foundWhite == 1 && board[rowTMP][colTMP].get_state() == 1) return true; //All white then Black
        if(foundWhite == 0 && board[rowTMP][colTMP].get_state() == 1) break; //All Black with no White Before
        if(board[rowTMP][colTMP].get_state() == 0) break; //Not possible for this direction
        colTMP--;
        rowTMP++;
    }
    colTMP = col;
    rowTMP = row;
    //Down-Right
    colTMP++;
    rowTMP++;
    while(colTMP >= 0 && colTMP <= 7 && rowTMP >= 0 && rowTMP <= 7){
        if(board[rowTMP][colTMP].get_state() == 2) foundWhite = 1; //Found First White
        if(foundWhite == 1 && board[rowTMP][colTMP].get_state() == 1) return true; //All white then Black
        if(foundWhite == 0 && board[rowTMP][colTMP].get_state() == 1) break; //All Black with no White Before
        if(board[rowTMP][colTMP].get_state() == 0) break; //Not possible for this direction
        colTMP++;
        rowTMP++;
    }
    colTMP = col;
    rowTMP = row;
    //Up-Left
    colTMP--;
    rowTMP--;
    while(colTMP >= 0 && colTMP <= 7 && rowTMP >= 0 && rowTMP <= 7){
        if(board[rowTMP][colTMP].get_state() == 2) foundWhite = 1; //Found First White
        if(foundWhite == 1 && board[rowTMP][colTMP].get_state() == 1) return true; //All white then Black
        if(foundWhite == 0 && board[rowTMP][colTMP].get_state() == 1) break; //All Black with no White Before
        if(board[rowTMP][colTMP].get_state() == 0) break; //Not possible for this direction
        colTMP--;
        rowTMP--;
    }

    return false;
}