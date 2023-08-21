#include "sudoku.h"

std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku) {
    std::cout << "╔═══╤═══╤═══╦═══╤═══╤═══╦═══╤═══╤═══╗\n";
    for (size_t i = 0; i < sudoku.board.size(); i++) {
        for (size_t j = 0; j < sudoku.board.at(i).size(); j++) {
            std::cout << (j % 3 ? "│ " : "║ ") << sudoku(i, j) << " ";
        }
        if (i + 1 == sudoku.board.size()) std::cout << "║\n╚═══╧═══╧═══╩═══╧═══╧═══╩═══╧═══╧═══╝";
        else if (i % 3 == 2) std::cout << "║\n╠═══╪═══╪═══╬═══╪═══╪═══╬═══╪═══╪═══╣\n";
        else std::cout << "║\n╟───┼───┼───╫───┼───┼───╫───┼───┼───╢\n";
    }
    return os;
}

bool Sudoku::valid(size_t i, size_t j, int n) const {
    for (size_t k = 0; k < board.size(); k++) {
        if (operator()(i / 3 * 3 + k / 3, j / 3 * 3 + k % 3) == n) return false;
        else if (operator()(i, k) == n || operator()(k, j) == n) return false;
    }
    return true;
}

bool Sudoku::backtrack(unsigned seed, size_t i, size_t j) {
    if (i == board.size()) return true;
    for (int n = 1; n <= 9; n++) {
        if (valid(i, j, n)) {
            operator()(i, j) = n;
            if (backtrack(seed, i + (j + 1) / board.size(), (j + 1) % board.size())) {
                return true;
            }
            operator()(i, j) = 0;
        }
    }
    return false;
    // std::uniform_int_distribution<int> dist(1, 9);
    // std::mt19937 twister(seed);
}
