/*
    Erik Safford
    my-cat: cat a file(s)
    Spring 2020
*/
// Replicates: cat [file ...]

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    // File pointer to be used when opening file
    FILE *fp = NULL;    
    // Buffer to hold read string from file   
    char *line = NULL;  

    // Attempt to open and read the contents of given command line files
    for(int i = 1; i < argc; i++) {
        // Open file for reading
        if((fp = fopen(argv[i], "r")) == NULL) {
            fprintf(stderr, "my-cat: cannot open file '%s'\n", argv[i]);
            exit(1);
        }

        // Read contents of file into str buffer
        size_t len = 0, read;
        while((read = getline(&line, &len, fp) != -1)) {
            // Print file contents to stdout
            printf("%s",line);
        }
        // Close the file after done reading
        fclose(fp);
        // Free the line buffer
        free(line);
    }

    // Return 0 if cat is successful (will return success even if no files are given on command line)
    return(0);
}