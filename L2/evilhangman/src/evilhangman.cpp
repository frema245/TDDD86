#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <map>

using namespace std;

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void initWordlist(set<string> &wordlist, string& currentKeyWord, int& wordLength);
void divide(char letter, set<char> &usedChars, set<string> &wordlist, string& currentKeyWord);

void printWordlist(set<string> &wordlist);
void printUsedChars(set<char> usedChars);
void printCurrentWord(string& currentKeyWord);
void printWordlistSize(set<string> &wordlist);
void printGuessesLeft(int& guesses);

int main() {

    set<char> usedChars;
    string currentKeyWord;
    set<string> wordlist;

    int wordLength;
    int guesses = 0;
    string input;

    while (true) {

    cout << "Welcome to Hangman." << endl;

    initWordlist(wordlist, currentKeyWord, wordLength);

    while (!(guesses > 0)) {
        cout << "Enter the amount of given guesses: ";
        cin >> guesses;}

    cout << "Do you want to see the amount of remaining words in the wordlist? (y/n)" << endl;

    cin >> input;

    // loops while there are still guesses left
    while (guesses) {
        guesses -= 1;

        cout << "MAKE A GUESS:     ";
        char guess;
        cin >> guess;

        if (usedChars.count(guess) == 0) {
            divide(guess, usedChars, wordlist, currentKeyWord);
        }
        else {
            guesses += 1;
        }

        string keyWordCopy = {currentKeyWord};

        if (keyWordCopy != currentKeyWord) {
            guesses += 1;
        }

        printCurrentWord(currentKeyWord);
        printGuessesLeft(guesses);
        printUsedChars(usedChars);

        if (input == "y") {
            printWordlistSize(wordlist);
        }

        if (wordlist.size() == 1){
            if (wordlist.count(currentKeyWord) == 1) {
                cout << "YOU WON" << endl;
                cout << "THE WORD WAS:  " << currentKeyWord << endl;
                guesses = 0;
            }
        }
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << endl; //Because it's nice
    }

    string answer;

    while (answer != "y") {

        cout << "GAME OVER" << endl;
        cout << "Do you want to play again? (y/n)" << endl;
        cin >> answer;

        usedChars.clear();

        if (answer == "n") {
            cout << "BYE" << endl;
            return 0;
        }
    }
}
}

// Adds a keyword to every word in wordlist. Pairs keyword and key and adds it to familyMap.
// Iterates over familyMap to find the biggest word-family (the most common keyword).
// Iterates (again) over familyMap to add the words with the most common keyword

void divide(char letter, set<char>& usedChars, set<string>& wordlist, string& currentKeyWord) {

    multimap<string,string> familyMap;

    usedChars.insert(letter);

    for (string word : wordlist) {
        string keyword = {word};
        for (char& c : keyword) {
            if (!usedChars.count(c)) {
                c = '-';
            }
        }
        familyMap.insert(pair<string,string>(keyword, word));
    }

    int largestFamilySize = 0;
    multimap<string,string>::iterator iter;
    wordlist.clear();

    for (iter = familyMap.begin(); iter != familyMap.end(); iter++) {
        if (familyMap.count((*iter).first) > largestFamilySize) {
            largestFamilySize = (familyMap.count((*iter).first));
            currentKeyWord = (*iter).first;
        }
    }

    pair<multimap<string,string>::iterator,multimap<string,string>::iterator> familyRange;

    familyRange = familyMap.equal_range(currentKeyWord);

    for (iter = familyRange.first; iter != familyRange.second; iter++) {
        wordlist.insert((*iter).second);
    }
}

void initWordlist(set<string> &wordlist, string& currentKeyWord, int& wordLength) {
    //creates set of strings of the .txt. reads wordlength and creates the currentWord.

    ifstream reader;
    string word;
    reader.open("dictionary.txt");

    cout << "Enter word length: "; cin >> wordLength;

    while(getline(reader, word)) {
        if (word.length() == wordLength) {
            wordlist.insert(word);
        }
    }

    string newstring (wordLength, '-');
    currentKeyWord = newstring;
    cout << currentKeyWord << endl;
}

void printGuessesLeft(int& guesses) {
    cout << "- You have " << guesses << " guesses left." << endl;
}

void printWordlistSize(set<string> &wordlist) {
    cout << "- Words left: " << wordlist.size() << endl;
}

void printUsedChars(set<char> usedChars) {
    if (!usedChars.empty()) {
        cout << "- Used Chars: ";
        for (char c : usedChars) {
            cout << "  " << c;
        }
        cout << endl;
    }
}

void printCurrentWord(string& currentKeyWord) {
    if (!currentKeyWord.empty()) {
        cout << "- Current word: " << currentKeyWord << endl;
    }
}
