#include <fstream>
#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <set>

using namespace std;

// Fredrik Malmfors (frema245), Jesper Jonsson (Jesjo430)

const string ALPHABET  = "abcdefghijklmnopqrstuvwxyz";

void findNeighbourWords(stack<string>& currentStack, set<string>& wordlist, set<string>& usedWords, queue<stack<string>>& myQueue);
void wordChain(string start, string finish, set<string>& wordlist, set<string>& usedWords, queue<stack<string>>& myQueue);
void initWordlist(set<string>& wordlist);
void printStack(stack<string> s);

int main() {

    set<string> wordlist;
    set<string> usedWords;
    queue<stack<string>> myQueue;

    initWordlist(wordlist);

    cout << "Welcome to TDDD86 Word Chain." << endl;
    cout << "If you give me two English words, I will transform the" << endl;
    cout << "first into the second by changing one letter at a time." << endl;
    cout << endl;

    cout << "Please type two words: ";

    string start;
    string finish;

    cin >> start;
    cin >> finish;

    wordChain(start, finish, wordlist, usedWords, myQueue);

    return 0;
}


// checks if (and how) we can add another word to our wordchain instance (input stack) according to wordlist
void findNeighbourWords(stack<string>& currentStack, set<string>& wordlist, set<string>& usedWords, queue<stack<string>>& myQueue) {
    string currentWord = {currentStack.top()};
    for (char& wordchar : currentWord) {
        char memorychar = {wordchar};
        for (char alphabetchar : ALPHABET) {
            wordchar = alphabetchar;
            // if the current word is in the wordlist AND has not been used before; do
            if ((wordlist.count(currentWord) != 0) && (usedWords.count(currentWord) == 0)) {
                // Copy current stack and add the current word to it. Add the new stack to our queue. Insert the word in the used words list
                stack<string> newStack = {currentStack};
                newStack.push(currentWord);
                myQueue.push(newStack);
                usedWords.insert(currentWord);
            }
        }
        wordchar = {memorychar};  // restores the char in the word before eventually going to the next char in the word.
    }
}

// Prints the given stack in reverse order (finish word to start word)
void printStack(stack<string> s) {
    string print;
    while (!s.empty()) {print = s.top();
    cout << print << endl;
    s.pop();
    }
}


// Takes the first stack in myQueue. If top word is not the final word, then find neighbours.
void wordChain(string start, string finish, set<string>& wordlist, set<string>& usedWords, queue<stack<string>>& myQueue) {
    stack<string> initStack;
    initStack.push(start);

    myQueue.push(initStack);

    while (!myQueue.empty()) {

        stack<string> currentStack = myQueue.front(); myQueue.pop();

        if (currentStack.top() == finish) {
            printStack(currentStack);
            break;
        }
        else {
            findNeighbourWords(currentStack, wordlist, usedWords, myQueue);
        }
    }
}

// reads the dictionary file and adds every word to wordlist.
void initWordlist(set<string>& wordlist) {
    ifstream reader;
    string word;
    reader.open("dictionary.txt");
    while(getline(reader, word)) {
        wordlist.insert(word);
    }
}

