#include "functions.h"

int main(int argc, char *argv[])
{
    if (checkTheFile(argc)!=2){
        return 1;
    }

    char *nameOfFile=argv[1];

    FILE *inputFile;
    inputFile=fopen(nameOfFile, "r");

    FILE *outputFile;
    outputFile=fopen(outputFileName(nameOfFile), "w");

    if (inputFile == NULL || outputFile == NULL) {
        perror("Error opening files");
        return 1;
    }

    lexer(inputFile, outputFile);
    fclose(inputFile);  
    fclose(outputFile);
}   