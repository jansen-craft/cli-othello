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
    noMoves = 0;
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
    if(move == "skip"){ //Skip Move
        game::make_move(move);
        noMoves++;
        return;
    }
    noMoves = 0;
    int curPlayer;
    int nextPlayer;

    //Check Whose Move it is 
    if(next_mover() == 0){ //In this case 0 is human which is black
        curPlayer = 1;
        nextPlayer = 2;
    } else if(next_mover() == 2){ //In this case 2 is computer which is white
        curPlayer = 2;
        nextPlayer = 1;
    } else { //Neither Person's turn? Must've been a solar flare
        cout << "oh?... What have you done!!!" << endl;
    }

    string cleanMv = cleanMove(move); //Clean Move

    //Turn A-H into Index Column
    int col = (cleanMv.at(0) - 'A');
    //Turn 1-8 into Index Row
    int row = (cleanMv.at(1) - '1');

    //Make Move
    board[row][col].set_state(curPlayer);
    
    //Make Flips
    //Up
    flipDir(row, col, -1, 0, curPlayer, nextPlayer);
    //Right
    flipDir(row, col, 0, 1, curPlayer, nextPlayer);
    //Down
    flipDir(row, col, 1, 0, curPlayer, nextPlayer);
    //Left
    flipDir(row, col, 0, -1, curPlayer, nextPlayer);
    //Up-Right
    flipDir(row, col, -1, 1, curPlayer, nextPlayer);
    //Down-Left
    flipDir(row, col, 1, -1, curPlayer, nextPlayer);
    //Down-Right
    flipDir(row, col, 1, 1, curPlayer, nextPlayer);
    //Up-Left
    flipDir(row, col, -1, -1, curPlayer, nextPlayer);

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
    return new Othello(*this);
}
// Compute all the moves that the next player can make:
void Othello::compute_moves(std::queue<std::string>& moves)const{
    //Must Use Strings
    string move = "";
    for (char i = 'A'; i < 'I'; i++){
        for (char j = '1'; j < '9'; j++){
            move += i;
            move += j;
            if(is_legal(move)){
                moves.push(move);
            }
            move = "";
        }
    }
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
    string whosTurn;
    if(next_mover() == 0){ //In this case 0 is human which is black
        whosTurn = "Black";
    } else if(next_mover() == 2){ //In this case 2 is computer which is white
        whosTurn = "White";
    } else { //Neither Person's turn?
        whosTurn = "Nobody";
    }
    cout << "It is " << whosTurn << "'s turn." << endl;
    cout << "If you have no moves enter: skip" << endl;
    return;
}
// Evaluate a board position:. NOTE: positive values are good for the computer.
int Othello::evaluate()const{
    int score = 0; // Who is winning - positive for computer
    int tmp = -3;
    for (size_t i = 0; i < 8; i++){
        for (size_t j = 0; j < 8; j++){
            tmp = board[i][j].get_state();
            if(tmp == 1){ //black gets a point (Human)
                score--;
            } else if(tmp == 2){ //White gets a point (Computer)
                score++;
            }
        }
    }
    return score;
}
// Return true if the current game is finished:
bool Othello::is_game_over()const{
    if(noMoves >= 2){
        return true;
    }
    return false;
}
// Return true if the given move is legal for the next player:
bool Othello::is_legal(const std::string& move)const{
    bool can_move = 0;
    if(move == "skip"){
        //Must Use Strings
        string tMove = "";
        for (char i = 'A'; i < 'I'; i++){
            for (char j = '1'; j < '9'; j++){
                tMove += i;
                tMove += j;
                if(is_legal(tMove)){
                    can_move = 1;
                }
                tMove = "";
            }
        }
        if(can_move == 0){
            return true;
        }
    }

    int curPlayer;
    int nextPlayer;

    //Check Whose Move it is 
    if(next_mover() == 0){ //In this case 0 is human which is black
        curPlayer = 1;
        nextPlayer = 2;
    } else if(next_mover() == 2){ //In this case 2 is computer which is white
        curPlayer = 2;
        nextPlayer = 1;
    } else { //Neither Person's turn? Impossible!!
        cout << "WITCHCRAFT!!!" << endl;
    }

    string cleanMv = cleanMove(move);
    if(cleanMv == "invalid"){ //if not a valid string for move
        return false;
    }

    //Turn A-H into Index Column
    int col = (cleanMv.at(0) - 'A');
    //Turn 1-8 into Index Row
    int row = (cleanMv.at(1) - '1');

    if(board[row][col].get_state() != 0) return false; //IF not empty then this is not a move

    //Check if the move is legal

    //Up
    if(searchDirection(row, col, -1, 0, curPlayer, nextPlayer) == 1) return true;
    //Right
    if(searchDirection(row, col, 0, 1, curPlayer, nextPlayer) == 1) return true;
    //Down
    if(searchDirection(row, col, 1, 0, curPlayer, nextPlayer) == 1) return true;
    //Left
    if(searchDirection(row, col, 0, -1, curPlayer, nextPlayer) == 1) return true;
    //Up-Right
    if(searchDirection(row, col, -1, 1, curPlayer, nextPlayer) == 1) return true;
    //Down-Left
    if(searchDirection(row, col, 1, -1, curPlayer, nextPlayer) == 1) return true;
    //Down-Right
    if(searchDirection(row, col, 1, 1, curPlayer, nextPlayer) == 1) return true;
    //Up-Left
    if(searchDirection(row, col, -1, -1, curPlayer, nextPlayer) == 1) return true;

    return false;
}

