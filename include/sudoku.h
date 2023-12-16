#pragma once

#include <algorithm>
#include <iostream>
#include <numeric>
#include <random>
#include <array>
#include <tuple>

typedef std::array<std::array<int, 9>, 9> Board;

class Sudoku {
public:
    // constructors
    Sudoku(const Board& board = Board{});

    // generators and solvers
    bool valid(size_t i, size_t j, int n) const;
    bool backtrack(unsigned seed, int nsol = 0);
    void eliminate(unsigned seed, int nsol = 1);

    // getters
    size_t nsol() const {return solutions.size();} std::string string() const;
    Sudoku solution(int i) const {return Sudoku(solutions.at(i));}

    // operators
    friend std::ostream& operator<<(std::ostream& os, const Sudoku& sudoku);
    int operator()(size_t i, size_t j) const {return board.at(i).at(j);}
    int& operator()(size_t i, size_t j) {return board.at(i).at(j);}

public:
    Board board; std::vector<Board> solutions;
    std::vector<std::pair<int, int>> empty;
};
