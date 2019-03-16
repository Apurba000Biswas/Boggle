// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#include <string>
#include "lexicon.h"
#include "bogglegui.h"
#include "simpio.h"
#include "strlib.h"

using namespace std;

void playOneGame(Lexicon& dictionary) {
    // create gui with 4 by 4 grid
    BoggleGUI::initialize(4,4);
    if(getYesOrNo("Do you want to generate a random board?")){
        // generate random board
    }else{
        // get board from user
        string enterdBoard = getLine("Type the 16 letters to appear on the board:");
        cout << "You entered : " << enterdBoard;
    }
}
