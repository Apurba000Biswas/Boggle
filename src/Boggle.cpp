
#include<string>
#include "Boggle.h"
#include "random.h"
#include "grid.h"
#include "bogglegui.h"

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
int humanScore;
int computerScore;

Boggle::Boggle(Lexicon& dictionary, string boardText) {
    this->dictionary = dictionary;
    boardStr = (boardText.size() == 0)?getRandomBoard():boardText;
    buildBoard();
    humanScore = 0;
    computerScore = 0;
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
    return '?';
}

bool Boggle::checkWord(string word) {
    word = toLowerCase(word);
    if(word.size() >= 4 && dictionary.contains(word)){
        word = toUpperCase(word);
        if(!humanWords.contains(word)){
            return true;
        }
    }
    return false;
}

bool Boggle::humanWordSearch(string word) {
    bool result = false;
    //for each row and collumn call helper to find the word in that index based
    Set<string> usedIndecies;
    for(int row=0; row<4; row++){
        for(int col=0; col<4; col++){
            BoggleGUI::clearHighlighting();
            BoggleGUI::setHighlighted(row, col, true);
            BoggleGUI::setAnimationDelay(150);

            usedIndecies.add(to_string(row) + to_string(col));
            result = humanWordSearchHelper(word, row, col, usedIndecies);
            if(result){
                humanWords.add(word);
                humanScore = humanScore + (word.size()-3);
                return true;
            }
            usedIndecies.clear();
        }
    }
    return result;
}


bool Boggle::humanWordSearchHelper(string word, int row, int col, Set<string>& usedIndecies){
    bool result = false;
    if(word.size() == 0){
        BoggleGUI::setHighlighted(row, col, false);
        return true;
    }else {
        string s = board[row][col];
        if( word[0] == s[0]){
            word = getRecycledWord(word);
            BoggleGUI::setHighlighted(row, col, true);
            usedIndecies.add(to_string(row) + to_string(col));
            for(int i=-1; i<2; i++){
                for(int j=-1; j<2; j++){
                    if(row+i>=0 && col+j>=0 && row+i<4 && col+j<4){
                        // choose
                        string index = to_string(row+i) + to_string(col+j);

                        // explore
                        if(!usedIndecies.contains(index)){
                            result = humanWordSearchHelper(word, row+i, col+j, usedIndecies);
                            if(result){
                                return result;
                            }
                        }
                    }
                }
            }
            // un choose
            BoggleGUI::setHighlighted(row, col, false);
            usedIndecies.remove(to_string(row) + to_string(col));
        }
    }
    return result;
}

string Boggle::getRecycledWord(string word){
    string recycledWord = "";
    for(int i=1; i<word.size(); i++){
        recycledWord += word[i];
    }
    return recycledWord;
}

int Boggle::getScoreHuman() {
    return humanScore;
}



Set<string> Boggle::computerWordSearch() {
    Set<string> result;
    Set<string> usedIndecies;
    for(int row=0; row<4; row++){
        for(int col=0; col<4; col++){
            usedIndecies.add(to_string(row) + to_string(col));
            buildAllWords(board[row][col], row, col, result, usedIndecies);
        }
    }
    return result;
}

void Boggle::buildAllWords(string word, int row, int col,
                                      Set<string>& result,
                                      Set<string>& usedIndecies ){
    if(dictionary.containsPrefix(word)){
        if(isValidWord(word, result)){
            if(!humanWords.contains(word)){
                result.add(word);
                computerScore = computerScore + (word.size()-3);
            }
        }
        usedIndecies.add(to_string(row) + to_string(col));
        string newWord = word;
        for(int i=-1; i<2; i++){
            for(int j=-1; j<2; j++){
                if(row+i>=0 && col+j>=0 && row+i<4 && col+j<4){
                    // choose
                    string index = to_string(row+i) + to_string(col+j);

                    // explore
                    if(!usedIndecies.contains(index)){
                        string boardLetter = board[row+i][col+j];
                        newWord += boardLetter;
                        buildAllWords(newWord, row+i, col+j, result, usedIndecies);
                    }
                    newWord = word;
                }
            }
        }
        // un choose
        usedIndecies.remove(to_string(row) + to_string(col));
    }// else
          // base case
}

bool Boggle::isValidWord(string word, Set<string>& result){
    word = toLowerCase(word);
    if(word.size() >= 4 && dictionary.contains(word)){
        word = toUpperCase(word);
        if(!result.contains(word)){
            return true;
        }
    }
    return false;
}

int Boggle::getScoreComputer() {
    return computerScore;
}

ostream& operator<<(ostream& out, Boggle& boggle) {
    return out;
}
