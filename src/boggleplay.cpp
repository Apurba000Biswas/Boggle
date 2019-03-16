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

using namespace std;

bool isValidBoard(string board);
string getValidBoard(string enteredBoard);

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
    BoggleGUI::labelAllCubes(boggle.getBoard());
    cout<< "Board is: " << board;
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
