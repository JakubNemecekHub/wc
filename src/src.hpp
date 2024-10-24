#include <iostream>
#include <string>
#include <ranges>
#include <filesystem>
#include <istream>
#include <fstream>
#include <sstream>
#include <optional>
#include <cctype>   // std::isspace
#include <bitset>
#include <algorithm>
#include <clocale>
#include <cstdlib>

#include "..\lib\mb.hpp"

namespace fs = std::filesystem;


std::unique_ptr<std::istream> open_stream(std::string_view file)
{
    if (file.empty())
    {
        std::unique_ptr<std::istream> s;
        s.reset(&std::cin);
        return s;
    }

    fs::path file_path { file };
    if( !fs::exists(file_path) )
    {
        std::cerr << "File " << fs::absolute(file_path) << " does not exists.";
        exit(1);
    }
    std::unique_ptr<std::ifstream> s = std::make_unique<std::ifstream>(file_path, std::ios::binary);
    if(!s->is_open())
    {
        std::cerr << "Error: Could not open the file " << fs::absolute(file_path) << std::endl;
        exit(1);
    }
    return s;
}

struct Count
{
    int lines;
    int words;
    int bytes;
    int characters;
};

Count count(std::string_view file)
{
    std::unique_ptr<std::istream> in { open_stream(file) };

    /*
        lines -> '\n'
        words -> seperated by whitespace
        bytes -> just bytes
        characters -> !mb::is_continuation
    */
   int count_lines      { 1 };
   int count_words      { 0 };
   int count_bytes      { 0 };
   int count_characters { 0 };

    bool flag_previous { mb::is_whitespace(in->peek()) };
    bool flag_current  { flag_previous        };

    unsigned char c { in->get() };
    do {
        std::cout << c << ' ' << mb::bit(c) << '\n';
        // lines
        if ( c == '\n' ) ++count_lines;
        // words
        flag_current = mb::is_whitespace(c);
        if ( flag_current & !flag_previous ) ++count_words;
        flag_previous = flag_current;
        // bytes
        ++count_bytes;
        // characters
        if ( !mb::is_continuation(c) ) ++count_characters;
        // read next byte
        c = in->get();
    }  while( !in->eof() );
    if (!flag_current) ++count_words;
    in->clear();

    std::cout << count_lines << " " << count_words << " "
              << count_bytes << " " << count_characters << '\n';
    // PROBLEM: returning Count struct causes the program to crash if
    //          inout is std::cin.
    Count res {count_lines, count_words, count_bytes, count_characters};
    return res;
}
