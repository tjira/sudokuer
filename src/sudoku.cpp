#include "sudoku.h"

Sudoku::Sudoku(const Board& board) : board(board) {
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            if (!operator()(i, j)) empty.push_back({i, j});
        }
    }
}

std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku) {
    std::cout << "╔═══╤═══╤═══╦═══╤═══╤═══╦═══╤═══╤═══╗\n";
    for (size_t i = 0; i < sudoku.board.size(); i++) {
        for (size_t j = 0; j < sudoku.board.at(i).size(); j++) {
            std::cout << (j % 3 ? "│ " : "║ ") << (sudoku(i, j) ? std::to_string(sudoku(i, j)) : " ") << " ";
        }
        if (i + 1 == sudoku.board.size()) std::cout << "║\n╚═══╧═══╧═══╩═══╧═══╧═══╩═══╧═══╧═══╝";
        else if (i % 3 == 2) std::cout << "║\n╠═══╪═══╪═══╬═══╪═══╪═══╬═══╪═══╪═══╣\n";
        else std::cout << "║\n╟───┼───┼───╫───┼───┼───╫───┼───┼───╢\n";
    }
    return os;
}

std::string Sudoku::string() const {
    // define the string
    std::string string;

    // fill the string
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            string += std::to_string(operator()(i, j));
        }
    }

    // return the string
    return string;
}

bool Sudoku::valid(size_t i, size_t j, int n) const {
    for (size_t k = 0; k < board.size(); k++) {
        if (operator()(i / 3 * 3 + k / 3, j / 3 * 3 + k % 3) == n) return false;
        else if (operator()(i, k) == n || operator()(k, j) == n) return false;
    }
    return true;
}

bool Sudoku::backtrack(unsigned seed, int nsol) {
    // if the board is filled
    if (!empty.size()) {solutions.push_back(board); 
        return nsol ? solutions.size() >= (size_t)nsol : true;
    }

    // define the cell indices
    size_t i = empty.at(0).first, j = empty.at(0).second;

    // create the array of available values
    std::array<int, 9> numbers; std::iota(numbers.begin(), numbers.end(), 1);
    std::shuffle(numbers.begin(), numbers.end(), std::mt19937(seed));

    // fill loop over the available numbers
    for (int n : numbers) {
        // if the current number can be assigned to the position
        if (valid(i, j, n)) {
            // assign the value to the cell and remove empty cell
            operator()(i, j) = n; empty.erase(empty.begin(), empty.begin() + 1);

            // backtrack from the next cell
            if (backtrack(++seed, nsol)) return true;

            // unassign the value and insert the cell back if backtracking failed
            operator()(i, j) = 0; empty.insert(empty.begin(), {i, j});
        }
    }

    // backtrack from the previous cell
    return false;
}

void Sudoku::eliminate(unsigned seed, int nsol) {
    // create the array of all cell coordinates
    std::vector<std::pair<int, int>> cells;

    // generate all pairs of indices
    for (size_t i = 0; i < 9; i++) {
        for (size_t j = 0; j < 9; j++) {
            cells.push_back({i, j});
        }
    }

    // shuffle the indices
    std::shuffle(cells.begin(), cells.end(), std::mt19937(seed));

    // perform the elimination
    for (size_t i = 0; i < 45; i++) {
        // create test sudoku
        Sudoku test(board); test.empty = empty;

        // remove one number from the test board
        if (test(cells.at(i).first, cells.at(i).second)) {
            test.empty.push_back({cells.at(i).first, cells.at(i).second});
            test.board.at(cells.at(i).first).at(cells.at(i).second) = 0;
        }

        // solve the test board
        test.backtrack(seed, nsol + 1);

        // accept if the solutions match
        if (test.solutions.size() <= nsol) {
            // add empty cell and make it empty
            empty.push_back({cells.at(i).first, cells.at(i).second});
            operator()(cells.at(i).first, cells.at(i).second) = 0;

            // assign the solutions
            solutions = test.solutions;
        }
    }
}
