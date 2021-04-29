// Dylan DuBay
// connectx
// class represntation of the board
#include <iostream>
#include <vector>

class Board {
    private:
        int height, width, num_to_win;
        std::vector<std::vector<char>> board;
    public:
        Board(int height, int width, int num_to_win);
        bool has_free_space(int column);
        bool place(int column, char player);
        bool check_win(char player, int col);
        void print();
        void clear();
};

Board::Board(int h, int w, int n)
    : height(h), width(w), num_to_win(n) {
    // Dynamically allocate memory for 2d board
    board.resize(height);
    for (int i = 0; i < height; i++) board[i].resize(width);
    std::fill(board.begin(), board.end(), std::vector<char>(width, ' '));
}

// prereq: column is between [1, width] 
// returns: bool representing if the placement was successful 
bool Board::place(int column, char player) {
    for (int r = 0; r < height; r++) {
        if (board[r][column - 1] == ' ') {
            board[r][column - 1] = player;
            return true;
        }
    }
    return false;
}

// prereq: column is between [1, width]
// returns: bool representing if the player has won
bool Board::check_win(char player, int col) {
    // get row of last placed token
    int row = height - 1;
    while (board[row][col - 1] == ' ') row--;
    int tokens = 0;

    // check for win horizontally
    for (int c = 0; c < width; c++) {
        if (board[row][c] == player) {
            if (++tokens == num_to_win) return true;
        }
        else tokens = 0;
    }
    tokens = 0;

    // check vertically
    for (int r = 0; r < height; r++) {
        if (board[r][col - 1] == player) {
            if (++tokens == num_to_win) return true;
        }
        else tokens = 0;
    }
    tokens = 0;

    // check diagonally
    // from bottom left to top right
    int r = std::max(0, row - num_to_win);
    int c = std::max(0, col - num_to_win);
    while (r < std::min(height, r + num_to_win) && 
        col < std::min(width, col + num_to_win)) {
        if (board[r][c] == player) {
            if (++tokens == num_to_win) return true;
        }
        else tokens = 0;
        r++;
        c++;
    }
    tokens = 0;

    // from top left to bottom right
    r = std::min(height - 1, row + num_to_win - 1);
    c = std::max(0, col - num_to_win);
    while (r >= std::max(0, row - num_to_win - 1) && 
        col < std::min(width, col + num_to_win)) {
        if (board[r][c] == player) {
            if (++tokens == num_to_win) return true;
        }
        else tokens = 0;
        r--;
        c++;
    }
    return false;
}

// method for printing the board in the terminal
void Board::print() {
    std::cout << std::endl;
    for (int i = 1; i <= width; i++) std::cout << i << "   ";
    std::cout << std::endl;
    for (int row = board.size() - 1; row >= 0; row--) {
        for (int col = 0; col < static_cast<int>(board[row].size()); col++) {
            std::cout << board[row][col];
            if (col != width - 1) std::cout << " | ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Sets all positons on the board to empty
void Board::clear() {
    for(auto &c : board) std::fill(c.begin(), c.end(), ' ');
}
