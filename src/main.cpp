// Dylan DuBay
// Connectx
#include "Board.cpp"

// Global variables representing the size of the board and the number of 
// tokens required in a row to win
int height, width, num_to_win;

// Helper function used to validate a column number input from the user
// and prompt the user repeatedly if the input is invalid
// params: input - char read in from user
// output: valid column number
int get_column_from_user(char input) {
		int column = (int)(input - '0');
		while (column <= 0 || column > width) {
		    std::cout << "Please enter a valid column number:" << std::endl;
				std::cin >> input;
				column = (int)(input - '0');
		}
		return column;
}

int main() {
    // Prompt user to enter game parameters
    std::cout << "Enter the height of the board: ";
    std::cin >> height;
    std::cout << "Enter the width of the board: ";
    std::cin >> width;
    std::cout << "Enter the number of tokens in a row to win: ";
    std::cin >> num_to_win;
    // initialize data structure
    Board game_board(height, width, num_to_win);
    // begin game loop
    bool quit = false;
    char input;
    char player = 'X';
    while (!quit) {
        game_board.print();
        // prompt user for command
        std::cout << "Player " << player << 
            " enter a column to place your token: ";
        // read input from terminal
        std::cin >> input;
				// validate input
				int column = get_column_from_user(input);
				// assert column can be played in, if not then get valid column
        while (!game_board.place(column, player)) {
					std::cout << "Column " << column << " is full, please chose another" << std::endl;
					std::cin >> input;
					column = get_column_from_user(input);
				}
				// Check for win by last token played
        if (game_board.check_win(player, column)) {
            game_board.print();
            std::cout << "Player " << player << " has won!" << std::endl;
						// Prompt user asking if they would like to go again
            std::cout << "Would you like to play again? (y/n)" << std::endl;
            std::cin >> input;
            if (input == 'n') quit = true;
            else game_board.clear();
        }
				// switch between players
        player = (player == 'X') ? 'O' : 'X';
    }
}
