#include "functions.h"

/**
 * @brief Checks the file specified in the command argument, and ensures they entered the right number of arguments
 * 
 * @param argc the arguments the user entered in the command line
 * @return int 
 */
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

/**
 * @brief Returns the file name with .lexer attatched to it
 * 
 * @param inputFilename the inputfile
 * @return char* 
 */
char* outputFileName(char *inputFilename)
{
    char *outputName=strcat(inputFilename, ".lexer");
    return outputName;
}
/**
 * @brief The function which determines which type of token the program is dealing with and calls the appropriate functions,
 * 
 * @param inputFile the inputfile
 * @param outputFile the outputfile
 */
void lexer(FILE *inputFile, FILE *outputFile)
{
    //list of all possible keywords
    char *keyword[]= {"accessor", "and", "array", "begin", "bool", "case", "character", "constant", "else", "elsif", "end", "exit", "function",
                    "if", "in", "integer", "interface", "is", "loop", "module", "mutator", "natural", "null", "of", "or", "other", "out",
                    "positive", "procedure", "range", "return", "struct", "subtype", "then", "type", "when", "while"};
    //Temp value used to move throughout the file
    char temp;
    //Set the value equal to the first character in the file
    temp =fgetc(inputFile);
    //initialize a second temp value for use in functions which require muiltiple values
    char temp2=temp;
    //main lexer loop
    while (temp!=EOF)
    {
        //if comment
        if (temp=='/')
        {
            isComment(inputFile, outputFile, temp, temp2);
        }

        //if string
        else if (temp=='"')
        {
            isString(inputFile, outputFile, temp);
        }

        //if character literal
        else if (temp=='\'')
        {
            isCharLiteral(inputFile,outputFile,temp);
        }

        //if numeric literal
        else if (temp >= '0' && temp <= '9')
        {
            isnumber(inputFile,outputFile,temp,temp2);
        }

        //if operator
        else if (temp=='.' || temp=='<' || temp=='>' || temp=='(' || temp==')' 
        || temp=='+' || temp=='-' || temp=='*' ||temp=='|' ||temp=='&'
        ||temp==';'||temp==','||temp==':'||temp=='['||temp==']'||temp=='=' || temp=='.'||temp=='<'||temp=='>'||temp=='!')
        {
            isOperator(inputFile, outputFile, temp, temp2);
        }

        //temp is space or newline or tab
        else if (temp==' ' || temp=='\n'||temp=='\t')
        {
            temp=fgetc(inputFile);
            continue;
        }
        //temp is an identifier or a keyword
        else if ((temp >= 'a' && temp <= 'z') || (temp >= 'A' && temp <= 'Z'))
        {
            isKeywordOrIdentifier(inputFile, outputFile, temp, temp2, keyword); 
        }

        //if unknown
        else            
        {
            fputc(temp,outputFile);
            char *unknown=" (unknown)\n";
            fputs (unknown, outputFile);
            
        }
        //increment the file by one
        temp=fgetc(inputFile);
    }

}
/**
 * @brief if the token is a comment this function displays the token entirely with the descriptor afterwards
 * 
 * @param inputFile the input file
 * @param outputFile the output file
 * @param temp temporary value used for navigating the file
 * @param temp2 secondary value also used for navigating the file
 */