void Othello::flipDir(int row, int col, int rowDir, int colDir, int curPlayer, int nextPlayer){
    bool foundFlip = 0;
    bool foundOther = 0;
    bool foundBad = 0;
    int flipCol = -1;
    int flipRow = -1;
    int Ncol = col; //Temp column
    int Nrow = row; //Temp row

    Ncol += colDir;
    Nrow += rowDir;
    //Looks for flips
    while(Ncol >= 0 && Ncol <= 7 && Nrow >= 0 && Nrow <= 7){
        if(board[Nrow][Ncol].get_state() == nextPlayer && foundBad == 0) foundOther = 1; //Found First other
        if(foundOther == 1 && board[Nrow][Ncol].get_state() == curPlayer){ //Found Flip spot
            if(foundFlip == 0){
                flipCol = Ncol;
                flipRow = Nrow;
                foundFlip = 1;
            }
        }
        if(board[Nrow][Ncol].get_state() == 0){  //Not possible for this direction
            foundBad = 1;
            foundOther = 0;
        }
        Ncol += colDir;
        Nrow += rowDir;
    }

    //flip them
    if(foundFlip == 1){ //This direction has flips
        //Flip from original spot to flip spot
        col += colDir;
        row += rowDir;
        while(col != flipCol || row != flipRow){
            if(board[row][col].get_state() == nextPlayer) board[row][col].flip(); //Found First next
            col += colDir;
            row += rowDir;
        }

    }
    return;
}

bool Othello::searchDirection(int row, int col, int rowDirection, int colDirection, int curPlayer, int nextPlayer)const{
    bool foundOther = 0;
    col += colDirection;
    row += rowDirection;
    while(col >= 0 && col <= 7 && row >= 0 && row <= 7){
        if(board[row][col].get_state() == nextPlayer) foundOther = 1; //Found First next
        if(foundOther == 1 && board[row][col].get_state() == curPlayer) return true; //All next then cur
        if(foundOther == 0 && board[row][col].get_state() == curPlayer) break; //All Cur with no next Before
        if(board[row][col].get_state() == 0) break; //Not possible for this direction
        col += colDirection;
        row += rowDirection;
    }
    return false;
}

string cleanMove(string move){
    //Return immediately invalid if not two characters
    if(move.length() != 2){
        return "invalid";
    }

    //Turn it all to uppercase
    string Umove ="";
    for (size_t i = 0; i < 2; i++){
        if(move.at(i) >= 'a' && move.at(i) <= 'z'){
            Umove += toupper(move.at(i));
        } else {
            Umove += move.at(i);
        }
    }

    //Return invalid if first char is not between A&H
    if(Umove.at(0) < 'A' || Umove.at(0) > 'H') return "invalid";
    //Return invalid if second char is not between 1&8
    if(Umove.at(1) < '1' || Umove.at(1) > '8') return "invalid";
    //If it reaches here the move must be on the board somewhere

    string cleanString = "";
    cleanString += Umove.at(0);
    cleanString += Umove.at(1);

    return cleanString;
}