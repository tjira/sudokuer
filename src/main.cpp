#include "argparse.hpp"
#include "sudoku.h"
#include <chrono>

int main(int argc, char** argv) {
    // initialize the argument parser and container for the arguments
    argparse::ArgumentParser program("Sudokuer", "1.0", argparse::default_arguments::none);

    // add options to the parser
    program.add_argument("-h", "--help").help("Display this help message and exit.").default_value(false).implicit_value(true);
    program.add_argument("-n", "--number").help("Set the number of solutions.").default_value(1U).scan<'i', unsigned>();
    program.add_argument("-s", "--seed").help("Seed for the random number generator.").default_value(0U).scan<'i', unsigned>();
    program.add_argument("--string").help("Print the sudoku string.").default_value(false).implicit_value(true);
    program.add_argument("--solution").help("Print the sudoku solutions.").default_value(false).implicit_value(true);

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
    Sudoku sudoku; sudoku.backtrack(seed); sudoku.eliminate(seed, program.get<unsigned>("-n"));

    // print the sudoku string
    if (program.get<bool>("--string")) std::cout << "SUDOKU: " << sudoku.string() << std::endl;

    // print the sudoku
    std::cout << sudoku << std::endl;

    // print the solutions
    if (program.get<bool>("--solution")) {
        for (size_t i = 0; i < sudoku.nsol(); i++) {
            // print the solution string
            if (program.get<bool>("--string")) std::cout << "SOLUTION #" << i + 1 << ": " << sudoku.solution(i).string() << std::endl;

            // print the solution board
            std::cout << sudoku.solution(i) << std::endl;
        }
    }
}
