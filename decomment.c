/*decomment.c
Final Project: Decomment Program
DONE BY: 
    MICHAEL ZEWDU ATR/9935/10
    YOPHTHAHE AMARE ATR/2890/10
    HANNA GIRMA ATR/3076/10
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdint.h>
#include<stddef.h>
#define SPACE 32
#define NEWLINE 10
#define SINGLEQUOTE 39
#define DOUBLEQUOTE 34
#define FORWARDSLASH 47
#define ASTERISX 42
int forwardSlash();
int doubleQuotes();
int singleQuotes();
void cacheSpaceChar();
void putFromSpaceCache();
int memoryHolderCtr=0; //index counter to access the array elements
int cacheHolder2 [] = {}; //Array to hold space characters
int lineNo=1; //keeps track of lines 


int main(void){  
    int character;  
    for(character=getchar();character!=EOF;character=getchar()){
    //for(c=getchar();;c=getchar()){
        switch(character){
            case FORWARDSLASH:
                forwardSlash(character);
                break;
            case DOUBLEQUOTE:
                doubleQuotes(character);
                break;
            case SINGLEQUOTE:
                singleQuotes(character);
                break;
            case EOF:
                return 0;

            default:
                if(character==NEWLINE){
                    lineNo++;
                }
                putchar(character);
                break;
        }
    }
}

/*forwardSlash function is executed if a forward slash that is not
 inside quotes is encountered if a comment is started and not properly
 closed it will throw an error otherwise it will disregard everything
 and give no output to stdout.*/
int forwardSlash(int cac){
    int afterC;
    int errorLineNo;
    afterC=getchar();
    if(afterC==ASTERISX){
        errorLineNo=lineNo;
        for(afterC=getchar();afterC!=EOF;afterC=getchar()){
            if(afterC==NEWLINE){
                cacheSpaceChar(NEWLINE);
                lineNo++;
                continue;
            }
            else if(afterC==ASTERISX){
                if(getchar()==FORWARDSLASH){
                    putchar(SPACE);
                    putFromSpaceCache();
                    return 0;
                }
            }

            else{
                continue;
            }

        }
        if(afterC==EOF){
                putchar(cac);
                putFromSpaceCache();
                printf("Error: line %d: unterminated comment\n",errorLineNo);
                return EXIT_FAILURE; 
            }
    }
    else{
        putchar(cac);
        //putFromCache();
        putchar(afterC);
        return 0;
    }
}

/*doubleQuotes function is executed if a double quote that is not
 inside a comment is encountered in the character input stream.
 It accepts a double quote to output to the stdout and returns an
 error if an opened double quote is not closed by a closing double 
 quote otherwise it returns 0. */
int doubleQuotes(int dbquotes){
    putchar(dbquotes);
    int errorLineNo;
    int string = getchar();
    for(string;string!=EOF;string=getchar()){    
        putchar(string);
        if(string==DOUBLEQUOTE){
            return 0;
        }
        if(string==NEWLINE){
            lineNo++;
        }
    }
}

/*Similar to the doublequotes function except it does the job for
 single quotes*/
int singleQuotes(int sgquotes){
    putchar(sgquotes);
    int string=getchar();
    for(string;string!=EOF;string=getchar()){
        putchar(string);
        if(string==SINGLEQUOTE){
            return 0;
        }  
        if(string==NEWLINE){
            lineNo++;
        }  
    }
}

/*This function stores new lines from comments in the character stream*/
void cacheSpaceChar(int memory2){
    cacheHolder2[memoryHolderCtr]=memory2;
    memoryHolderCtr++;
}

/*This function returns stored newlines to be converted to space characters*/
void putFromSpaceCache(){
    for(memoryHolderCtr; memoryHolderCtr >= 0; memoryHolderCtr-- ){
        putchar(cacheHolder2[memoryHolderCtr-1]);
    }
    memoryHolderCtr=0;
}


