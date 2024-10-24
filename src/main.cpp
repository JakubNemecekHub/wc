#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

#include "..\lib\argparse.hpp"

#include "src.hpp"

int main(int argc, char* argv[])
{

    argparse::ArgumentParser program("wc", "0.0.1");

    // Positional argument - name of the file.
    program.add_argument("file")
        .help("Input file.")
        .default_value("");

    // Optional arguments - flags.
    program.add_argument("-c")
        .help("Count number of bytes in file.")
        .flag();
    program.add_argument("-l")
        .help("Count number of lines in file.")
        .flag();
    program.add_argument("-w")
        .help("Count number of words in file.")
        .flag();
    program.add_argument("-m")
        .help("Count number of characters in file.")
        .flag();

    try
    {
        program.parse_args(argc, argv);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        std::cerr << program;
        return 0;
    }
    bool any_flag { program.is_used("-l") || program.is_used("-w") || program.is_used("-c") || program.is_used("-m") };

    Count result {0, 0, 0, 0};
    std::string file { program.get<std::string>("file") };
    if ( file.empty() )
    {
        // std::cin
        result = wc(std::cin);
    }
    else
    {
        // file
        fs::path file_path { file };
        if( !fs::exists(file_path) )
        {
            std::cerr << "File " << fs::absolute(file_path) << " does not exists.";
            exit(1);
        }
        std::ifstream file { file_path, std::ios::binary };
        if(!file.is_open())
        {
            std::cerr << "Error: Could not open the file " << fs::absolute(file_path) << std::endl;
            exit(1);
        }
        result = wc(file);
    }

    if (program["-l"] == true || !any_flag) std::cout << result.lines << ' ';
    if (program["-w"] == true || !any_flag) std::cout << result.words << ' ';
    if (program["-c"] == true || !any_flag) std::cout << result.bytes << ' ';
    if (program["-m"] == true) std::cout << result.characters << ' ';
    std::cout << file << '\n';

    return 0;

}
