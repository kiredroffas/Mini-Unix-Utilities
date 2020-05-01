/*
    Erik Safford
    my-uniq: remove consecutive duplicate lines from file(s) 
    Spring 2020
*/
// Replicates: uniq [file ...]

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFromCommandLine() {
    char line[4096];
    while(fgets(line, sizeof(line), stdin)) {
        printf("%s", line);
    }
}

void printWithoutDuplicateLines(char *file) {
    FILE *fp;
    char *line1 = NULL;  // Line that is being compared to
    char *line2 = NULL;  // Line that was most previously read in
    size_t len1 = 0;     // Lengths of strings read by getline
    size_t len2 = 0;
    int lineRead = 0;    // Flag for when getline reaches end of file
    
    // Attempt to open the given file
    if((fp = fopen(file, "r")) == NULL) {
        fprintf(stderr, "my-uniq: cannot open file '%s'\n", file);
        exit(1);
    }

    // Read the first line of the file
    while(getline(&line1, &len1, fp) != -1) {
        // Remove the newline if it exists
        if(line1[strlen(line1) - 1] == '\n') {
            line1[strlen(line1) - 1] = '\0';
        }
        // Continue reading each line of the file until the end is reached
        while((lineRead = getline(&line2, &len2, fp)) != -1) {
            // Remove the newline if it exists
            if(line2[strlen(line2) - 1] == '\n') {
                line2[strlen(line2) - 1] = '\0';
            }
            // Compare the two lines, printing only if they are not the same
            if(strcmp(line1, line2) != 0) {
                printf("%s\n", line1);
                // Copy line2 into line1 and reset strings
                free(line1);
                line1 = NULL;
                line1 = strdup(line2);
                free(line2);
                line2 = NULL;
                len1 = len2;
                len2 = 0;
            }
        }
        // If the last line of the file has been read, free the last compare string
        if(lineRead == -1) {
            free(line2);
            line2 = NULL;
        }
    }
    // Print the final line from the file in line1 if it was not already printed
    if (line1 != NULL) {
        printf("%s\n", line1);
        // free remaining string
        free(line1);
        line1 = NULL;
    }
    // Close the opened file
    if (fclose(fp) != 0) {
        fprintf(stderr, "my-uniq: cannot close file.\n");
        exit(1);
    }
}

int main(int argc, char **argv) {
    // If no file argument is given, read from stdin and print to stdout until CTRL+C received
    if(argc == 1) {
        readFromCommandLine();
    }
    // Else attempt to open and read the contents of given command line files
    else {
        for(int i = 1; i < argc; i++) {
            // Print each given file without duplicate lines
            printWithoutDuplicateLines(argv[i]);
        }
    }
    // Return 0 if uniq completes successfully
    return(0);
}