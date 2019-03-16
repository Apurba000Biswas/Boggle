// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <string>
#include<stdio.h>
#include<stdlib.h>
#include "lexicon.h"
#include "bogglegui.h"
#include "simpio.h"
#include "strlib.h"
#include "Boggle.h"
#include "console.h"

using namespace std;

bool isValidBoard(string board);
string getValidBoard(string enteredBoard);
void printBoard(string board);

void playOneGame(Lexicon& dictionary) {
    // create gui with 4 by 4 grid
    BoggleGUI::initialize(4,4);
    string board;
    if(!getYesOrNo("Do you want to generate a random board?")){
        // get board from user
        board = getLine("Type the 16 letters to appear on the board:");
        board = getValidBoard(board);
    }
    Boggle boggle(dictionary, board);
    board = boggle.getBoard();
    BoggleGUI::labelAllCubes(board);
    printBoard(board);
}

void printBoard(string board){
    clearConsole();
    cout<< "Its your turn!";
    for(int i=0; i<board.size(); i++){
        if(i%4 == 0){
            cout << endl;
        }
        cout << board.at(i);
    }
}

string getValidBoard(string enteredBoard){
    while(!isValidBoard(enteredBoard)){
        // not a valid board try again
        enteredBoard = getLine("That is not a valid 16-letter board string. Try again.");
    }
    return toUpperCase(enteredBoard);
}

bool isValidBoard(string board){
    if(board.size() == 16){
        // its 16 letter length
        for(int i=0; i<16; i++){
            if(isalpha(board.at(i)) == 0){
                return false;
            }
        }
        return true;
    }else{
        return false;
    }
}
