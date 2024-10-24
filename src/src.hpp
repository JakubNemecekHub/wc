#include <istream>
#include <cctype>   // std::isspace

#include "..\lib\mb.hpp"

struct Count
{
    int lines;
    int words;
    int bytes;
    int characters;

    Count& operator+=(const Count& rhs)
    {
        lines += rhs.lines;
        words += rhs.words;
        bytes += rhs.bytes;
        characters += rhs.characters;
        return *this;
    }

    friend Count operator+(Count lhs, const Count& rhs)
    {
        lhs += rhs;
        return lhs;
    }
};

Count wc(std::istream& in)
{

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

    bool flag_previous { mb::is_whitespace(in.peek()) };
    bool flag_current  { flag_previous        };

    unsigned char c { in.get() };
    do {
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
        c = in.get();
    }  while( !in.eof() );
    if (!flag_current) ++count_words;

    return {count_lines, count_words, count_bytes, count_characters};
}
