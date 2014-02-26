#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef enum {
  false, true
} bool;

struct RPNElement {
  bool isNumericFlag;
  union {
      char ch[4];
      float f;
  };
};

void main() {

    static const float PI = 3.14159265359;
    static const float E = 2.71828182846;

    char input[] = " ";
    int i;
    char charBuffer[] = "";
    int charBufferLast = 0;
    
    struct RPNElement tmpStack[20], RPNStack[40];
    int tmpStackIndex = 0, RPNStackIndex = 0;

    bool flag;

    fgets(input, 255, stdin);

    // parse input from infix
    for (i = 0; i<(strlen(input)-1); i++) {
        charBuffer[charBufferLast] = input[i];
        switch (charBuffer[charBufferLast++]) {
            case 'P':
                break;
            case 'I':
                if (charBuffer[0] == 'P') {
                    strcpy(RPNStack[RPNStackIndex++],"PI");
                    charBufferLast = 0;
                } else {
                    //error
                }
                break;
            case 'E':
                strcpy(RPNStack[RPNStackIndex++],"E");
            charBufferLast = 0;
                    break;
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
            case '0':
                if (isdigit(input[i+1]) || input[i+1] == '.') {
                    //just keep in stack
                } else {
                    charBuffer[charBufferLast] = '\0';
                    strcpy(RPNStack[RPNStackIndex++],charBuffer);
                    charBufferLast = 0;
                }
                break;
            case '.':
                if (!isdigit(input[i+1])) {
                    //error
                }
                break;
            case '+':
                if (tmpStackIndex == 0) {
                    strcpy(RPNStack[RPNStackIndex++],"+");
                    charBufferLast = 0;
                } else {
                    flag = true;
                    do {
                        switch(tmpStack[tmpStackIndex][0])    {
                            case '+':
                            case '-':
                            case '*':
                            case '/':
                                flag = false;
                                strcpy(RPNStack[RPNStackIndex++],tmpStack[tmpStackIndex--]);
                                break;
                            case '(':
                                flag = true;
                                strcpy(RPNStack[RPNStackIndex++],"+");
                                charBufferLast = 0;
                        }
                    } while (!flag);
                }
                break;
            case '*':
                strcpy(RPNStack[RPNStackIndex++],"*");
                charBufferLast = 0;
                break;
            case '-':
                strcpy(RPNStack[RPNStackIndex++],"-");
                charBufferLast = 0;
                break;
            case '/':
                strcpy(RPNStack[RPNStackIndex++],"/");
                charBufferLast = 0;
                break;
            default:
                charBufferLast = 0;
                break;
        }
        //printf("\n");
    }
    printf("\n");
    for (i = 0; i < RPNStackIndex; i++) {
        printf("%s\n",RPNStack[i]);
    }
}



struct RPNElement formRPNElement(char charBuffer[], bool isNumber)
{
    struct RPNElement tmp;


    if (isNumber == true) {
       tmp.f = strtof(charBuffer, NULL);
    } else {
       strcpy(tmp.ch, charBuffer);
    }

    tmp.isNumericFlag = isNumber;
    return (tmp);
}