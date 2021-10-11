#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define NUM_ROWS 8
#define NUM_COLS 8

#define SPACE 0
#define WALL -1
#define EXIT -2

/***********************************************************/
/***********************************************************/
/******* ADD THE REQUIRED FUNCTIONS BELOW THIS POINT *******/
/***********************************************************/
/***********************************************************/

// Your function definitions should go here...

void InitialiseRoad(int road[NUM_ROWS][NUM_COLS], char side, int pos)
{

	// variable to keep track of rows 
	int i = 0;
	// variable to keep track of columns
	int j = 0;

	// loop through the rows and columns and assign the appropriate values
	for (i = 0; i < NUM_ROWS; i++) {
		for (j = 0; j < NUM_COLS; j++) {
			
			// first initialise the road to be all blank spaces 
			road[i][j] = SPACE; 

			// set up the walls
			if (i == 0) {
				road[0][j] = WALL;
			} else if (i == NUM_ROWS - 1) {
				road[NUM_ROWS - 1][j] = WALL;
			} else if (j == 0) {
				road[i][0] = WALL;
			} else if (j == NUM_COLS - 1) {
				road[i][NUM_COLS - 1] = WALL;
			}
			
			// set up the exits
			if (side == 'N') {
				road[0][pos] = EXIT;
			} else if (side == 'S') {
				road[NUM_ROWS - 1][pos] = EXIT;
			} else if (side == 'W') {
				road[pos][0] = EXIT;
			} else if (side == 'E') {
				road[pos][NUM_COLS - 1] = EXIT;
			} 
			

		}
	}

}

void PrintRoad(int road[NUM_ROWS][NUM_COLS])
{
	int i;
	int j;

	for (i = 0; i < NUM_ROWS; i++) {
		for (j = 0; j < NUM_COLS; j++) {
			
			// print the road
			if (road[i][j] == WALL) {
				printf("#");
			} else if (road[i][j] == EXIT) {
				printf("O");
			} else if (road[i][j] == SPACE) {
				printf(" ");
			}

			// print the cars onto the road 
			if (road[i][j] > SPACE) {
				printf("%c", road[i][j] + 64);
			}

		}
		// print a new line character so each row is on a new line
		printf("\n");
	}

} 

double PercentUsed(int road[NUM_ROWS][NUM_COLS])
{
	int i;
	int j;
	double used = 0;
	double percentUsed;

	// only scan through the internal part of the grid where the road is 
	for (i = 1; i < NUM_ROWS - 1; i++) {
		for (j = 1; j < NUM_COLS - 1; j++) {
			
			if (road[i][j] != SPACE) {
				used++;
			}
		
		}
	}

	// return the percentage of the road used
	return percentUsed = (used/((NUM_COLS - 2)*(NUM_ROWS - 2))) * 100;

}

void AddCar(int road[NUM_ROWS][NUM_COLS], int row, int col, int size)
{
	// variables to scan through rows and columns of the road 
	int i, j;
	// variable to add a car 
	int cars = 0;

	// check to see if there are already cars on the road 
	for (i = 1; i < NUM_ROWS - 1; i++) {
		for (j = 1; j < NUM_COLS - 1; j++) {

			// if there is already a car on the road, store the number of the car in the 'cars' variable 
			if (road[i][j] > cars) {
				cars = road[i][j];
			} 

		}
	}

	// assign the value for the car to be added
	cars++;

	// for a horizontal car 
	// if there is already a car in the road then return so the function is not executed
	for (j = col; j < col + size; j++) {
		
		if (road[row][j] != SPACE) {
			return;
		} 

	}
	// else add the car onto the road 
	if ((size > 0) && (size <= NUM_COLS - 2)) {
		
		for (j = col; j < col + size; j++){
			road[row][j] = cars;
		}

	}

	// for a vertical car 
	// if there is already a car in the road then return so the function doesn't execute
	for (i = row; i < size *(-1) + row; i++) {
		
		if (road[i][col] != SPACE) {
			return;
		}

	}
	// else add the car onto the road 
	if ((size < 0) && (size <= NUM_ROWS - 2)) {
		
		for (i = row; i < size *(-1) + row; i++) {
			road[i][col] = cars;
		}

	}
	
}

void FindCar(int road[NUM_ROWS][NUM_COLS], char move, int *rowStart, int *colStart, int *rowEnd, int *colEnd)
{
	int i,j;
	// count is used so after the first location of the car is found it is stored 
	// and then when it is greater than 0, the loop to find the car will continue 
	// until the last location of the car is found
	int count = 0;

	for (i = 1; i < NUM_ROWS - 1; i++) {
		for (j = 1; j < NUM_COLS - 1; j++) {
			// find the location of the specified car and store the left-most 
			// or upper-most part of the car in rowStart and colStart
			if (road[i][j] == (move - 64) && count == 0) {
				*rowStart = i;
				*colStart = j;
				count++;
			} // find the location of the specified car and store the right-most 
			  // or lowest-most part of the car in rowEnd and colEnd
				else if (road[i][j] == (move - 64) && count > 0) {
				*rowEnd = i;
				*colEnd = j;
			}

		}
	}


}


