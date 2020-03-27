#include <iostream>
using namespace std;

void sudoku_solve(int s[][9]);                              //Function where all the calculations takes place
bool box_check(int s[][9], int x, int y, int num);          //Function to check if a particular number is present in respective box
bool horizantal_check(int s[][9], int x, int y, int num);   //Function to check if a particular number is present in horizontal line
bool vertical_check(int s[][9], int x, int y, int num);     //Function to check if a particular number is present in vertical line
bool is_completed(int s[][9]);                              //Function to check if sudoku is solved

int main()
{
    int s[9][9];
    cout << "Enter the sudoku input: \n";
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            cin >> s[i][j];
    sudoku_solve(s);
}

bool box_check(int s[][9], int x, int y, int num) //returns false if number is found in that box
{
    int xpointer = x / 3;
    int ypointer = y / 3;
    xpointer *= 3;
    ypointer *= 3;
    for (int i = xpointer; i < xpointer + 3; i++)
    {
        for (int j = ypointer; j < ypointer + 3; j++)
        {
            if (s[i][j] == num)
            {
                return false;
            }
        }
    }
    return true;
}

bool horizantal_check(int s[][9], int x, int y, int num) //returns false if number is found in that horizantal line
{
    for (int i = 0; i < 9; i++)
        if (s[x][i] == num)
            return false;
    return true;
}

bool vertical_check(int s[][9], int x, int y, int num) //returns false if number is found in that vertical line
{
    for (int i = 0; i < 9; i++)
        if (s[i][y] == num)
            return false;
    return true;
}

bool is_completed(int s[][9]) //returns false if sudoku isn't completed
{
    for (int i = 0; i < 9; i++)
        for (int j = 0; j < 9; j++)
            if (s[i][j] == 0)
                return false;
    return true;
}

void sudoku_solve(int s[][9]) //function to slove sudoku (using BACKTRACKING)
{
    int i, j, k, starting, point = 0, index[81][2];
    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            starting = 1;
            if (s[i][j] == 0)
            {
            start:
                for (k = starting; k <= 9; k++)
                {
                    if (box_check(s, i, j, k) && horizantal_check(s, i, j, k) && vertical_check(s, i, j, k))
                    {
                        s[i][j] = k;
                        index[point][0] = i;
                        index[point][1] = j;
                        point++;
                        break;
                    }
                }
                if (k == 10)
                {
                    s[i][j] = 0;
                    point--;
                    i = index[point][0];
                    j = index[point][1];
                    starting = s[i][j] + 1;
                    goto start;
                }
            }
        }
    }
    if (is_completed(s))
    {
        cout << "solved sudoku: \n";
        for (i = 0; i < 9; i++)
        {
            for (j = 0; j < 9; j++)
                cout << s[i][j] << "  ";
            cout << endl;
        }
    }
    else
    {
        cout << "Something went wrong!";
    }
}