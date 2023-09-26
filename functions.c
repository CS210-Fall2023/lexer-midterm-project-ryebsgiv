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
    temp =fgetc(inputFile);
    char temp2=temp;
    while (temp!=EOF)
    {
        if (temp=='/')
        {
            isComment(inputFile, outputFile, temp, temp2);
        }
        else if (temp=='"')
        {
            isString(inputFile, outputFile, temp);
        }
        else if (temp=='\'')
        {
            isCharLiteral(inputFile,outputFile,temp);
        }
        else if (temp=='0'||temp=='1'||temp=='2'||temp=='3'||temp=='4'||temp=='5'||temp=='6'||temp=='7'||temp=='8'||temp=='9'){
            isnumber(inputFile,outputFile,temp,temp2);
        }
        else
        {
            fputc(temp,outputFile);
            char *unknown=" (unknown)\n";
            fputs (unknown, outputFile);
            
        }
        temp=fgetc(inputFile);
    }

}

void isComment(FILE *inputFile, FILE *outputFile, char temp, char temp2)
{
    temp2=fgetc(inputFile);
    if (temp2=='*')
    {
        while(temp!=EOF||temp2!=EOF){
            if (temp == '*' && temp2 == '/')
            {
                fputc(temp, outputFile);
                fputc(temp2, outputFile);
                char *comment=" (comment)\n";
                fputs (comment, outputFile);
                break;
            }
            else {
                fputc(temp, outputFile);
                temp=temp2;
                temp2=fgetc(inputFile);
            }
        }
    }
    else
    {
        fputc(temp, outputFile);
        char *opperator=" (opperator)\n";
        fputs (opperator, outputFile);
        return;
    }
}
void isString(FILE *inputFile, FILE *outputFile, char temp){
    fputc(temp, outputFile);
    // fputc(temp2, outputFile);
    temp=fgetc(inputFile);
    while (temp!='"'){
        fputc(temp, outputFile);
        temp=fgetc(inputFile);
    }
    fputc(temp, outputFile);
    char *string=" (string)\n";
    fputs (string, outputFile);
    return;
}
void isCharLiteral(FILE *inputFile, FILE *outputFile, char temp){
    fputc(temp, outputFile);
    temp=fgetc(inputFile);
    fputc(temp,outputFile);
    temp=fgetc(inputFile);
    fputc(temp,outputFile);
    char *charLiteral=" (character literal)\n";
    fputs (charLiteral, outputFile);
    return;
}
void isnumber(FILE *inputFile, FILE *outputFile, char temp, char temp2){
    fputc(temp, outputFile);
    temp2=fgetc(inputFile);
    char temp3=temp;
    char isDecimal='n';
    if (temp2!='.'&&temp2!='#'){
        ungetc(temp2, inputFile);
        char *numberLiteral=" (numeric literal)\n";
        fputs (numberLiteral, outputFile);
        return;
    }
    temp3=temp2;
    if (temp2=='.'&&(temp2=fgetc(inputFile))=='.')
    {
        fputc(temp, outputFile);        
        char *numberLiteral=" (numeric literal)\n";
        fputs (numberLiteral, outputFile);
        fputc(temp2, outputFile);
        fputc(temp2, outputFile);
        char *opperator=" (opperator)\n";
        fputs (opperator, outputFile);
        return;
    }
    else{
        fputc(temp3, outputFile);
        ungetc(temp2, inputFile);
    }

    while(temp!=EOF||temp2!=EOF)
    {
        temp=fgetc(inputFile);
        // fputc(temp, outputFile);
        if (temp=='.')
        {
            fputc(temp, outputFile);
            if (isDecimal=='y')
            {
                ungetc(temp2, inputFile);
                fputc(temp, outputFile);
                char *numberLiteral=" (numeric literal)\n";
                fputs (numberLiteral, outputFile);
            }
            isDecimal='y';
        }
        else if (temp=='#')
        {   
            temp2=fgetc(inputFile);
            if (temp2=='0'||temp2=='1'||temp2=='2'||temp2=='3'||temp2=='4'||temp2=='5'||temp2=='6'||temp2=='7'||temp2=='8'||temp2=='9')
            {
                ungetc(temp2, inputFile);
                // fputc(temp, outputFile);
            }

        }
        else{
            ungetc(temp, inputFile);
            break;
        }
    }
}
