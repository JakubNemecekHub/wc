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

    Count count { 1, 0, 0, 0 };

    bool flag_previous { mb::is_whitespace(in.peek()) };
    bool flag_current  { flag_previous        };

    unsigned char c { in.get() };
    do {
        // lines
        if ( c == '\n' ) ++count.lines;
        // words
        flag_current = mb::is_whitespace(c);
        if ( flag_current & !flag_previous ) ++count.words;
        flag_previous = flag_current;
        // bytes
        ++count.bytes;
        // characters
        if ( !mb::is_continuation(c) ) ++count.characters;
        // read next byte
        c = in.get();
    }  while( !in.eof() );
    if (!flag_current) ++count.words;

    return count;
}
