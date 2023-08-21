#include "argparse.hpp"
#include "sudoku.h"

int main(int argc, char** argv) {
    // initialize the argument parser and container for the arguments
    argparse::ArgumentParser program("Sudokuer", "1.0", argparse::default_arguments::none);

    // add options to the parser
    program.add_argument("-h", "--help").help("Display this help message and exit.").default_value(false).implicit_value(true);

    // extract the variables from the command line
    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error &error) {
        std::cerr << error.what() << std::endl << std::endl << program; return EXIT_FAILURE;
    }

    // print help if the help flag was provided
    if (program.get<bool>("-h")) {
        std::cout << program.help().str(); return EXIT_SUCCESS;
    }

    // create the board
    Sudoku sudoku(std::array<std::array<int, 9>, 9>{});
    sudoku.backtrack(1, 0, 0);

    // print the sudoku
    std::cout << sudoku << std::endl;
}
