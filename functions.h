/**
 * @file functions.h
 * @author Ben Givens
 * @brief header file for the functions that go with main.c
 * @date 2023-09-26
 */
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
void isOpperator(FILE *inputFile, FILE *outputFile, char temp, char temp2);
void isKeywordOrIdentifier(FILE *inputFile, FILE *outputFile, char temp, char temp2,char *keyword[]);
