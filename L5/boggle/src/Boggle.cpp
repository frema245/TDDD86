
#include <sstream>
#include "Boggle.h"
#include "random.h"
#include "shuffle.h"
#include "strlib.h"
#include <stdlib.h>
#include "grid.h"
#include "lexicon.h"
#include "foreach.h"

static const int NUM_CUBES = 16;   // the number of cubes in the game
static const int CUBE_SIDES = 6;   // the number of sides on each cube
static const int GRID_SIDE_LENGTH = 4;   // the number of sides on each cube
static string CUBES[NUM_CUBES] = {



  // the letters on all 6 sides of every cube
   "AAEEGN", "ABBJOO", "ACHOPS", "AFFKPS",
   "AOOTTW", "CIMOTU", "DEILRX", "DELRVY",
   "DISTTY", "EEGHNW", "EEINSU", "EHRTVW",
   "EIOSST", "ELRTTY", "HIMNQU", "HLNNRZ"
};

Boggle::Boggle(){
    wordlist = Lexicon("EnglishWords.dat");
    myGrid.resize(GRID_SIDE_LENGTH,GRID_SIDE_LENGTH);
    visited.resize(GRID_SIDE_LENGTH,GRID_SIDE_LENGTH);
    score = 0;
    compScore = 0;

    // Vet inte varför denna är rödmarkerad men den utför vad den ska.
    foreach (bool n in visited) {n = false;}

}

void Boggle::computer() {
    for (int y = 0; y < GRID_SIDE_LENGTH; y++) {
        for (int x = 0; x < GRID_SIDE_LENGTH; x++) {
            string letter = myGrid[y][x];
            visited[y][x] = true;
            computerHelper(letter, y, x);
            visited[y][x] = false;
        }
    }
}

void Boggle::computerHelper(string word, int row, int col) {

    // Conditions:
    // Has not been used before by either computer or human, is at least 4 characters, and is in the wordlist
    if (wordlist.contains(word) && (!isUsedWord(word)) && (word.length() >= 4) && (!isUsedCompWord(word)) ) {
        compWords.insert(word);
        addScore(word.length(), true);
    }
    for (int y = row-1; y < row+2; y++) {
        for (int x = col-1; x < col+2; x++) {
            if (myGrid.inBounds(y,x) && !((y == row) && (x == col)) && (!visited[y][x])) {
                string currentLetter = myGrid[y][x];
                if (wordlist.containsPrefix(word + currentLetter)) {
                    visited[y][x] = true;
                    computerHelper(word + currentLetter, y, x);
                    visited[y][x] = false;
                }
            }
        }
   }
}

void Boggle::reset() {
    score = 0;
    compScore = 0;
    usedWords.clear();
    compWords.clear();
}

bool Boggle::human(const string guess, int row, int col, string rest) {

    string firstLetter;
    string restOfGuess;

    // Base case (when the word is found)
    if (guess == "" && !isUsedWord(rest)) {
        usedWords.insert(rest);
        addScore(rest.length());
        return true;

    // The case for the first letter in the word
    } else if (rest == "") {
        for (int y = 0; y < GRID_SIDE_LENGTH; y++) {
            for (int x = 0; x < GRID_SIDE_LENGTH; x++) {

                firstLetter = guess.substr(0, 1);
                restOfGuess = guess;
                restOfGuess.erase(0,1);

                if (firstLetter == myGrid[y][x]) {
                    visited[y][x] = true;
                    if (human(restOfGuess, y, x, firstLetter)) {
                        return true;
                    };
                    visited[y][x] = false;
                }
            }
        }
    // The case for the remaining letters in the word
    } else {
        for (int y = row-1; y < row+2; y++) {
            for (int x = col-1; x < col+2; x++) {

                firstLetter = guess.substr(0,1);
                restOfGuess = guess;
                restOfGuess.erase(0,1);

                if (myGrid.inBounds(y,x) && !((y == row) && (x == col)) && (!visited[y][x])) {
                    if (firstLetter == myGrid[y][x]) {
                        visited[y][x] = true;
                        if (human(restOfGuess, y, x, rest+firstLetter)) {
                            return true;
                        };
                        visited[y][x] = false;
                    }
                }
            }
        }
    }

    return false;

}

void Boggle::GridFromString(string s) {

    int count = 0;

    for (int row = 0; row < GRID_SIDE_LENGTH; row++) {
        for (int col = 0; col < GRID_SIDE_LENGTH; col++) {
             myGrid[row][col] = s.at(count);
             count += 1;
        }
    }
}

void Boggle::GridFromRandom() {

    int count = 0;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            int random = rand() % 6;
            myGrid[row][col] = CUBES[count].at(random);
            count += 1;
        }
    }
}

string Boggle::stringFromBoard() {

    string print;

    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
             print += myGrid[row][col] + " ";
        }
        print += "\n";
    }

    return print;

}



Grid<string> Boggle::getGrid()  const{
    return myGrid;
}

void Boggle::shuffleGrid() {
    shuffle(myGrid);
}

bool Boggle::contains(const string &word)  const{
    return (this->wordlist.contains(word));
}

bool Boggle::isUsedWord(const string &word)  const{
    return (usedWords.count(word));
}

bool Boggle::isUsedCompWord(const string &word)  const{
    return (compWords.count(word));
}

int Boggle::getScore()  const{
    return score;
}

int Boggle::getCompScore()  const{
    return compScore;
}

void Boggle::addScore(const int length, const bool computer) {
    if (computer) {compScore += (length - 3);
    } else score += (length - 3);
}

set<string> Boggle::getUsedWords()  const{
    return usedWords;
}

set<string> Boggle::getCompWords()  const{
    return compWords;
}
