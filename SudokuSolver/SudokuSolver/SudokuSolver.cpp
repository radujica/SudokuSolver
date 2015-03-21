#include <iostream>

//for efficiency checking
#include <time.h>
#include <iomanip>

using namespace std;

const short N = 9;		//number of distinct digits in the grid; implicitly, size of the grid
const short M = 3;		//height/width of box, i.e. N/3
const short EMPTY = 0;	//digit referring to an empty spot, i.e. no digit

bool solveSudoku(short grid[N][N]);
void printGrid(short grid[N][N]);
bool findUnassignedField(short grid[N][N], short &i, short &j);
bool isValidChoice(short grid[N][N], short i, short j, short num);
bool checkForValueHorizontal(short grid[N][N], short i, short num);
bool checkForValueVertical(short grid[N][N], short j, short num);
bool checkForValueSquare(short grid[N][N], short i, short j, short num);

//TODO: change method of finding unassigned field to be more efficient
/*
	Finds the next EMPTY spot in the grid, left to right, top to bottom. 
	Returns true if such a spot is found.
*/
bool findUnassignedField(short grid[N][N], short &i, short &j)
{
	for (i=0;i<N;i++) {
		for (j=0;j<N;j++) {
			if (grid[i][j] == EMPTY) return true; 
		}
	}
	return false;
}

//TODO: change to short; efficient-ize
/*
	Returns true if num can be placed in that spot
*/
bool isValidChoice(short grid[N][N], short i, short j, short num) {
	return !checkForValueHorizontal(grid,i,num) && !checkForValueVertical(grid,j,num)
		&& !checkForValueSquare(grid,i - i%M,j - j%M,num);
}

/*
	Returns true if num is found in the horizontal line
*/
bool checkForValueHorizontal(short grid[N][N], short i, short num) {
	for (short j=0;j<N;j++) {
		if (grid[i][j] == num) return true;
	}
	return false;
}

/*
	Returns true if num is found in the vertical line
*/
bool checkForValueVertical(short grid[N][N], short j, short num) {
	for (short i=0;i<N;i++) {
		if (grid[i][j] == num) return true;
	}
	return false;
}

/*
	Returns true if num is found in the square.
	NOTE: Currently checks for N/3 squares
*/
bool checkForValueSquare(short grid[N][N], short i, short j, short num) {
	for (short a=0;a<M;a++) {
		for (short b=0;b<M;b++) {
			if (grid[a+i][b+j] == num) return true;
		}
	}
	return false;
}

/*
	Returns true when the entire grid has been filled in
*/
bool solveSudoku(short grid[N][N]) 
{
	//declare row, column indices
	short i,j;

	//end condition; the unassigned field coords are stored in i,j
	if (!findUnassignedField(grid,i,j)) return true;
	
	//loop through all possible choices, i.e. 1..N
	for (short num = 1; num <=N; num++) {
		if (isValidChoice(grid, i, j, num)) {
			grid[i][j] = num;		//assign number
			if (solveSudoku(grid)) return true;
			grid[i][j] = EMPTY;		//
		}
	}
	return false;	//no valid choice, trigger backtracking
}

/*
	Prints the grid using the standard output
*/
void printGrid(short grid[N][N]) {
	for (short i=0;i<N;i++) {
		for (short j=0;j<N;j++) {
			cout << grid[i][j] << ' ';
			//TODO: make it a for loop
			if (j == 2 || j == 5 || j == 8) cout<<' ';
		}
		cout<<endl;
	}
}

//TODO: use a pointer, instead of passing grid?
int main()
{
	clock_t startTime = clock();
	short grid[N][N] = {{5,3,0,0,7,0,0,0,0},		
                      {6,0,0,1,9,5,0,0,0},		
                      {0,9,8,0,0,0,0,6,0},		
                      {8,0,0,0,6,0,0,0,3},
					  {4,0,0,8,0,3,0,0,1},
					  {7,0,0,0,2,0,0,0,6},
					  {0,6,0,0,0,0,2,8,0},
					  {0,0,0,4,1,9,0,0,5},
					  {0,0,0,0,8,0,0,7,9}};	

	//int * arrayPointer = &grid[N][N];

    if (solveSudoku(grid) == true) printGrid(grid);
    else cout<<"No solution exists"<<endl;

	cout<<"Time taken: "<<setprecision(7)<<(double)(clock() - startTime)/CLOCKS_PER_SEC<<'s'<<endl;

    return 0;
}