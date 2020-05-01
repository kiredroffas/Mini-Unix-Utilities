/*
    Erik Safford
    my-sed: search and replace a given search term from file(s)
    Spring 2020
*/
// Replicates: sed 's/dog/cat/' [file ...]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Search a given line for a matching searchTerm, and print the line to stdout replacing searchTerm with replaceTerm if first instance found
// Returns 0 if no matching term is found and line is not printed, returns 1 if matching search term is found, replaced, and printed
int searchAndReplace(char *line, char *searchTerm, char *replaceTerm) {
    // Get the length of the searchTerm
    int lengthSearchTerm = strlen(searchTerm);
    // Get the length of the line read in from the file
    int lengthLine = strlen(line);

    int index = 0;                   // The current index of the line being searched for searchTerm
    int offset = 0;                  // The current offset of the line being searched for searchTerm
    char matchStr[lengthSearchTerm]; // The current string from the line being checked to match searchTerm
    int matchFound = 0;              // Flag to signify that a matching searchTerm has been found on a line
    int matchIndex = 0;              // The index of the line where the matching term has been found

    // While the current index + the length of the searchTerm is less the the total length of the line
    while(index + lengthSearchTerm <= lengthLine && offset < lengthSearchTerm) {
        // Read in sets of characters from the line into matchStr buffer (to compare to searchTerm)
        for(int i = 0; i < lengthSearchTerm; i++) {
            // Add the sets of characters to matchStr buffer
            matchStr[offset] = line[index + offset];
            offset++;
        }
        matchStr[offset] = '\0';

        // Check to see if searchTerm matches matchStr, if it matches record the matchIndex, set matchFound flag, and break
        int result;
        if((result = strncmp(searchTerm, matchStr, lengthSearchTerm)) == 0) {
            matchIndex = index;
            matchFound = 1;
            break;
        }
        // Increment index and reset offset after each matchStr is checked for match
        else {
            index++;
            offset = 0;
        }
    }

    // If a matching searchTerm was found in the given line, print the line with the searchTerm replaced with replaceTerm
    if(matchFound == 1) {
        for(int i = 0; i < lengthLine; i++) {
            if(i != matchIndex) {
                printf("%c", line[i]);
            }
            else {
                printf("%s", replaceTerm);
                i += lengthSearchTerm - 1;
            }
        }
        return(1);
    }
    // Else if a matching searchTerm wasn't found on the given line, dont print the line
    else {
        return(0);
    }
}

void readFromCommandLine(char *searchTerm, char *replaceTerm) {
    char line[4096];
    while(fgets(line, sizeof(line), stdin)) {
        // If no matching replace term found, print the line as is
        if(searchAndReplace(line, searchTerm, replaceTerm) == 0) {
            printf("%s", line);
        }
    }
}

void parseFile(char *file, char *searchTerm, char *replaceTerm) {
    FILE *fp = NULL;
    // Open file for reading
    if((fp = fopen(file, "r")) == NULL) {
        fprintf(stderr, "my-sed: cannot open file '%s'\n", file);
        exit(1);
    }

    char *line = NULL;
    size_t len = 0, read;

    // Read lines from opened file
    while((read = getline(&line, &len, fp) != -1)) {
        // Search for searchTerm in the given line, replace with replaceTerm and print only if first occurance of matching searchTerm is found
        if(searchAndReplace(line, searchTerm, replaceTerm) == 0) {
            // Otherwise print the line as is
            printf("%s", line);
        }
    }
    free(line);
    fclose(fp);
}

int main(int argc, char **argv) {
    // If proper amount of command line args are not present, error and exit
    if(argc < 3) {
        fprintf(stderr, "my-sed: find_term replace_term [file ...]\n");
        exit(1);
    }

    // Get the string to be replaced from command line arg
    char searchTerm[4096];
    strncpy(searchTerm, argv[1], sizeof(searchTerm));
    searchTerm[4096] = '\0';

    // Get the string to replace searchTerm from command line arg
    char replaceTerm[4096];
    strncpy(replaceTerm, argv[2], sizeof(replaceTerm));
    replaceTerm[4096] = '\0';

    // If no input file(s) is specified, read from stdin until CTRL+C received
    if(argc == 3) {
        readFromCommandLine(searchTerm, replaceTerm);
    }
    // Else if input file(s) are specified
    else if(argc > 3) {
        // Attempt to search and replace for each line of the specified file(s)
        for(int i = 3; i < argc; i++) {
            parseFile(argv[i], searchTerm, replaceTerm);
        }
    }

    // Return 0 if my-sed completes successfully
    return(0);
}