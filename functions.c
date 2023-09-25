#include "functions.h"

int checkTheFile(int argc){
    if (argc > 2)
    {
        printf("Error. You inputed more then one file.\n");
        return 1;
    }
    if (argc < 2)
    {
        printf("Error. You did not specify a file to process in the command argument.\n");
        return 1;
    }
    return 2;
}

char* outputFileName(char *inputFilename)
{
    char *outputName=strcat(inputFilename, ".lexer");
    return outputName;
}

void lexer(FILE *inputFile, FILE *outputFile)
{
   // fprintf(outputFile, );
    char temp;
    char temp2;
    temp =fgetc(inputFile);
    while (temp!=EOF)
    {
        if (temp=='/')
        {
            if ((temp2=fgetc(inputFile))=='*')
            {
                fputc(temp, outputFile);
                fputc(temp2, outputFile);
                while((temp=fgetc(inputFile))!='*' && (temp2=fgetc(inputFile)) !='/'){
                    fputc(temp,outputFile);
                    fputc(temp2, outputFile);
                }
                fputc(temp, outputFile);
                fputc(temp2, outputFile);
                char *comment=" (comment)\n";
                fputs (comment, outputFile);
            }
            else
            {
                fputc(temp, outputFile);
                char *opperator=" (opperator)\n";
                fputs (opperator, outputFile);
            }
        }
    }
}

int lexerClassification(char *input)
{
    int type=0;
    return type;
    //if 
}