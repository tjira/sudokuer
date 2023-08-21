#pragma once

#include <iostream>
#include <random>
#include <tuple>

class Sudoku {
public:
    // constructors
    Sudoku(const std::array<std::array<int, 9>, 9>& board) : board(board) {}

    // generators and solvers
    bool backtrack(unsigned seed, size_t i, size_t j);
    bool valid(size_t i, size_t j, int n) const;

    // operators
    friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);
    int operator()(size_t i, size_t j) const {return board.at(i).at(j);}
    int& operator()(size_t i, size_t j) {return board.at(i).at(j);}

private:
    std::array<std::array<int, 9>, 9> board;
};
