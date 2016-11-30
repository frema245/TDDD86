
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <sstream>
#include "Boggle.h"
#include "bogglemain.h"
#include "strlib.h"
#include "grid.h"
#include "lexicon.h"

using namespace std;

// Declarations
void printBoard(const Grid<string> grid);
bool askManualGrid();
bool isAlpha(const string &str);
string enterManualGrid();
bool isInWordlist(const string &word);
string enterWord(Boggle& boggle);
void printBoard(Boggle& boggle);
void printScore(Boggle& boggle);
void printUsedWords(Boggle& boggle);
void printCompScore(Boggle& boggle);
void printCompWords(Boggle& boggle);

/*
 * Plays one game of Boggle using the given boggle game state object.
 */
void playOneGame(Boggle& boggle) {

    // Vi har läst att man ska vara försiktig vid använandet av "goto", men tycker i detta fall att det skapar en tydlig struktur för vems tur det är, och vems tur det blir

    clearConsole();

        if (askManualGrid()) {
            boggle.GridFromString(enterManualGrid());
        } else {
            boggle.GridFromRandom();
            boggle.shuffleGrid();
        }

        printBoard(boggle);

        cout << endl;

        string guess = enterWord(boggle);

human:
        clearConsole();

        // if no guess --> computer turn
        if (guess != "") {
            if (boggle.human(guess)) {
                cout << "FOUND WORD!" << endl;
            } else {
                cout << "The word was not found" << endl;
            }
        } else {
            goto computer;
        }

        // printers
        printBoard(boggle);
        printScore(boggle);
        printUsedWords(boggle);

        // new guess
        guess = enterWord(boggle);

        goto human;

computer:
        clearConsole();

        boggle.computer();

        // printers
        printBoard(boggle);
        printCompScore(boggle);
        printCompWords(boggle);

        cout << endl;

        // Who is the winner?
        if (boggle.getCompScore() > boggle.getScore()) {
            cout << "Guess I'm the better one....... HA" << endl;
        } else {
            cout << "Guess you're the better one. Damn it" << endl;
        }

        cout << endl;

        boggle.reset();
    }


/*
 * Gives the user the opportunity to guess a word, and returns it if it lives up to the conditions
 */
string enterWord(Boggle& boggle) {
    while (true) {

        cout << "Type a word (Or press enter to give up):  ";

        string answer;
        getline(cin, answer);

        if (answer.length() == 0) return answer;

        answer = trim(toUpperCase(answer));

        if ((answer.length() >= 4)) {
            if (boggle.contains(answer)) {
                if (boggle.isUsedWord(answer)) {
                    cout << "You've already guessed this word before" << endl;
                } else {
                    return answer;
                }
            } else {
                cout << "Please enter an english word!" << endl;
            }
        } else {
            cout << "The word must contain at least 4 letters!" << endl;
        }
    }
}

/*
 * Asks if to create a random or manual grid
 */
bool askManualGrid() {
    cout << "Do you want a randomized grid och do you want to manually enter one?" << endl;
    cout << "('r' = random, 'm' = 'manual':  ";
    while (true) {
        string answer;
        getline(cin, answer);
        answer = trim(toLowerCase(answer));
        if (startsWith(answer, 'm')) {
            return true;
        } else if (startsWith(answer, 'r')) {
            return false;
        } else {
            cout << "Please type a word that begins with 'r' or 'm'." << endl;
        }
    }
}

/*
 * User enters a manual grid. Returns the string if it lives up to conditions
 */
string enterManualGrid() {
    cout << "Enter a string containing 16 characters (a-z):  ";
    while (true) {
        string answer;
        getline(cin, answer);
        answer = trim(toUpperCase(answer));
        if (answer.length() == 16 && isAlpha(answer)) {
            return answer;
        } else {
            cout << "rules: 16 caracters (a-z). Try again!" << endl;
        }
    }
}

/*
 * Checks if the input is alphabetic
 */
bool isAlpha(const string &str) {
    for(int i = 0; i < str.size(); i++) {
        if ( !isalpha(str[i])) return false;
    }
    return true;
}

void printBoard(Boggle& boggle) {

    cout << boggle.stringFromBoard() << endl;

}

void printScore(Boggle& boggle) {
    cout << "Your score: " << boggle.getScore() << endl;
}

void printCompScore(Boggle& boggle) {
    cout << "My score: " << boggle.getCompScore() << endl;
}

void printUsedWords(Boggle& boggle) {

    cout << "Your words (" << boggle.getUsedWords().size() << "):  ";

    for(auto word : boggle.getUsedWords()) {
      cout << word << ", ";
    }

    cout << endl;

}

void printCompWords(Boggle& boggle) {

    cout << "My words (" << boggle.getCompWords().size() << "):  ";

    for(auto word : boggle.getCompWords()) {
      cout << word << ", ";
    }

    cout << endl;

}

/*
 * Erases all currently visible text from the output console.
 */
void clearConsole() {
#if defined(_WIN32) || defined(_WIN64)
    std::system("CLS");
#else
    // assume POSIX
    std::system("clear");
#endif
}
