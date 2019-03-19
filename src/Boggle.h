// This is a .h file you will edit and turn in.
// We have provided a skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own.
// TODO: remove this comment header

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "lexicon.h"
#include "grid.h"
using namespace std;

class Boggle {
public:
    Boggle(Lexicon& dictionary, string boardText = "");
    char getLetter(int row, int col);
    bool checkWord(string word);
    bool humanWordSearch(string word);
    Set<string> computerWordSearch();
    int getScoreHuman();
    int getScoreComputer();

    // TODO: add any other member functions/variables necessary
    friend ostream& operator<<(ostream& out, Boggle& boggle);
    string getBoard();
    string board[4][4];
    Set<string> getHumanWords();

private:
    // TODO: add any other member functions/variables necessary
    string getRandomBoard();
    bool humanWordSearchHelper(string word, int row, int col, Set<string>& usedIndecies);
    string getRecycledWord(string word);
    string boardStr;
    void buildBoard();
    Set<string> humanWords;
    Lexicon dictionary;
};

#endif // _boggle_h