void isComment(FILE *inputFile, FILE *outputFile, char temp, char temp2)
{
    //set temp2 equal to the second value in the file
    temp2=fgetc(inputFile);
    //if it's equal to * then it is a comment and not an operator
    if (temp2=='*')
    {

        //loop to copy contents of comment to output file
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
    //if it is not a comment but an operator
    else
    {
        fputc(temp, outputFile);
        char *operator=" (operator)\n";
        fputs (operator, outputFile);
        return;
    }
}
/**
 * @brief determines if it is a string and tokenizes it
 * 
 * @param inputFile the inputfile
 * @param outputFile the output file
 * @param temp the temporary value used to navigate the file
 */
void isString(FILE *inputFile, FILE *outputFile, char temp)
{
    //put quotation mark into file and read next character
    fputc(temp, outputFile);
    temp=fgetc(inputFile);
    //Loop through rest of the string
    while (temp!='"'){
        fputc(temp, outputFile);
        temp=fgetc(inputFile);
    }
    //Put last quotation mark into file and then the string banner
    fputc(temp, outputFile);
    char *string=" (string)\n";
    fputs (string, outputFile);
    return;
}
/**
 * @brief Determins if it is a char literal and tokenizes it
 * 
 * @param inputFile the input file
 * @param outputFile the output file
 * @param temp the temporary value used to navigate the file
 */
void isCharLiteral(FILE *inputFile, FILE *outputFile, char temp)
{
    //Load the first ' to the output file and iterate the posistion
    fputc(temp, outputFile);
    temp=fgetc(inputFile);

    //Load the char to the output file and iterate the posistion
    fputc(temp,outputFile);
    temp=fgetc(inputFile);

    //load the second ' to the output file and the token label
    fputc(temp,outputFile);
    char *charLiteral=" (character literal)\n";
    fputs (charLiteral, outputFile);
    return;
}
/**
 * @brief Checks if the input is a numeric literal and tokenizes it if it is
 * 
 * @param inputFile the inputFile
 * @param outputFile the outputFile
 * @param temp the temp value used to navigate the file
 * @param temp2 a backup temp value used to navigate the file
 */
void isnumber(FILE *inputFile, FILE *outputFile, char temp, char temp2){
    fputc(temp, outputFile);
    temp2=fgetc(inputFile);

    //If there is more numbers
    while (temp2<= '9' && temp2>= '0')
    {
        fputc(temp2, outputFile);
        temp2=fgetc(inputFile);
    }

    //if there isnt a decimal or # then exit then print the number literal banner and return 
    if (temp2!='.'&&temp2!='#')
    {
        ungetc(temp2, inputFile);
        char *numberLiteral=" (numeric literal)\n";
        fputs (numberLiteral, outputFile);
        return;
    }
    //If there is a period following the numbers, but it is an opperator not a decimal
    if (temp2=='.'&&(temp=fgetc(inputFile))=='.')
    {      
        //print numberLiteral banner
        char *numberLiteral=" (numeric literal)\n";
        fputs (numberLiteral, outputFile);

        //print two periods to file and then the opperator banner
        fputc(temp, outputFile);
        fputc(temp, outputFile);
        char *operator=" (operator)\n";
        fputs (operator, outputFile);
        return;
    }
    //If decimal
    else if (temp2=='.'&&(temp<= '9' && temp>= '0'))
    {
        //Put period into file
        fputc(temp2, outputFile);
        //cycle through remaining intergers behind the decimal
        while (temp<= '9' && temp>= '0')
        {
            fputc(temp, outputFile);
            temp=fgetc(inputFile);
        }
        ungetc(temp, inputFile);
        char *numberLiteral=" (numeric literal)\n";
        fputs (numberLiteral, outputFile);
        return;
    }
    //else the number is followed by #
    else{
        fputc(temp2, outputFile);
        temp=fgetc(inputFile);
        while ((temp<= '9' && temp>= '0')||temp=='#')
        {
            fputc(temp, outputFile);
            temp=fgetc(inputFile);
        }
        ungetc(temp, inputFile);
        char *numberLiteral=" (numeric literal)\n";
        fputs (numberLiteral, outputFile);
        return;
    }
}

/**
 * @brief Checks the input is an operator and prints it
 * 
 * @param inputFile 
 * @param outputFile 
 * @param temp 
 * @param temp2 
 */
void isOperator(FILE *inputFile, FILE *outputFile, char temp, char temp2){
    //Check if it one of the operators that has two parts
   if (temp=='<')
   {
        temp2=fgetc(inputFile);
        if (temp2=='>'|| temp2=='=' || temp2=='<')
        {
            fputc(temp, outputFile);
            fputc(temp2, outputFile);
            char *operator=" (operator)\n";
            fputs (operator, outputFile);
            return;
        }
        else{
            ungetc(temp2, inputFile);
        }
   }
   else if (temp=='>')
   {
        temp2=fgetc(inputFile);
        if (temp2=='>'|| temp2=='=')
        {
            fputc(temp, outputFile);
            fputc(temp2, outputFile);
            char *operator=" (operator)\n";
            fputs (operator, outputFile);
            return;
        }
        else{
            ungetc(temp2, inputFile);
        }
   }
   else if (temp==':')
   {
        temp2=fgetc(inputFile);
        if (temp2=='=')
        {
            fputc(temp, outputFile);
            fputc(temp2, outputFile);
            char *operator=" (operator)\n";
            fputs (operator, outputFile);
            return;
        }
        else{
            ungetc(temp2, inputFile);
        }
   }
    else if (temp=='.')
   {
        temp2=fgetc(inputFile);
        if (temp2=='.')
        {
            fputc(temp, outputFile);
            fputc(temp2, outputFile);
            char *operator=" (operator)\n";
            fputs (operator, outputFile);
            return;
        }
        else{
            ungetc(temp2, inputFile);
        }
   }
   else if (temp=='*')
   {
        temp2=fgetc(inputFile);
        if (temp2=='*')
        {
            fputc(temp, outputFile);
            fputc(temp2, outputFile);
            char *operator=" (operator)\n";
            fputs (operator, outputFile);
            return;
        }
        else{
            ungetc(temp2, inputFile);
        }
   }    
   else if (temp=='!')
   {
        temp2=fgetc(inputFile);
        if (temp2=='=')
        {
            fputc(temp, outputFile);
            fputc(temp2, outputFile);
            char *operator=" (operator)\n";
            fputs (operator, outputFile);
            return;
        }
        else{
            ungetc(temp2, inputFile);
        }
   }    
   else if (temp=='=')
   {
        temp2=fgetc(inputFile);
        if (temp2=='>')
        {
            fputc(temp, outputFile);
            fputc(temp2, outputFile);
            char *operator=" (operator)\n";
            fputs (operator, outputFile);
            return;
        }
        else{
            ungetc(temp2, inputFile);
        }
   }
   //otherwise just print the opperator and the banner
    fputc(temp, outputFile);
    char *operator=" (operator)\n";
    fputs (operator, outputFile);
    return;
}

/**
 * @brief This function determines if the information is a keyword or a identifier by running the input through the list of all the keywords
 * 
 * @param inputFile the input file
 * @param outputFile the output file
 * @param temp temp value used for moving through the file
 * @param temp2 secondary temp value used for moving through the file
 * @param keyword array of all the possible key words
 */
void isKeywordOrIdentifier(FILE *inputFile, FILE *outputFile, char temp, char temp2, char *keyword[]){
    //total number of possible keywords
    int numPossible=37;
    //total possible length of input
    char tokenHolder[256];
    //counter
    int numberToken=0;

    //Loop that stores temp to array as long as it fits within the requirements
    while ((temp != ' ' && temp != EOF && temp!= '\n' )&&(((temp >= 'a' && temp <= 'z') || (temp >= 'A' && temp <= 'Z')||(temp >= '0' && temp <= '9')||(temp =='_'))))
    {
        tokenHolder[numberToken]=temp;
        numberToken++;
        temp=fgetc(inputFile);
    }
    //check to make sure the loop didn't take one too many values
    if (temp!=((temp >= 'a' && temp <= 'z') || (temp >= 'A' && temp <= 'Z')||(temp >= '0' && temp <= '9')||(temp =='_')))
    {
        ungetc(temp, inputFile);
    }
    
    //Put a null terminator at the end of the string. This is essential for comparing the strings and the keywords
    tokenHolder[numberToken]='\0';
    
    //compare the string to all of the keywords if it matches then print the word with the keyword label
    //else it is an identifier
    for (int i=0; i<numPossible; i++){
        if (strcmp(tokenHolder, keyword[i])==0){
            fputs (tokenHolder, outputFile);
            char *keywordLabel=" (keyword)\n";
            fputs (keywordLabel, outputFile);
            return;
        }
    }

    fputs (tokenHolder, outputFile);
    char *indentifierLabel=" (identifier)\n";
    fputs (indentifierLabel, outputFile);
    return;
}