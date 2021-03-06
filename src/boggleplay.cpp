
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
void printBoard(string board, string message);
string getWordFromHuman(string board, Boggle& boggle, string message);
int playWithHuman(string board, Boggle& boggle);
int playWithComputer(Boggle& boggle);
void recordAllWordsOnGUI(Set<string>& allWords);

void playOneGame(Lexicon& dictionary) {
    BoggleGUI::initialize(4,4);
    string board;
    if(!getYesOrNo("Do you want to generate a random board?")){
        board = getLine("Type the 16 letters to appear on the board:");
        board = getValidBoard(board);
    }
    Boggle boggle(dictionary, board);
    board = boggle.getBoard();
    BoggleGUI::labelAllCubes(board);

    int humanScore = playWithHuman(board, boggle);
    int computerScore = playWithComputer(boggle);
    string message = (computerScore > humanScore) ? "Ha ha ha, I destroyed you. Better luck next time, puny human!"
            : "WOW, you defeated me! Congratulations!";
    cout << message << endl;
    BoggleGUI::setStatusMessage(message);
}

int playWithComputer(Boggle& boggle){
    cout << "Its my turn!" << endl;
    BoggleGUI::setStatusMessage("Its my turn!");
    BoggleGUI::clearHighlighting();
    Set<string> allWords = boggle.computerWordSearch();
    cout << "My Words (" << allWords.size() << "): ";
    cout << allWords.toString() << endl;
    int score = boggle.getScoreComputer();
    cout << "My score: " << score << endl;
    BoggleGUI::setScore(score, BoggleGUI::COMPUTER);
    recordAllWordsOnGUI(allWords);
    return score;
}

void recordAllWordsOnGUI(Set<string>& allWords){
    for(string word : allWords){
        BoggleGUI::recordWord(word, BoggleGUI::COMPUTER);
    }
}


int playWithHuman(string board, Boggle& boggle){
    string humansWord = getWordFromHuman(board, boggle, "Its your turn!");
    while(humansWord.size() != 0){
        // do search
        bool searchResult = boggle.humanWordSearch(humansWord);
        string message = (searchResult)?"You found a new word!'" + humansWord + "'"
                                       :"That word can't be formed on this board." ;
        if(searchResult){
            BoggleGUI::recordWord(humansWord, BoggleGUI::HUMAN);
        }
        humansWord = getWordFromHuman(board, boggle, message);
    }
    return  boggle.getScoreHuman();
}


string getWordFromHuman(string board, Boggle& boggle, string message){
    Set<string> humanWords = boggle.getHumanWords();
    string humanEnterdWord;
    do{
        printBoard(board, message);
        cout << "\nYour words (" << humanWords.size() << "): " << humanWords.toString()<<endl;
        cout << "Your score: " << boggle.getScoreHuman();
        BoggleGUI::setScore(boggle.getScoreHuman(), BoggleGUI::HUMAN);
        humanEnterdWord = getLine("\nType a word (or Enter to stop): ");
        message = "You must enter an unfound 4+ letter word from the dictionary.";
    }while(humanEnterdWord.size() != 0 && !boggle.checkWord(humanEnterdWord));
    return toUpperCase(humanEnterdWord);
}

void printBoard(string board, string message){
    clearConsole();
    cout<< message;
    BoggleGUI::setStatusMessage(message);
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
