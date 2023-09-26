/**
 * @file main.c
 * @author Ben Givens
 * @brief A lexer which will scan through certain CCX programs and tokenize them.
 * @date 2023-09-26
 */
#include "functions.h"

int main(int argc, char *argv[])
{
    //Makes sure the user entered a valid inputfile.
    if (checkTheFile(argc)!=2){
        return 1;
    }
    //The input file will be in argv[1]
    char *nameOfFile=argv[1];

    //Open the input file
    FILE *inputFile;
    inputFile=fopen(nameOfFile, "r");
    
    //Open the output file
    FILE *outputFile;
    outputFile=fopen(outputFileName(nameOfFile), "w");
    
    //Check to see if they opened properly
    if (inputFile == NULL || outputFile == NULL) {
        perror("Error opening files");
        return 1;
    }

    //Run the lexer
    lexer(inputFile, outputFile);

    //Close the files
    fclose(inputFile);  
    fclose(outputFile);
}   