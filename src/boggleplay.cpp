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

using namespace std;

bool isValidBoard(string board);

void playOneGame(Lexicon& dictionary) {
    // create gui with 4 by 4 grid
    BoggleGUI::initialize(4,4);
    if(getYesOrNo("Do you want to generate a random board?")){
        // generate random board
    }else{
        // get board from user
        string enterdBoard = getLine("Type the 16 letters to appear on the board:");
        while(!isValidBoard(enterdBoard)){
            // not a valid board try again
            enterdBoard = getLine("That is not a valid 16-letter board string. Try again.");
        }
        cout << "Ok we are good!";
        enterdBoard = toLowerCase(enterdBoard);
        cout << "You entered : " << enterdBoard;
    }
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
