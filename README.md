# Mini-Unix-Utilities
* This system includes a set of simpler versions of Linux utilities programmed in C to emulate the cat, sed, and uniq system calls.
## my-cat
* Run with: './my-cat filename ... ...'
* My-cat will read a specified file(s) and print its contents to stdout. It does this by utilizing the fopen(), getline(), and fclose() functions. If fopen() fails to open a file, an error message is printed to stderr, and the program exits with a return of 1. getline() allows for my-cat to read lines of unspecified length from a file. my-cat will return 0 if no filename/filepath is specified, or if the program completes successfully.
## my-sed
* Run with: './my-sed stringToSearchFor stringToReplaceWith filename ... ...'
* My-sed finds and replaces a given string with another given string, within specified input file(s). It finds only the first occurance of the string in a line, and substitutes it with another, before printing the output to stdout. Instances following the first instance remain as is, and are not printed. If an empty string ("") is specified as the replace term, then instead of replacing, the search term is deleted (without substituting a space). The matching is case sensitive, so 'foo' will not match with 'Foo'. The find and replace terms must not contain any escape characters like /n or /0. The lines of the file(s) can be arbitrarily long (due to getline() implementation.) If my-sed is passed with no command line arguments, or if any of the mandatory arguments are missing, an error message is printed to stderr, and program exits with status code 1. If my-sed encounters a file that it can't open, it again prints an error to stderr, and exits with status code 1. If no input file is specified, my-sed works but instead of reading from a file, my-sed reads from stdin. Input file(s) are not modified. Functions utilized include: fopen(), getline(), fclose(), strlen(), strncmp(), strncpy(), and fgets(). My-sed will return 0 if the program completes successfully.
## my-uniq
* Run with: './my-uniq filename ... ...'
* My-uniq detects adjacent duplicate lines in input file(s), removes them, and prints to stdout. My-uniq accepts an arbitrary number of input files, and prints the output to stdout. However it only detects duplicates within each file, i.e. if the first line in the second file is the same as the last line in the first file, it won't be removed. If my-uniq encounters a file that it can't open, an error message is printed to stderr, and the program exits with status code 1. Input files can be really large, and each line can be arbitrarily long. Input file(s) are not modified. If no files are specified, my-uniq will read from stdin. Funtions utilized include: fopen(), getline(), fclose(), strcmp(), strdup(), and fgets(). My-uniq will return 0 if the program completes successfully.
# Screenshots
## Test Files
### a.txt
![Alt text](/screenshots/a.png?raw=true "a.txt")
### b.txt
![Alt text](/screenshots/b.png?raw=true "b.txt")
### c.txt
![Alt text](/screenshots/c.png?raw=true "c.txt")
## my-cat
![Alt text](/screenshots/cat.png?raw=true "cat")
## my-sed
![Alt text](/screenshots/sed.png?raw=true "sed")
## my-uniq
![Alt text](/screenshots/uniq.png?raw=true "uniq")
