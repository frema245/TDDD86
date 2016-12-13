#include<iostream>
#include<fstream>
#include"grid.h"
#include"lifeutil.h"

// Fredrik Malmfors frema245 & Jesper Jonsson Jesjo430

using namespace std;

string take_filename_input(void);
void initialize(string& filename, Grid<char>& grid);
void show_grid(Grid<char>& grid);
void update_grid(Grid<char>& grid);
void create_grid(int height, int width, ifstream &input, Grid<char>& grid);
int check_neighbors(int row, int col, Grid<char>& grid);

int main() {
    cout << "Welcome to the TDDD86 Game of Life, "
            "a simulation of the \n lifecycle of a bacteria colony. \n"
            "Cells (X) live and die by the following rules: \n\n"
            "- A cell with 1 or fewer neighbours dies.\n"
            "- Locations with 2 neighbours remain stable.\n"
            "- Locations with 3 neighbours will create life.\n"
            "- A cell with 4 or more neighbours dies. \n" << std::endl;

    char tick = 'q';
    string filename = take_filename_input();
    Grid<char> grid;
    initialize(filename, grid);

    while(true)
    {
        show_grid(grid);
        cout << "a)nimate, t)ick, q)uit?" << endl;
        cin >> tick;

        if(tick == 't')
        {
             update_grid(grid);
             clearConsole();
        }

        else if(tick == 'a')
        {
            while(true)
            {
                update_grid(grid);
                show_grid(grid);
                pause(100);
                clearConsole();
            }
        }
        else if(tick == 'q')
        {
            cout << "Have a nice Life!" << endl;
            return 0;
        }
    }
}

//Returns a string from istream.
string take_filename_input(void) {
    string filename;
    cout << "Enter a filename: ";
    cin >> filename;
    return filename;
}

//Creates a grid with given size.
void create_grid(int height, int width, ifstream& input, Grid<char>& grid)
{
    string text;
    grid.resize(height, width);

    for(int i = 0; i < height; i++)
    {
        input >> text;
        for(int j = 0; j < width; j++)
        {
            if (text[j] == 'X')
            {
                grid.set(i, j, 'X');
            }
            else
            {
                grid.set(i, j, '-');
            }
        }
    }
}

//Takes a string and opens a file corresponding to string. Initializes the grid.
void initialize(string& filename, Grid<char>& grid) {
    ifstream input;
    input.open(filename);


    int width;
    int height;

    input >> height >> width;

    create_grid(height, width, input, grid);

    input.close();
}


//Sends the argument grid to the cout.
void show_grid(Grid<char>& grid) {
    for(int i = 0; i < grid.numRows(); i++)
    {
        for(int j = 0; j < grid.numCols(); j++)
        {
            if (grid[i][j] == 'X')
            {
                cout << 'X';
            }
            else
            {
                cout << '-';
            }
        }
        cout << endl;
    }
}

//Counts the amout of neighboors of a specific given position in a given grid.
int check_neighbors(int row, int col, Grid<char>& grid) {
    int neighbors = 0;

    int start_row = row-1;
    int start_col = col-1;
    int end_row = row+1;
    int end_col = col+1;

    for(int i = start_row; i <= end_row; i++)
    {
        for(int j = start_col; j <= end_col; j++)
        {
            if (grid.inBounds(i,j) && grid.get(i,j) == 'X') {
                neighbors += 1;
            }
        }
    }

    if(grid.get(row,col)=='X')
    {
        neighbors -= 1;
    }
    return neighbors;
}

// Changes the grid accordning to written rules.
void update_grid(Grid<char>& grid)
{
    Grid<char> new_grid = grid;
    for(int i = 0; i < grid.numRows(); i++)
    {
        for(int j = 0; j < grid.numCols(); j++)
        {
            int neighbors = check_neighbors(i,j, grid);

            if(neighbors < 2 || neighbors > 3)
            {
                new_grid.set(i,j,'-');
            }
            else if (neighbors == 3)
            {
                new_grid.set(i,j, 'X');
            }
            else
            {
            }
        }
    }
    grid = new_grid;
}




