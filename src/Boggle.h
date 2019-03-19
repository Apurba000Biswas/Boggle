
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

    friend ostream& operator<<(ostream& out, Boggle& boggle);
    string getBoard();
    string board[4][4];
    Set<string> getHumanWords();

private:
    string getRandomBoard();
    bool humanWordSearchHelper(string word, int row, int col, Set<string>& usedIndecies);
    string getRecycledWord(string word);
    string boardStr;
    void buildBoard();
    Set<string> humanWords;
    Lexicon dictionary;
    int humanScore;
    void buildAllWords(string word, int row, int col, Set<string>& result, Set<string>& usedIndecies);
    bool isValidWord(string word, Set<string>& result);
    int computerScore;
};

#endif // _boggle_h
