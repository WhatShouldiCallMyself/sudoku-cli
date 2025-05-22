#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

#define INTRO_MSG "Welcome to a game of sudoku!"
#define CHOOSE_MSG1 "Please pick a row (1-9)"
#define CHOOSE_MSG2 "Please pick a column (1-9)."
#define CHOOSE_MSG3 "Please pick a number to put in (1-9, 0 to re-choose row and column)."
#define ERR_SPOT_TAKEN "Chosen spot already has a number (%hu)! Please choose again.\n"
#define ERR_OUT_OF_RANGE "Chosen number is out of range!\nPlease choose again."
#define ERR_BAD_CHOICE "Invalid number! Either the row already has the number, the column already has the number, or the subgrid already has the number. Please choose again."
#define BOARD_FORMAT " %hu | %hu | %hu ‖ %hu | %hu | %hu ‖ %hu | %hu | %hu \n-----------------------------------\n %hu | %hu | %hu ‖ %hu | %hu | %hu ‖ %hu | %hu | %hu \n-----------------------------------\n %hu | %hu | %hu ‖ %hu | %hu | %hu ‖ %hu | %hu | %hu \n===================================\n %hu | %hu | %hu ‖ %hu | %hu | %hu ‖ %hu | %hu | %hu \n-----------------------------------\n %hu | %hu | %hu ‖ %hu | %hu | %hu ‖ %hu | %hu | %hu \n-----------------------------------\n %hu | %hu | %hu ‖ %hu | %hu | %hu ‖ %hu | %hu | %hu \n===================================\n %hu | %hu | %hu ‖ %hu | %hu | %hu ‖ %hu | %hu | %hu \n-----------------------------------\n %hu | %hu | %hu ‖ %hu | %hu | %hu ‖ %hu | %hu | %hu \n-----------------------------------\n %hu | %hu | %hu ‖ %hu | %hu | %hu ‖ %hu | %hu | %hu \n"

//                 row column
//                   V  V
unsigned short board[9][9] = {
	{0, 0, 0,0, 0, 0,0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}, {0, 0, 0, 0, 0, 0, 0, 0, 0}
};



unsigned short get_num() {
	#ifdef _WIN32
	return (unsigned short)(getch() - 48);
	#else
	struct termios oldt, newt;

	tcgetattr(STDIN_FILENO, &oldt);
	newt = oldt;

	newt.c_lflag &= ~(ICANON | ECHO);

	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
	const int result = getchar();
	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

	return (unsigned short)(result - 48);
	#endif
}



char is_valid_choice(unsigned short* row, unsigned short* col, unsigned short* val) {
	const unsigned short subgrid_row = (*row / 3) * 3;
    const unsigned short subgrid_col = (*col / 3) * 3;

	for (unsigned short i = 0; i < 9; i++) {
		if ( (board[i][*col] == *val) || (board[*row][i] == *val) ) // check full row & column
			return '0';
		
		if ( board[subgrid_row + (i / 3)][subgrid_col + (i % 3)] == *val ) // check 3x3 subgrid
			return '0';
	}

	return '1';
}

char is_board_complete() {
	for (short i = 0; i < 9; i++) {
		for (short j = 0; j < 9; j++) {
			if (board[i][j] == 0) { return '0'; }
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
	for (unsigned short row = 0; row < 9; row++) {
		for (unsigned short col = 0; col < 9; col++) {
			if ( (rand() % 3) != 0 ) { continue; }

			unsigned short num = (rand() % 9) + 1;
			for (unsigned short i = 0; i < 9; i++) {
				if (is_valid_choice(&row, &col, &num) == '1') { break; }
				num++;
				if (num > 9) { num -= 9; }
			}

			board[row][col] = num;
		}
	}
}



int main(/* int argc, const char** argv */) {
	init_board();
	puts(INTRO_MSG);

	while (is_board_complete() != 1) {
		fwrite("\n", sizeof(char), 1, stdout);
		print_board();

		// choose row
		puts(CHOOSE_MSG1);
		unsigned short row = get_num() - 1;
		while (row > 8) {
			puts(ERR_OUT_OF_RANGE);
			row = get_num() - 1;
		}

		// choose column
		puts(CHOOSE_MSG2);
		unsigned short col = get_num() - 1;
		while (col > 8) {
			puts(ERR_OUT_OF_RANGE);
			col = get_num() - 1;
		}

		if (board[row][col] != 0) {
			printf(ERR_SPOT_TAKEN, board[row][col]);
			continue;
		}

		// choose number to put in slot
		puts(CHOOSE_MSG3);
		unsigned short val = get_num();
		while ( (val < 1) || (val > 9) ) {
			puts(ERR_OUT_OF_RANGE);
			val = get_num();
			if (val == 0) { break; }
		}
		if (val == 0) { continue; }

		while (is_valid_choice(&row, &col, &val) != '1') {
			puts(ERR_BAD_CHOICE);
			val = get_num();
			if (val == 0) { break; }
		}
		if (val > 0) { board[row][col] = val; }
	}
	return 0;
}
