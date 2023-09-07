#include "argparse.hpp"
#include "sudoku.h"
#include <chrono>

int main(int argc, char** argv) {
    // initialize the argument parser and container for the arguments
    argparse::ArgumentParser program("Sudokuer", "1.0", argparse::default_arguments::none);

    // add options to the parser
    program.add_argument("-h", "--help").help("Display this help message and exit.").default_value(false).implicit_value(true);
    program.add_argument("-s", "--seed").help("Seed for the random number generator.").default_value(0U).scan<'i', unsigned>();

    // parse the variables from the command line
    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error &error) {
        std::cerr << error.what() << std::endl << std::endl << program; return EXIT_FAILURE;
    }

    // print help if the help flag was provided
    if (program.get<bool>("-h")) {
        std::cout << program.help().str(); return EXIT_SUCCESS;
    }

    // extract the command line variables
    unsigned seed = program.get<unsigned>("-s") ? program.get<unsigned>("-s") : std::chrono::system_clock::now().time_since_epoch().count();

    // create the board
    Sudoku sudoku; sudoku.backtrack(seed, 1);
    std::cout << "elimination" << std::endl;
    sudoku.eliminate(seed);

    // print the sudoku
    // std::cout << sudoku << std::endl;
}
