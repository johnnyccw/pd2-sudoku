#include "Sudoku.h"
using namespace std;

void Sudoku::giveQuestion(){
   int question[81]={3,0,2,0,0,5,6,9,0,
                     0,4,0,0,9,6,0,3,0,
                     0,5,0,0,0,8,0,0,0,
                     1,9,0,0,8,0,7,0,3,
                     0,0,0,0,0,0,0,0,0,
                     5,0,7,0,3,0,0,6,1,
                     0,0,0,8,0,0,0,2,0, 
                     0,8,0,9,6,0,0,7,0,
                     0,6,5,7,0,0,3,0,9};
   for(i=0;i<81;i++){
         cout<<map[i];
         if (i%9==8){
            cout<<endl;
         }
         if (i%9!=8){
            cout<<" ";
         }
   }
}

void Sudoku::readIn(){
   for(i=0;i<9;i++){
      for(j=0;j<9;j++){
         cin>>map[i][j];
      }
   }
}

void Sudoku::changeNum(int a,int b){
   for(i=0;i<9;i++){
      for(j=0;j<9;j++){
         if(map[i][j]==a){
            map[i][j]=10;
         }
         if(map[i][j]==b){
            map[i][j]=11;
         }
      }
   }
   for(i=0;i<9;i++){
      for(j=0;j<9;j++){
         if(map[i][j]==10){
            map[i][j]=b;
         }
         if(map[i][j]==11){
            map[i][j]=a;
         }
      }
   }
}

void Sudoku::changeRow(int a,int b){
   int temp;
   for(i=0;i<3;i++){
      for(j=0;j<9;j++){
         temp=map[i+b*3][j];
         map[i+b*3][j]=map[i+a*3][j];
         map[i+a*3][j]=temp;
      }
   }       
}

void Sudoku::changeCol(int a,int b){
   int temp;
   for(i=0;i<3;i++){
      for(j=0;j<9;j++){
         temp=map[j][i+b*3];
         map[j][i+b*3]=map[j][i+a*3];
         map[j][i+a*3]=temp;
      }
   }
}

void Sudoku::rotate(int n){
   int tempA[9][9],temp;
   for(k=0;k<n;k++){
      for(i=0;i<9;i++){
         for(j=0;j<9;j++){
            tempA[i][j]=map[i][j];
         }
      }
      for(i=0;i<9;i++){
         for(j=0;j<9;j++){
            map[i][j]=tempA[j][i];
         }
      }
      for(i=0;i<4;i++){
         for(j=0;j<9;j++){
            temp=map[j][i];
            map[j][i]=map[j][8-i];
            map[j][8-i]=temp;
         }
      }
   }   
}

void Sudoku::rotate2(int n){
   int tempA[9][9],temp;
   for(k=0;k<n;k++){
      for(i=0;i<9;i++){
         for(j=0;j<9;j++){
            tempA[i][j]=map2[i][j];
         }
      }
      for(i=0;i<9;i++){
         for(j=0;j<9;j++){
            map2[i][j]=tempA[j][i];
         }
      }
      for(i=0;i<4;i++){
         for(j=0;j<9;j++){
            temp=map2[j][i];
            map2[j][i]=map2[j][8-i];
            map2[j][8-i]=temp;
         }
      }
   }   
}

void Sudoku::rotate3(int n){
   int tempA[9][9],temp;
   for(k=0;k<n;k++){
      for(i=0;i<9;i++){
         for(j=0;j<9;j++){
            tempA[i][j]=ans2[i][j];
         }
      }
      for(i=0;i<9;i++){
         for(j=0;j<9;j++){
            ans2[i][j]=tempA[j][i];
         }
      }
      for(i=0;i<4;i++){
         for(j=0;j<9;j++){
            temp=ans2[j][i];
            ans2[j][i]=ans2[j][8-i];
            ans2[j][8-i]=temp;
         }
      }
   }   
}

