#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int checkTheFile(int argc);
char* outputFileName(char *inputFilename);
void lexer(FILE *inputFile, FILE *outputFile);

int lexerClassification(char *input);