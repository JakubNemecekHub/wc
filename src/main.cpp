#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

#include "..\lib\argparse.hpp"

#include "src.hpp"

struct Flags
{
    bool lines;
    bool words;
    bool bytes;
    bool characters;

    bool any()
    {
        return lines || words || bytes || characters;
    }
};

void print(Count result, Flags flags)
{
    bool any { flags.lines || flags.words || flags.bytes || flags.characters};
    if ( flags.lines || !flags.any() ) std::cout << result.lines      << ' ';
    if ( flags.words || !flags.any() ) std::cout << result.words      << ' ';
    if ( flags.bytes || !flags.any() ) std::cout << result.bytes      << ' ';
    if ( flags.characters )            std::cout << result.characters << ' ';
}

int main(int argc, char* argv[])
{

    argparse::ArgumentParser program("wc", "0.0.1");

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

    program.add_argument("files")
        .help("Input files")
        .remaining();

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

    Flags flags { program.get<bool>("-l"), program.get<bool>("-w"),
                  program.get<bool>("-c"), program.get<bool>("-m") };

    Count total_result {0, 0, 0, 0};
    Count result       {0, 0, 0, 0};

    try
    {
        // files
        auto files = program.get<std::vector<std::string>>("files");
        for (const auto& file : files)
        {
            fs::path file_path { file };
            if( !fs::exists(file_path) )
            {
                std::cerr << "File " << fs::absolute(file_path) << " does not exists.";
                exit(1);
            }
            std::ifstream file_stream { file_path, std::ios::binary };
            if(!file_stream.is_open())
            {
                std::cerr << "Error: Could not open the file " << fs::absolute(file_path) << std::endl;
                exit(1);
            }
            result = wc(file_stream);
            if ( files.size() > 1 ) total_result += result;
            print(result, flags);
            std::cout << file << '\n';
        }
        if ( files.size() > 1 ) print(total_result, flags);
        std::cout << "total";
    }
    catch (std::logic_error& e)
    {
        // std::cin
        result = wc(std::cin);
        print(result, flags);
    }

    return 0;

}