int MoveCar(int road[NUM_ROWS][NUM_COLS], int r0, int c0, int r1, int c1)
{
	int row, col;
	// variable to keep track if the car has already been moved.
	// initally movement is 0 and increase when the car has been moved.
	int movement = 0;
	int moved = 0;
	// variable to check if the car is located next to the exit and is able to move out of the road 
	int exit;
	

	// move for a horizontal car
	if (r0 == r1) {

		// if there is space to the left of the car, the car will move to the left as far as possible		
		while (road[r0][c0 - 1] == SPACE) {
			for (col = c0; col < c1; col++) {
				road[r0][c0 - 1] = road[r0][c0];
				road[r1][c1] = SPACE;
			}
			// change the column variables to represent the new location of the car 
			c1--; 
			c0--;
			// movement increases as car has been moved
			movement++;
			moved++;
		} 
		
		// else if there is no space to the left of the car and the car hasn't already been moved 
		// then move the car to the right as far as possible
		if ((road[r1][c1 + 1] == SPACE) && (movement == 0)) {

			while (road[r1][c1 + 1] == SPACE) {
				for (col = c1; col > c0; col--) {
					road[r1][c1 + 1] = road[r1][c1];
					road[r0][c0] = SPACE;
				}
				// change the column variables to represent the new location of the car
				c0++;
				c1++;
				// moved variable increases as car has been moved
				moved++;
			}

		}
		
	}

	// move for a vertical car 
	if (c0 == c1) {

		// if there is space above the car, the car will move upwards as far as possible 
		if (road[r0 - 1][c0] == SPACE) {

			while (road[r0 - 1][c0] == SPACE) {
				for (row = r0; row < r1; row++) {
				road[row - 1][c0] = road[row][c0];
				road[r1][c1] = SPACE;
				}
			// change the row variables to represent the new location of the car
			r0--; 
			r1--;
			// movement increases as car has been moved
			movement++;
			moved++;
			} 
		} 

		// else if there is no space aboe the car and the car hasn't already been moved
		// then move the car downwards as far as possible 
		if ((road[r1 + 1][c1] == SPACE) && (movement == 0)) {

			while (road[r1 + 1][c1] == SPACE) {
				for (row = r1; row > r0; row--) {
				road[row + 1][c1] = road[row][c1];
				road[r0][c0] = SPACE;
				}
			// change the row variables to represent the new location of the car 
			r0++; 
			r1++;
			// moved variable increases to show car has been moved
			moved++;
			} 
		} 
		
		
	}

	
	// check if horizontal or vertical car is lined up with exit and that the car has been moved before exiting
	if (((road[r1][c1 + 1] == EXIT) || (road[r0][c0 - 1] == EXIT)) && (r0 == r1) && (moved > 0)) {
		// if the car is lined up and is able to exit, then exit = 1
		exit = 1;
	} else if (((road[r0 - 1][c0] == EXIT) || (road[r1 + 1][c1] == EXIT)) && (c0 == c1) && (moved > 0)) {
		// if the car is lined up and is able to exit, then exit = 1
		exit = 1;
	} else {
		// if the car is not lined up with the exit, then exit = 0
		exit = 0;
	}

	return exit;

}
/***********************************************************/
/***********************************************************/
/********* DO NOT MODIFY ANY CODE BELOW THIS POINT *********/
/***********************************************************/
/***********************************************************/

/* Function to obtain capital letter as input */
char GetMove(void)
{
	char move;
	printf("\nMove car: ");
	scanf("%c", &move);
	// Ignore non-capital letter inputs
	while ((move < 'A') || (move > 'Z')) {
		scanf("%c", &move);
	}
	return move;
}

/* The main Traffic Jam simulation */
int main(void)
{
	int gameOver = 0;
	int road[NUM_ROWS][NUM_COLS];
	int rowStart, colStart, rowEnd, colEnd;
	char input;

	/* Print banner */
	printf(" _____           __  __ _            _                                        \n");
	printf("|_   _| __ __ _ / _|/ _(_) ___      | | __ _ _ __ ___           ____          \n");
	printf("  | || '__/ _` | |_| |_| |/ __|  _  | |/ _` | '_ ` _ \\  --   __/  |_\\_      \n");
	printf("  | || | | (_| |  _|  _| | (__  | |_| | (_| | | | | | | --- |  _     _``-.    \n");
	printf("  |_||_|  \\__,_|_| |_| |_|\\___|  \\___/ \\__,_|_| |_| |_| --  '-(_)---(_)--'\n\n");

	/* Initialise the road and add cars */
	InitialiseRoad(road, 'N', 5);
	AddCar(road, 3, 3, 2);
	AddCar(road, 1, 1, 2);
	AddCar(road, 2, 1, 3);
	AddCar(road, 3, 2, -2);
	AddCar(road, 5, 2, -2);
	AddCar(road, 4, 4, -2);
	AddCar(road, 6, 3, 3);
	AddCar(road, 1, 5, -3);
	AddCar(road, 2, 6, -2);


	
	/* Print status */
	printf("ENGGEN131 2020 - C Project\nTraffic Jam!  There is a lot of traffic on the road!\n");
	printf("In fact, %.2f%% of the road is cars!\n\n", PercentUsed(road));

	/* Main simulation loop */
	while (!gameOver) {
		PrintRoad(road);
		input = GetMove();
		FindCar(road, input, &rowStart, &colStart, &rowEnd, &colEnd);
		gameOver = MoveCar(road, rowStart, colStart, rowEnd, colEnd);
	}

	/* A car has exited - the simulation is over */
	PrintRoad(road);
	printf("\nCongratulations, you're on your way again!");

	return 0;
}