void Sudoku::flip(int n){
   int temp;
   if (n==0){
      for(i=0;i<4;i++){
         for(j=0;j<9;j++){
            temp=map[i][j];
            map[i][j]=map[8-i][j];
            map[8-i][j]=temp;
         }
      }  
   }
   if (n==1){
      for(i=0;i<4;i++){
         for(j=0;j<9;j++){
            temp=map[j][i];
            map[j][i]=map[j][8-i];
            map[j][8-i]=temp;
         }
      } 
   }   
} 

void Sudoku::transform(){
   srand(time(NULL));
   changeNum(rand()%9+1,rand()%9+1);
   changeRow(rand()%3,rand()%3);
   changeCol(rand()%3,rand()%3);
   rotate(rand()%4);
   flip(rand()%2);
   for(i=0;i<9;i++){
      for(j=0;j<9;j++){
         cout<<map[i][j]<<" ";
      }
      cout<<endl;
   }
}

int Sudoku::isAvailable(int puzzle[][9], int row, int col, int num){
    int rowStart = (row/3) * 3;
    int colStart = (col/3) * 3;
    int i, j;

    for(i=0; i<9; ++i)
    {
        if (puzzle[row][i] == num) return 0;
        if (puzzle[i][col] == num) return 0;
        if (puzzle[rowStart + (i%3)][colStart + (i/3)] == num) return 0;
    }
    return 1;
}

int Sudoku::fillSudoku(int puzzle[][9], int row, int col){
    int i;
    if(row<9 && col<9)
    {
        if(puzzle[row][col] != 0)
        {
            if((col+1)<9) return fillSudoku(puzzle, row, col+1);
            else if((row+1)<9) return fillSudoku(puzzle, row+1, 0);
            else return 1;
        }
        else
        {
            for(i=0; i<9; ++i)
            {
                if(isAvailable(puzzle, row, col, i+1))
                {
                    puzzle[row][col] = i+1;
                    if((col+1)<9)
                    {
                        if(fillSudoku(puzzle, row, col +1)) return 1;
                        else puzzle[row][col] = 0;
                    }
                    else if((row+1)<9)
                    {
                        if(fillSudoku(puzzle, row+1, 0)) return 1;
                        else puzzle[row][col] = 0;
                    }
                    else return 1;
                }
            }
        }
        return 0;
    }
    else return 1;
}

int Sudoku::isSolvable1(){   
    int puzzle[9][9];
    for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          puzzle[i][j]=map[i][j];
       }
    }
    if(fillSudoku(puzzle, 0, 0))
    {  
       for(i=0;i<9;i++){
          for(j=0;j<9;j++){
             ans1[i][j]=puzzle[i][j];
          }
       }
 
       return 1;  
    }
    else
       return 0;
}

int Sudoku::isSolvable2(){   
    int puzzle[9][9];
    for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          puzzle[i][j]=map2[i][j];
       }
    }
    if(fillSudoku(puzzle, 0, 0))
    {  
       for(i=0;i<9;i++){
          for(j=0;j<9;j++){
             ans2[i][j]=puzzle[i][j];
          }
       }
 
       return 1;  
    }
    else
       return 0;
}

void Sudoku::solve(){
   for(i=0;i<9;i++){
      for(j=0;j<9;j++){
         map2[i][j]=map[i][j];
      }
   }
   if(isSolvable1()==0)
   {
      cout<<"0";
      
   }
   if(isSolvable1()==1)
   {
   	  rotate2(2);
      isSolvable2();
      rotate3(2);
      for(i=0;i<9;i++){
         for(j=0;j<9;j++){
         	if(ans1[i][j]!=ans2[i][j]){
         	   cout<<"2"; exit(0);	
			}
		 }	
	  }
	  cout<<"1"<<endl;
	  for(i=0;i<9;i++){
         for(j=0;j<9;j++){
         	cout<<ans1[i][j]<<" ";
         }
	     cout<<endl;
      }
   } 
}