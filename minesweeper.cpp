//minesweeper 

#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
using namespace std;

#define BEGINNER 0 
#define INTERMEDIATE 1 
#define ADVANCED 2 
#define MAXSIDE 16 
#define MAXMINES 40 
#define MOVESIZE 216 // (16 * 16 - 40)   maximum to which we can move

int SIDE; // side length of the board 
int MINES; // number of mines on the board 

// myboard will only let you see - and number
// realboard will let u see -, number and mines
char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE];

// A Utility Function to check whether given cell (row, col) 
// is a valid cell or not 
bool isValid(int row, int col)
{
	// Returns true if row number and column number 
	// is in range 
	return (row >= 0) && (row < SIDE) &&
		(col >= 0) && (col < SIDE);
}

// A Utility Function to check whether given cell (row, col) 
// has a mine or not. 
bool contains_mine(int row, int col, char board[][MAXSIDE])
{
	if (board[row][col] == '@')
		return (true);
	else
		return (false);
}



// A Function to print the current gameplay board 
void printBoard(char myBoard[][MAXSIDE])
{
	int i, j;

	cout << "    ";

	for (i = 0; i < SIDE; i++) {
		if(i<10)
			cout << i << "  ";
		else
			cout << i << " ";
	}
	cout<<"\n\n";

	for (i = 0; i < SIDE; i++)
	{
		if (i < 10)
			cout << i << "   ";
		else
			cout << i << "  ";

		for (j = 0; j < SIDE; j++)
			cout<<myBoard[i][j]<<"  ";
		cout<<"\n";
	}
	return;
}
// A Function to get the user's move 
void printBoard(char myBoard[][MAXSIDE],int key)
{
	int i, j;

	cout << "    ";

	for (i = 0; i < SIDE; i++) {
		if (i < 10)
			cout << i << "  ";
		else
			cout << i << " ";
	}
	cout << "\n\n";

	for (i = 0; i < SIDE; i++)
	{
		if (i < 10)
			cout << i << "   ";
		else
			cout << i << "  ";

		for (j = 0; j < SIDE; j++)
			cout << myBoard[i][j] << "  ";
		cout << "\n";
	}
	return;
}
//the above function is to print original board using function overloading
void makeMove(int* x, int* y)
{
	// Take the input move 
	cout << "Enter your move, (row, column) -> ";
	cin >> (*x) >> (*y);
	return;
}
// A Function to count the number of 
// mines in the adjacent cells 
int countAdjacentMines(int row, int col, int mines[][2],char realBoard[][MAXSIDE])
{

	int i;
	int count = 0;

	/*
		Count all the mines in the 8 adjacent
		cells

			 N.W  N   N.E
		       \  |  /
			    \ | /
			W----Cell----E
			    / | \
			   /  |  \
			 S.W  S   S.E

	*/

	//----------- 1st Neighbour (North) ------------ 

		// Only process this cell if this is a valid one 
	if (isValid(row - 1, col) == true)
	{
		if (contains_mine(row - 1, col, realBoard) == true)
			count++;
	}

	//----------- 2nd Neighbour (South) ------------ 

		// Only process this cell if this is a valid one 
	if (isValid(row + 1, col) == true)
	{
		if (contains_mine(row + 1, col, realBoard) == true)
			count++;
	}

	//----------- 3rd Neighbour (East) ------------ 

		// Only process this cell if this is a valid one 
	if (isValid(row, col + 1) == true)
	{
		if (contains_mine(row, col + 1, realBoard) == true)
			count++;
	}

	//----------- 4th Neighbour (West) ------------ 

		// Only process this cell if this is a valid one 
	if (isValid(row, col - 1) == true)
	{
		if (contains_mine(row, col - 1, realBoard) == true)
			count++;
	}

	//----------- 5th Neighbour (North-East) ------------ 

		// Only process this cell if this is a valid one 
	if (isValid(row - 1, col + 1) == true)
	{
		if (contains_mine(row - 1, col + 1, realBoard) == true)
			count++;
	}

	//----------- 6th Neighbour (North-West) ------------ 

		// Only process this cell if this is a valid one 
	if (isValid(row - 1, col - 1) == true)
	{
		if (contains_mine(row - 1, col - 1, realBoard) == true)
			count++;
	}

	//----------- 7th Neighbour (South-East) ------------ 

		// Only process this cell if this is a valid one 
	if (isValid(row + 1, col + 1) == true)
	{
		if (contains_mine(row + 1, col + 1, realBoard) == true)
			count++;
	}

	//----------- 8th Neighbour (South-West) ------------ 

		// Only process this cell if this is a valid one 
	if (isValid(row + 1, col - 1) == true)
	{
		if (contains_mine(row + 1, col - 1, realBoard) == true)
			count++;
	}

	return (count);
}

