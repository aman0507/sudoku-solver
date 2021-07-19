#include<bits/stdc++.h>
#include<conio.h>
#include<stdlib.h>
using namespace std;
bool isSafe(vector<vector<char>>&board,int row,int col,int num)
{
    int n=board.size();
    int m=board[0].size();
    for(int i=0;i<n;i++)
        if((board[i][col]-'0')==num)
        return false;
    for(int i=0;i<m;i++)
        if((board[row][i]-'0')==num)
        return false;
    row=row/3*3;
    col=col/3*3;
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
            if((board[row+i][col+j]-'0')==num)
            return false;
    }
    return true;
}
bool isValidSudoku(vector<vector<char>>& board)
{
    vector<int>row(9,0);
    vector<int>col(9,0);
    vector<vector<int>>mat(3,vector<int>(3,0));
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(board[i][j]!='.')
            {
                int mask=1<<(board[i][j]-'0');
                if((row[i]&mask)==0&&(col[j]&mask)==0&&(mat[i/3][j/3]&mask)==0)
                {
                    row[i]^=mask;
                    col[j]^=mask;
                    mat[i/3][j/3]^=mask;
                }
                else
                    return false;
            }
        }
    }
    return true;
}
int solve(vector<vector<char>>&board,vector<int>&emptyCells,int idx)
{
    if(idx==emptyCells.size())
        return true;
    int cell=emptyCells[idx];
    int r=cell/9;
    int c=cell%9;
    for(int i=1;i<=9;i++)
    {
        if(isSafe(board,r,c,i))
        {
            board[r][c]=char(i+'0');
            if(solve(board,emptyCells,idx+1)==1)
                return true;
            board[r][c]='.';
        }
    }
    return false;
}
int solveSudoku(vector<vector<char>>& board)
{
    if(!isValidSudoku(board))
        return 2;
    vector<int>emptyCells;
    for(int i=0;i<9;i++)
    {
        for(int j=0;j<9;j++)
        {
            if(board[i][j]=='.')
                emptyCells.push_back(9*i+j);
        }
    }
    bool solutionexist=solve(board,emptyCells,0);
    return solutionexist;
}
void Instructions()
{
    cout <<"\n\t\tINSTRUCTIONS\n\n";
    cout<<"1. Only enter the values from 1 to 9 \n";
    cout<<"2. Enter any other character in place of empty spaces\n";
    cout<<"3. Enter only one character in place of empty spaces\n\n";
    cout<<"press any key to continue the game......";
    getch();
    system("CLS");
}
void print(vector<vector<char>>&board,int solutionexist)
{
    if(solutionexist==0)
    {
        cout<<"\n\n\t\t\t\t\t\t\t\t\t\t\t\tRESULT : NO SOLUTION EXIST  :(\n\n";
    }
    else if(solutionexist==1)
    {
      cout<<endl;
        cout<< "\t"<<" _____     ____                        _________   _________    ____"<<"\n";
        cout<< "\t"<<"/         /    \\     |       |     |       |           |       /    \\     |\\   |"<<"\n";
        cout<< "\t"<<"\\____     |     |    |       |     |       |           |       |     |    | \\  |"<<"\n";
        cout<< "\t"<<"     \\    |     |    |       |     |       |           |       |     |    |  \\ |"<<"\n";
        cout<< "\t"<<"_____/     \\___/     |_____  \\_____/       |       ____|____    \\___/     |   \\|"<<"\n";
        cout<<endl;
        cout<<"\t\t\t\t-------------------------------------\n";
        for(auto it:board)
        {
          cout<<"\t\t\t\t| ";
            for(auto i:it)
                cout<<i <<" | ";
            cout<<endl;
            cout<<"\t\t\t\t-------------------------------------";
            cout<<endl;
        }
    }
    else
    {
        cout<<"\n\n\t\t\t\t\tRESULT : Invalid Sudoku  :(\n";
    }
}
int main()
{
  while(1)
  {
      system("CLS");
      int t;
      cout<<"\nCHOICES\n";
      cout<<"1. Play Game\n";
      cout<<"2. Exit\n";
      cout<<"\nEnter your choice : ";
      cin>>t;
      if(t!=1)
          break;
      system("CLS");
      Instructions();
      cout<<"\t\tENTER THE VALUES :\n";
      vector<vector<char>>board(9,vector<char>(9));
      bool flag=false;
      for(int i=0;i<9;i++)
      {
          for(int j=0;j<9;j++)
          {
              string s;
              cin>>s;
              if(s.length()>1)
              {
                cout<<"\n\nInvalid Values :(\n\n";
                cout<<endl<<endl;
                cout<<"press any key to continue the game....";
                getch();
                flag=true;
              }
              char t=s[0];
              if(t>='0'&&t<='9')
                  board[i][j]=t;
              else
                  board[i][j]='.';
          }
      }
      if(flag)
        continue;
      system("CLS");
      int solutionexist=solveSudoku(board);
      print(board,solutionexist);
      cout<<endl<<endl;
      cout<<"press any key to continue the game....";
      getch();
  }

    return 0;
}



// {
// {'5','3','.','.','7','.','.','.','.'},
// {'6','.','.','1','9','5','.','.','.'},
// {'.','9','8','.','.','.','.','6','.'},
// {'8','.','.','.','6','.','.','.','3'},
// {'4','.','.','8','.','3','.','.','1'},
// {'7','.','.','.','2','.','.','.','6'},
// {'.','6','.','.','.','.','2','8','.'},
// {'.','.','.','4','1','9','.','.','5'},
// {'.','.','.','.','8','.','.','7','9'}
// };




// 5 3 . . 7 . . . .
// 6 . . 1 9 5 . . .
// . 9 8 . . . . 6 .
// 8 . . . 6 . . . 3
// 4 . . 8 . 3 . . 1
// 7 . . . 2 . . . 6
// . 6 . . . . 2 8 .
// . . . 4 1 9 . . 5
// . . . . 8 . . 7 9
