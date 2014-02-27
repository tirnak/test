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

struct RPNElement formRPNElementNum(float num);
struct RPNElement formRPNElementOp(char charBuffer[]);

void main() {

    static const float PI = 3.14159265359;
    static const float E = 2.71828182846;

    char input[] = " ";
    int i;
    char charBuffer[15];
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
                    RPNStack[RPNStackIndex++] = formRPNElementNum(PI);
                    charBufferLast = 0;
                } else {
                    //error
                }
                break;
            case 'E':
                RPNStack[RPNStackIndex++] = formRPNElementNum(E);
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
                    RPNStack[RPNStackIndex++] = formRPNElementNum(atof(charBuffer));
                    charBufferLast = 0;
                }
                break;
            case '.':
                if (!isdigit(input[i+1])) {
                    //error
                }
                break;
            case '+':
                do {
                    flag = false;
                    if (tmpStackIndex == 0 || tmpStack[tmpStackIndex].ch[0] == '(' ) {
                        tmpStack[tmpStackIndex++] = formRPNElementOp("+");
                        charBufferLast = 0;
                        flag = true;
                    } else {
                        switch(tmpStack[tmpStackIndex].ch[0])    {
                            case '+':
                            case '-':
                            case '*':
                            case '/':
                                RPNStack[RPNStackIndex++] = tmpStack[tmpStackIndex--];
                                break;
                        }
                    } /* endif */
                } while (!flag);
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



struct RPNElement formRPNElementOp(char charBuffer[])
{
    struct RPNElement tmp;

    strcpy(tmp.ch, charBuffer);
    tmp.isNumericFlag = false;

    return (tmp);
}


struct RPNElement formRPNElementNum(float num)
{
    struct RPNElement tmp;

    tmp.f = num;
    tmp.isNumericFlag = true;

    return (tmp);
}