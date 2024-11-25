# wc

Implementation os the **wc** Unix command in c++. As per https://codingchallenges.fyi/challenges/challenge-wc/.

## Usage

`wc [--help] [--version] [-c] [-l] [-w] [-m] [files]...`

## Options
- **--help** Display help and exit
- **--version** Output version information and exit
- **-c, --bytes** Print the byte counts
- **-l, --lines** Print the newline counts
- **-w, --words** Print the word counts
- **-m, --chars** Print the character counts
- **--files0-from=F** Name or names of files to process. If no name is given uses Standard input.
- **-L, --max-line-length** Print the length of the longest line NOT IMPLEMENTED

Grouping of options is supported. `wc -l -w -c test.txt` is the same as `wc -lwc test.txt`.

Default options are `-l`, `-w` and `-c`.

The order of the options *does not* change the order of the output. It is always in the order as if used options are `-l -w -c -m` in this exact order.

## Standard ipnut

When no file is specified, content from Standard input is used. E.g. `echo "Hello" | wc`or `Get-Content data.txt | wc`.

## Notes

A word is a series of non-whitespace characters surrounded by whitespace characters on both sides. Whitespace characters are as follows.
| Name            | Byte | Symbol |
|-----------------|------|--------|
| space           | 0x20 | ' '    |
| form feed       | 0x0c | '\f'   |
| line feed       | 0x0a | '\n'   |
| carriage return | 0x0d | '\r'   |
| horizontal tab  | 0x09 | '\t'   |
| vertical tab    | 0x0b | '\v'   |

UTF-8 encoding is supported. --chars and --bytes return the same value only for ASCII files. We are using the following UTF-8 byte scheme:
- 1-byte sequence (0xxxxxxx): ASCII characters
- 2-byte sequence (110xxxxx 10xxxxxx)
- 3-byte sequence (1110xxxx 10xxxxxx 10xxxxxx)
- 4-byte sequence (11110xxx 10xxxxxx 10xxxxxx 10xxxxxx)


