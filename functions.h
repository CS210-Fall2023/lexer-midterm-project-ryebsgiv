#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int checkTheFile(int argc);
char* outputFileName(char *inputFilename);
void lexer(FILE *inputFile, FILE *outputFile);
void isComment(FILE *inputFile, FILE *outputFile, char temp, char temp2);
void isString(FILE *inputFile, FILE *outputFile, char temp);
void isCharLiteral(FILE *inputFile, FILE *outputFile, char temp);
void isnumber(FILE *inputFile, FILE *outputFile, char temp, char temp2);
