#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#define INTRO_MSG "Welcome to a game of sudoku!\n"
#define CHOOSE_MSG1 "Please pick a row (1-9)\n"
#define CHOOSE_MSG2 "Please pick a column (1-9).\n"
#define CHOOSE_MSG3 "Please pick a number to put in (1-9, 0 to re-choose row and column).\n"
#define ERR_OUT_OF_RANGE "Chosen number is out of range!\nPlease pick again.\n"
#define ERR_BAD_CHOICE "Invalid number! Either the row already has the number, the column already has the number, or the subgrid already has the number. Please try again.\n"
#define BOARD_FORMAT " %d | %d | %d ‖ %d | %d | %d ‖ %d | %d | %d \n-----------------------------------\n %d | %d | %d ‖ %d | %d | %d ‖ %d | %d | %d \n-----------------------------------\n %d | %d | %d ‖ %d | %d | %d ‖ %d | %d | %d \n===================================\n %d | %d | %d ‖ %d | %d | %d ‖ %d | %d | %d \n-----------------------------------\n %d | %d | %d ‖ %d | %d | %d ‖ %d | %d | %d \n-----------------------------------\n %d | %d | %d ‖ %d | %d | %d ‖ %d | %d | %d \n===================================\n %d | %d | %d ‖ %d | %d | %d ‖ %d | %d | %d \n-----------------------------------\n %d | %d | %d ‖ %d | %d | %d ‖ %d | %d | %d \n-----------------------------------\n %d | %d | %d ‖ %d | %d | %d ‖ %d | %d | %d \n"

//        row column
//          V  V
short board[9][9] = {
	{0, 0, 0,0, 0, 0,0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}
};

char is_valid_choice(short* row, short* col, short* val) {
	const short real_row = *row - 1;
	const short real_col = *col - 1;
	const short subgrid_row = (real_row / 3) * 3;
    const short subgrid_col = (real_col / 3) * 3;

	for (short i = 0; i < 9; i++) {
		if ( (board[i][real_col] == *val) || (board[real_row][i] == *val) ) // check full row & column
			return '0';
		
		if ( board[subgrid_row + (i / 3)][subgrid_col + (i % 3)] == *val ) // check 3x3 subgrid
			return '0';
	}

	return '1';
}

char is_board_complete() {
	for (short i = 0; i < 9; i++) {
		for (short j = 0; j < 9; j++) {
			if (board[i][j] == 0)
				return '0';
		}
	}

	return '1';
}

void print_board() { // yandere sim ahh code 💀💀💀
	printf(BOARD_FORMAT,
		board[0][0], board[0][1], board[0][2], board[0][3], board[0][4], board[0][5], board[0][6], board[0][7], board[0][8],
		board[1][0], board[1][1], board[1][2], board[1][3], board[1][4], board[1][5], board[1][6], board[1][7], board[1][8],
		board[2][0], board[2][1], board[2][2], board[2][3], board[2][4], board[2][5], board[2][6], board[2][7], board[2][8],
		board[3][0], board[3][1], board[3][2], board[3][3], board[3][4], board[3][5], board[3][6], board[3][7], board[3][8], 
		board[4][0], board[4][1], board[4][2], board[4][3], board[4][4], board[4][5], board[4][6], board[4][7], board[4][8],
		board[5][0], board[5][1], board[5][2], board[5][3], board[5][4], board[5][5], board[5][6], board[5][7], board[5][8],
		board[6][0], board[6][1], board[6][2], board[6][3], board[6][4], board[6][5], board[6][6], board[6][7], board[6][8],
		board[7][0], board[7][1], board[7][2], board[7][3], board[7][4], board[7][5], board[7][6], board[7][7], board[7][8],
		board[8][0], board[8][1], board[8][2], board[8][3], board[8][4], board[8][5], board[8][6], board[8][7], board[8][8]);
}

void init_board() {
	srand(time(NULL));
	for (short row = 0; row < 9; row++) {
		if ( (rand() % 9) == 0 ) { continue; }

		for (short col = 0; col < 9; col++) {
			if ( (rand() % 3) == 0 ) { continue; }

			short num = (rand() % 9) + 1;
			for (short i = 0; i < 9; i++) {
				if (is_valid_choice(&row, &col, &num) == '1') { break; }
				num++;
				if (num > 9) { num -= 9; }
			}

			board[row][col] = num;
		}
	}
}

short get_num() {
	#ifdef _WIN32
	return (short)(getch() - 48);
	#else
	struct termios oldt, newt;

	tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;

	newt.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	const int result = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return (short)(result - 48);
	#endif
}

int main(/* int argc, const char** argv */) {
	init_board();
	printf(INTRO_MSG);

	while (is_board_complete() != 1) {
		print_board();
		printf(CHOOSE_MSG1);
		short row = get_num();
		while ( (row < 1) || (row > 9) ) {
			printf(ERR_OUT_OF_RANGE);
			row = get_num();
		}

		printf(CHOOSE_MSG2);
		short col = get_num();
		while ( (col < 1) || (col > 9) ) {
			printf(ERR_OUT_OF_RANGE);
			col = get_num();
		}

		printf(CHOOSE_MSG3);
		short val = get_num();
		while ( (val < 1) || (val > 9) ) {
			printf(ERR_OUT_OF_RANGE);
			val = get_num();
			if (val == 0) { break; }
		}
		if (val == 0) { continue; }

		while (is_valid_choice(&row, &col, &val) != '1') {
			printf(ERR_BAD_CHOICE);
			val = get_num();
			if (val == 0) { break; }
		}
		if (val > 0) { board[row-1][col-1] = val; }
	}
	return 0;
}
