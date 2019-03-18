// This is a .cpp file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header
#include<string>
#include "Boggle.h"
#include "random.h"
#include "grid.h"

// letters on all 6 sides of every cube
static string CUBES[16] = {
    "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
    "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
    "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
    "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

// letters on every cube in 5x5 "Big Boggle" version (extension)
static string BIG_BOGGLE_CUBES[25] = {
   "AAAFRS", "AAEEEE", "AAFIRS", "ADENNN", "AEEEEM",
   "AEEGMU", "AEGMNN", "AFIRSY", "BJKQXZ", "CCNSTW",
   "CEIILT", "CEILPT", "CEIPST", "DDLNOR", "DDHNOT",
   "DHHLOR", "DHLNOR", "EIIITT", "EMOTTT", "ENSSSU",
   "FIPRSY", "GORRVW", "HIPRRY", "NOOTUW", "OOOTTU"
};

string boardStr;
string board[4][4];
Set<string> humanWords;
Lexicon dictionary;

Boggle::Boggle(Lexicon& dictionary, string boardText) {
    this->dictionary = dictionary;
    boardStr = (boardText.size() == 0)?getRandomBoard():boardText;
    buildBoard();
}

void Boggle::buildBoard(){
    int row = 0;
    int col = 0;
    for(int i=0; i<boardStr.size(); i++){
        if(col >3){
            col = 0;
            row++;
        }
        board[row][col] = boardStr.at(i);
        col++;
    }
}

string Boggle::getRandomBoard(){
    string board = "";
    for(int i=0; i<16; i++){
        int randomCubeIndex = randomInteger(0, 15);
        string randomCube = CUBES[randomCubeIndex];
        int randomSide = randomInteger(0, 5);
        char ch = randomCube[randomSide];
        board += ch;
    }
    return board;
}

string Boggle::getBoard(){
    return boardStr;
}

Set<string> Boggle::getHumanWords(){
    return humanWords;
}




char Boggle::getLetter(int row, int col) {
    // TODO: implement
    return '?';   // remove this
}

bool Boggle::checkWord(string word) {
    word = toLowerCase(word);
    if(word.size() >= 4 && dictionary.contains(word) && !humanWords.contains(word)){
        return true;
    }
    return false;
}

bool Boggle::humanWordSearch(string word) {
    //
    //for each row and collumn call helper to find the word in that index based
    for(int row=0; row<4; row++){
        for(int col=0; col<4; col++){
            //
            Set<string> usedIndecies;
            string currIndex = to_string(row) + to_string(col);
            usedIndecies.add(currIndex);
            humanWordSearchHelper(word, row, col, usedIndecies);
            usedIndecies.clear();
        }
    }
    return false;   // remove this
}


bool Boggle::humanWordSearchHelper(string word, int row, int col, Set<string> usedIndecies){
    cout << usedIndecies.toString();
    return false;
}







int Boggle::getScoreHuman() {
    // TODO: implement
    return 0;   // remove this
}

Set<string> Boggle::computerWordSearch() {
    // TODO: implement
    Set<string> result;   // remove this
    return result;        // remove this
}

int Boggle::getScoreComputer() {
    // TODO: implement
    return 0;   // remove this
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    // TODO: implement
    return out;
}
