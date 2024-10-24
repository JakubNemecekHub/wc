echo "Hello, World! Řeka." > test.txt
wc -l test.txt  # Number of lines
wc -w test.txt  # Number of words
wc -c test.txt  # Number of bytes
wc -m test.txt  # Number of characters

wc test.txt # Same as -l -w -c
wc -l -w -c test.txt
# The order of arguments doesn't matter.
# The final outpu is always as: -l -w -c.
wc -c -l -w test.txt

wc -l -w test.txt
wc -lw test.txt  # Arguments can be concatenated
wc -wl test.txt  # Again the order doesn't matter.

A word is a series of non-whitespace characters surrounded by whitespace characters on both sides.


Normal input = file name/path (test with path) -> create an ifstream for each command
             = multiple names/paths -> create an ifstream for each file and each commant | NOT YET IMPLEMENTED
Piped input = uses cin.
              Somewhere along the way a single new line byte is added at the end of the input. This is expected, do not remove this last byte.