// A Recursive Fucntion to play the Minesweeper Game 
bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE],
	int mines[][2], int row, int col, int* movesLeft)
{

	// Base Case of Recursion 
	if (myBoard[row][col] != '-')             //for first time it will not be true
		return (false);                       //if my board already contains number then just return
											//and ask for new values

	int i, j;

	// You opened a mine 
	// You are going to lose 
	if (realBoard[row][col] == '@')            //for first time it will never be true 
	{
		myBoard[row][col] = '@';

		for (i = 0; i < MINES; i++)
			myBoard[mines[i][0]][mines[i][1]] = '@';   //giving all the values of the mines to myboard

		printBoard(myBoard);
		cout<<"\nYou lost!\n";
		return (true);
	}

	else
	{
		// Calculate the number of adjacent mines and put it 
		// on the board 
		int count = countAdjacentMines(row, col, mines, realBoard);
		(*movesLeft)--;

		myBoard[row][col] = count + '0';     //since myboard all values are character

		if (!count)    //it will call recursivley the function if the count=0 or no mine nearby
		{
			/*
			Recur for all 8 adjacent cells

				N.W   N   N.E
				   \  |  /
					\ | /
				W----Cell----E
					/ | \
				   /  |  \
				 S.W  S   S.E

		
			*/

			//----------- 1st Neighbour (North) ------------ 


			if (isValid(row - 1, col) == true)
			{
				if (contains_mine(row - 1, col, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row - 1, col, movesLeft);
			}

			//----------- 2nd Neighbour (South) ------------ 

			if (isValid(row + 1, col) == true)
			{
				if (contains_mine(row + 1, col, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row + 1, col, movesLeft);
			}

			//----------- 3rd Neighbour (East) ------------ 


			if (isValid(row, col + 1) == true)
			{
				if (contains_mine(row, col + 1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col + 1, movesLeft);
			}

			//----------- 4th Neighbour (West) ------------ 

			if (isValid(row, col - 1) == true)
			{
				if (contains_mine(row, col - 1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col - 1, movesLeft);
			}

			//----------- 5th Neighbour (North-East) ------------ 

			if (isValid(row - 1, col + 1) == true)
			{
				if (contains_mine(row - 1, col + 1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row - 1, col + 1, movesLeft);
			}

			//----------- 6th Neighbour (North-West) ------------ 

			if (isValid(row - 1, col - 1) == true)
			{
				if (contains_mine(row - 1, col - 1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row - 1, col - 1, movesLeft);
			}

			//----------- 7th Neighbour (South-East) ------------ 

			if (isValid(row + 1, col + 1) == true)
			{
				if (contains_mine(row + 1, col + 1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row + 1, col + 1, movesLeft);
			}

			//----------- 8th Neighbour (South-West) ------------ 

			if (isValid(row + 1, col - 1) == true)
			{
				if (contains_mine(row + 1, col - 1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row + 1, col - 1, movesLeft);
			}
		}

		return (false);
	}
}

// A Function to place the mines randomly on the board 
void placeMines(int mines[][2], char realBoard[][MAXSIDE])
{
	bool mark[MAXSIDE * MAXSIDE];                  //1D ARRay of postion of mines

	memset(mark, false, sizeof(mark));              //basically making every flag as flase this flag will used in mines creation

	// Continue until all random mines have been created. 
	for (int i = 0; i < MINES; )
	{
		int random = rand() % (SIDE * SIDE);
		int x = random / SIDE;
		int y = random % SIDE;

		// Add the mine if no mine is placed at this 
		// position on the board 
		if (mark[random] == false)
		{
			// Row Index of the Mine 
			mines[i][0] = x;
			// Column Index of the Mine 
			mines[i][1] = y;

			// Place the mine 
			realBoard[x][y] = '@';
			mark[random] = true;
			i++;
		}
	}

	return;
}

// A Function to initialise the game 
void initialise(char realBoard[][MAXSIDE], char myBoard[][MAXSIDE])
{
	// Initiate the random number generator so that 
	// the same configuration doesn't arises 
	srand(time(NULL));

	// Assign all the cells as mine-free 
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			myBoard[i][j] = realBoard[i][j] = '-';
		}
	}

	return;
}


// A function to replace the mine from (row, col) and put 
// it to a vacant space 
void replaceMine(int row, int col, char board[][MAXSIDE])
{
	for (int i = 0; i < SIDE; i++)
	{
		for (int j = 0; j < SIDE; j++)
		{
			// Find the first location in the board 
			// which is not having a mine and put a mine 
			// there. 
			if (board[i][j] != '@')
			{
				board[i][j] = '@';
				board[row][col] = '-';
				return;
			}
		}
	}
	return;
}

// A Function to play Minesweeper game 
void playMinesweeper()
{
	// Initially the game is not over 
	bool gameOver = false;

	// Actual Board and My Board 


	int movesLeft = SIDE * SIDE - MINES, x, y;    // x and y for current moves
	char cheat[6];
	int mines[MAXMINES][2]; // stores (x,y) coordinates of all mines. 

	initialise(realBoard, myBoard);

	// Place the Mines randomly 
	placeMines(mines, realBoard);


	// You are in the game until you have not opened a mine 
	// So keep playing 

	int currentMoveIndex = 0;
	while (gameOver == false)
	{
		cout<<"Current Status of Board : \n";
		printBoard(myBoard);
		cout << endl << endl;
		//printBoard(realBoard,1); if we want to cheat
		makeMove(&x, &y);


		// This is to guarantee that the first move is 
		// always safe 
		// If it is the first move of the game 
		if (currentMoveIndex == 0)
		{
			// If the first move itself is a mine 
			// then we remove the mine from that location 
			if (contains_mine(x, y, realBoard) == true)
				replaceMine(x, y, realBoard);
		}

		currentMoveIndex++;

		gameOver = playMinesweeperUtil(myBoard, realBoard, mines, x, y, &movesLeft);

		if ((gameOver == false) && (movesLeft == 0))
		{
			cout<<"\nYou won !\n";
			gameOver = true;
		}
	}
	return;
}

// A Function to choose the difficulty level 
// of the game 
void chooseDifficultyLevel()
{


	int level;

	cout<<"Enter the Difficulty Level\n";
	cout<<"Press 0 for BEGINNER (5 * 5 Cells and 6 Mines)\n";
	cout<<"Press 1 for INTERMEDIATE (9 * 9 Cells and 10 Mines)\n";
	cout<<"Press 2 for ADVANCED (16 * 16 Cells and 40 Mines)\n";

	cin>>level;

	if (level == BEGINNER)
	{
		SIDE = 5;
		MINES = 6;
	}

	if (level == INTERMEDIATE)
	{
		SIDE = 9;
		MINES = 10;
	}

	if (level == ADVANCED)
	{
		SIDE = 16;
		MINES = 40;
	}

	return;
}

// Driver Program to test above functions 
int main()
{
	/* Choose a level between
	--> BEGINNER = 5 * 5 Cells and 6 Mines
	--> INTERMEDIATE = 9 * 9 Cells and 10 Mines
	--> ADVANCED = 16 * 16 Cells and 40 Mines
	*/
	chooseDifficultyLevel();

	playMinesweeper();

	return (0);
}
