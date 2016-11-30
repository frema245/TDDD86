
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include "grid.h"
#include "lifeutil.h"

using namespace std;

int main() {

    queue<int> baoz;

    baoz.push(9);
    baoz.push(2);
    baoz.push(3);
    baoz.push(4);
    baoz.push(5);

    int size = baoz.size();
    int front = baoz.front();

    cout << size << endl;
    cout << front << endl;

    return 0;
}

