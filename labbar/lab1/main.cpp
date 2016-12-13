#include <iostream>
#include<fstream>

using namespace std;

void initialize(string filename);

int main()
{
    string filename;
    cout << "Enter filename: ";
    cin >> filename;
    initialize(filename);

    return 0;
}


void initialize(string filename)
{
    ifstream input;
    input.open(filename.c_str());
    string line;
    while (getline(input, line)) {
        cout << line << endl;
        }
    input.close();
    cout << "Done!" << endl;
}
