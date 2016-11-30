// This is the .h file you will edit and turn in.
// We have provided a minimal skeleton for you,
// but you must finish it as described in the spec.
// Also remove these comments here and add your own, as well as on the members.
// TODO: remove this comment header and replace it with your own

#ifndef _boggle_h
#define _boggle_h

#include <iostream>
#include <string>
#include "grid.h"
#include "lexicon.h"
#include <set>

// TODO: include any other header files you need

using namespace std;

class Boggle {
public:

    const string DICTIONARY_FILE = "EnglishWords.dat";
    const int MIN_WORD_LENGTH = 4;
    const int BOARD_SIZE = 4;

    Boggle();

    /*
    * Creates a grid from the given string
    */
    void GridFromString(string s);

    /*
    * Creates a randomized grid, according the the rules
    */
    void GridFromRandom();

    /*
    * Shuffles the grid once, plain and simple
    */
    void shuffleGrid();


    /*
     * Build a string from myGrid
     */
    string stringFromBoard();

    /*
    * Checks if the Lexicon contains the given word
    */
    bool contains(const string &word) const;

    /*
     * Checks if human has found this word before
     */
    bool isUsedWord(const string &word) const;

    /*
     * Checks if computer has found this word before
     */
    bool isUsedCompWord(const string &word) const;

    /*
     * This is where the program find all (remaining) possible words on the board
     */
    void addScore(const int length, const bool computer = false);

    /*
     * This is where the program find all (remaining) possible words on the board
     */
    bool human(string guess, int row = 0, int col = 0, string rest = "");

    /*
     * This is where the program find all (remaining) possible words on the board
     */
    void computer();

    /*
     * Helper function for computer().
     */
    void computerHelper(string word, int row, int col);

    /*
     * Returns the human score
     */
    int getScore() const;

    /*
     * Returns the computers score
     */
    int getCompScore() const;

    /*
     * Returns used words
     */
    set<string> getUsedWords() const;

    /*
     * Returns the words found by the computer
     */
    set<string> getCompWords() const;

    /*
     * Returns the grid of the board
     */
    Grid<string> getGrid() const;

    /*
     * Resets score and the two lists of words
     */
    void reset();

private:

    Lexicon wordlist;

    // score of human and computer
    int score;
    int compScore;

    // already found words of human and computer
    set<string> usedWords;
    set<string> compWords;

    // a grid of the visited letters in myGrid while backtracking. Used by human() and computer()
    Grid<bool> visited;

    // A 2D grid containing the board of letters
    Grid<string> myGrid;

};

#endif
