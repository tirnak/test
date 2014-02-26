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

struct RPNElement formRPNElement(char charBuffer[], bool isNumber);

void main() {

    static const float PI = 3.14159265359;
    static const float E = 2.71828182846;

    char input[] = " ";
    int i;
    char charBuffer[15];
    char charBuffer2[15];
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
                    //strcpy(charBuffer2, (sprintf("%f", PI));
                    RPNStack[RPNStackIndex++] = formRPNElement( sprintf("%1.11f", PI)/*charBuffer2*/, true);
                    charBufferLast = 0;
                } else {
                    //error
                }
                break;
            case 'E':
                RPNStack[RPNStackIndex++] = formRPNElement( sprintf("%1.11f", E), true);
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
                    RPNStack[RPNStackIndex++] = formRPNElement(charBuffer, true);
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
                    RPNStack[RPNStackIndex++] = formRPNElement("+" , false);
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
                                RPNStack[RPNStackIndex++] = tmpStack[tmpStackIndex--];
                                break;
                            case '(':
                                flag = true;
                                RPNStack[RPNStackIndex++] = formRPNElement("+" , false);
                                charBufferLast = 0;
                        }
                    } while (!flag);
                }
                break;
            case '*':
                RPNStack[RPNStackIndex++] = formRPNElement("*" , false);
                charBufferLast = 0;
                break;
            case '-':
                RPNStack[RPNStackIndex++] = formRPNElement("-" , false);
                charBufferLast = 0;
                break;
            case '/':
                RPNStack[RPNStackIndex++] = formRPNElement("/" , false);
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
        if (RPNStack[i].isNumericFlag == true) {
            printf("%f\n",RPNStack[i].f);
        } else {
            printf("%s\n",RPNStack[i].ch);
        }
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