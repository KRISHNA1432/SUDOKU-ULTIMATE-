/*
 * C++ Program to Solve Sudoku Problem using BackTracking
 */
#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

#define BLANK 0
#define N 9

int FindBLANK(int grid[N][N], int &row, int &col);
int InsertSafely(int grid[N][N], int row, int col, int num);

/* assign values to all BLANK locations for Sudoku solution
 */
void gotoxy(int x,int y)
{
    for(int i=0;i<x;i++)
        cout<<'\n';
    for(int i=0;i<y;i++)
        cout<<' ';
}
 void welcome()
 {
     system("cls");
     for(int i=0;i<336;i++)
        cout<<'_';

        gotoxy(5,70);
        cout<<"WELCOME TO SUDOKU WORLD !";
        gotoxy(3,70);
        cout<<"PREPARED BY :-";
        gotoxy(3,85);
        cout<<"KRISHNA YADAV";
        gotoxy(3,85);
        cout<<"MAHIMA SACHDEVA";
        gotoxy(3,85);
        cout<<"MUKUL VERMA";
        gotoxy(15,0);
        for(int i=0;i<336;i++)
        cout<<'_';

     system("pause");
     system("cls");
 }

int Solve(int grid[N][N])
{
    int row, col;
    if (!FindBLANK(grid, row, col))
       return 1;
    for (int num = 1; num <= 9; num++)
    {
        if (InsertSafely(grid, row, col, num))
        {
            grid[row][col] = num;
            if (Solve(grid))
                return 1;
            grid[row][col] = BLANK;
        }
    }
    return 0;
}

/* Searches the grid to find an entry that is still BLANK. */
int FindBLANK(int grid[N][N], int &row, int &col)
{
    for (row = 0; row < N; row++)
        for (col = 0; col < N; col++)
            if (grid[row][col] == BLANK)
                return 1;
    return 0;
}

/* Returns whether any assigned entry n the specified row matches
   the given number. */
int RepeatInRow(int grid[N][N], int row, int num)
{
    for (int col = 0; col < N; col++)
        if (grid[row][col] == num)
            return 1;
    return 0;
}

/* Returns whether any assigned entry in the specified column matches
   the given number. */
int RepeatInCol(int grid[N][N], int col, int num)
{
    for (int row = 0; row < N; row++)
        if (grid[row][col] == num)
            return 1;
    return 0;
}

/* Returns whether any assigned entry within the specified 3x3 box matches
   the given number. */
int RepeatInBox(int grid[N][N], int SubRow, int SubCol, int num)
{
    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+SubRow][col+SubCol] == num)
                return 1;
    return 0;
}

/* Returns whether it will be legal to assign num to the given row,col location.*/
int InsertSafely(int grid[N][N], int row, int col, int num)
{
    if(!RepeatInRow(grid, row, num) && !RepeatInCol(grid, col, num) &&
           !RepeatInBox(grid, row - row % 3 , col - col % 3, num))
           {
               return 1;
           }
    else
        return 0;
}


int valid(int grid[9][9],int row,int col,int num)
{
    int flagR=0,flagC=0,flagB=0;

    for(int i=0;i<9;i++)
    {
        if(grid[row][i]==num)
        {
            flagR++;
        }
        if(grid[i][col]==num)
        {
            flagC++;
        }
    }

    int SubRow=row-row%3;
    int SubCol=col-col%3;

    for (int row = 0; row < 3; row++)
        for (int col = 0; col < 3; col++)
            if (grid[row+SubRow][col+SubCol] == num)
            {
                ++flagB;
            }

    if(flagC>=2)
    {
        gotoxy(5,30);
        cout<<"INPUT ERROR IN COLUMN";
        return 0;
    }

    if(flagR>=2)
    {
        gotoxy(5,30);
        cout<<"INPUT ERROR IN ROW";
        return 0;
    }

    if(flagB>=2)
    {
        gotoxy(5,30);
        cout<<"INPUT ERROR IN BOX";
        return 0;
    }


    return 1;
}

/* PRINT GRID  */
void printGrid(int grid[N][N])
{
    for (int row = 0; row < N; row++)
    {
        cout<<endl<<"\t\t\t\t\t\t\t";

        if(row==0)
        {
            cout<<endl<<"\t\t\t\t\t\t\t-------------------------\n\t\t\t\t\t\t\t";
        }

        for (int col = 0; col < N; col++)
        {

            if(col==0||col==3||col==6)
            {
                cout<<"| ";
            }
            cout<<grid[row][col]<<' ';
            if(col==8)
            {
                cout<<"| ";
            }
        }
        if(row==8||row==2||row==5)
        {
            cout<<endl<<"\t\t\t\t\t\t\t-------------------------";
        }

    }
}

/* MAIN FUNCTION */
int main(int argc,char* argv[])
{
    welcome();

    int count=0,check=0,a,grid[N][N];
    char ch,choice;
    const char *puzzle;

//CHECK FOR VALID NO OF ARGUMENTS.
        if(argc!=2)
        {
            cout<<"\n\n\t Invalid No. Of Arguments...";
                return 0;
        }

    puzzle=argv[1];

        ifstream fp;
            fp.open(puzzle,ios::in);


        //CHECK FOR FILE IS OPEN.
            if(!fp.is_open())
            {
                cout<<"\n\n\t File Not Found...";
                return 0;
            }


            //CHECK FOR EMPTY FILE.
                fp.seekg(0,ios::end);


            if(fp.tellg()==0)
            {
                cout<<"\n\n\t Empty FILE...";
                fp.close();
                return 0;
            }

            fp.close();

        fp.open(puzzle,ios::in);


    //CHECK FOR VALID INPUT.
        while(fp.get(ch))
        {
            if(ch>='0'&&ch<='9')
            {
                check++;
            }
            if(1)
            {
                if((ch>='0'&&ch<='9')||ch==' '||ch=='\n')
                {
                    continue;
                }
                else
                {
                    cout<<"\n\n\t Invalid Input In File...";
                    return 0;
                }
            }
        }


        //CHECK FOR VALIDITY OF CONTENTS IN FILE.
            if(check!=81)
            {

                cout<<"Invalid Number Elements In Given Puzzle...";
                return 0;
            }

            fp.close();
            fp.open(puzzle,ios::in);


            //TAKING INPUT FROM FILE.

        for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
                fp>>grid[i][j];



         for(int i=0;i<9;i++)
            for(int j=0;j<9;j++)
            {
                if(grid[i][j])
                {
                    if(!valid(grid,i,j,grid[i][j]))
                    {
                        return 0;
                    }
                }
            }

            gotoxy(5,25);
            cout<<"Given Sudoku Puzzle In File : ";

        printGrid(grid);

        fp.close();

        for(int i=0;i<N;i++)
            for(int j=0;j<N;j++)
                if(grid[i][j]!=0)
                {
                    if(InsertSafely(grid,i,j,grid[i][j]))
                    {
                        gotoxy(5,25);
                        cout<<i<<j<<grid[i][j]<<"Given Puzzle Is Wrong....Solution Is Not Possible...";
                        return 0;
                    }
                }


        if (Solve(grid)==1)
        {
            gotoxy(5,25);
            cout<<"Hurrah!!! Your Answer Is Here...";
            printGrid(grid);
        }
        else
            cout<<"No solution exists"<<endl;


    return 0;

}
