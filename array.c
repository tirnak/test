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

int parseIntoRPN(char input[], struct RPNElement *RPNStackPointer);
struct RPNElement formRPNElementNum(float num);
struct RPNElement formRPNElementOp(char charBuffer[]);

int main() {

    static const float PI = 3.14159265359;
    static const float E = 2.71828182846;

    char input[50];
    int i;
    char charBuffer[15];
    int charBufferLast = 0;
    
    struct RPNElement tmpStack[20], RPNStack[40];
    int tmpStackIndex = 0, RPNStackIndex = 0;

    bool flag;

    //fgets(input, 50, stdin);
    scanf("%s", input);

    // parse input from infix
    RPNStackIndex = parseIntoRPN(input, &RPNStack);

    printf("\n");
    for (i = 1; i < RPNStackIndex + 1; i++) {
        if (RPNStack[i].isNumericFlag == true) {
            printf("%f\n",RPNStack[i].f);
        } else {
            printf("%s\n",RPNStack[i].ch);
        }
    }
}

// returns RPNStackIndex
int parseIntoRPN(char input[], struct RPNElement *RPNStack) {
    int i;
    char charBuffer[15];
    int charBufferLast = 0;

    struct RPNElement tmpStack[20];
    int tmpStackIndex = 0, RPNStackIndex = 0;

    bool flag;

    for (i = 0; i < strlen(input); i++) {
        charBuffer[charBufferLast] = input[i];
        switch (charBuffer[charBufferLast]) {
            case 'e':
                if (input[i+1] != 'x' || input[i+2] != 'p') {
                    //error
                }
                tmpStack[++tmpStackIndex] = formRPNElementOp("exp");
                i = i+2;
                break;
            case 's':
                if (input[i+1] != 'i' || input[i+2] != 'n') {
                    //error
                }
                tmpStack[++tmpStackIndex] = formRPNElementOp("sin");
                i = i+2;
                break;
            case 'c':
                if (input[i+1] != 'o' || input[i+2] != 's') {
                    //error
                }
                tmpStack[++tmpStackIndex] = formRPNElementOp("cos");
                i = i+2;
                break;
            case 'P':
                if (input[i+1] != 'I') {
                    //error
                }
                RPNStack[++RPNStackIndex] = formRPNElementNum(PI);
                i++;
                break;
            case 'E':
                RPNStack[++RPNStackIndex] = formRPNElementNum(E);
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
                    charBufferLast++;
                } else {
                    charBuffer[++charBufferLast] = '\0';
                    RPNStack[++RPNStackIndex] = formRPNElementNum(atof(charBuffer));
                    charBufferLast = 0;
                }
                break;
            case '.':
                if (!isdigit(input[i+1])) {
                    //error
                }
                charBufferLast++;
                break;
            case '+':
                do {
                    flag = false;
                    if (tmpStackIndex == 0 || tmpStack[tmpStackIndex].ch[0] == '(' ) {
                        tmpStack[++tmpStackIndex] = formRPNElementOp("+");
                        charBufferLast = 0;
                        flag = true;
                    } else {
                        switch(tmpStack[tmpStackIndex].ch[0])    {
                            case '+':
                            case '-':
                            case '*':
                            case '/':
                                RPNStack[++RPNStackIndex] = tmpStack[tmpStackIndex--];
                                break;
                        }
                    } /* endif */
                } while (!flag);
                break;
            case '-':
                do {
                    flag = false;
                    if (tmpStackIndex == 0 || tmpStack[tmpStackIndex].ch[0] == '(' ) {
                        tmpStack[++tmpStackIndex] = formRPNElementOp("-");
                        charBufferLast = 0;
                        flag = true;
                    } else {
                        switch(tmpStack[tmpStackIndex].ch[0])    {
                            case '+':
                            case '-':
                            case '*':
                            case '/':
                                RPNStack[++RPNStackIndex] = tmpStack[tmpStackIndex--];
                                break;
                        }
                    } /* endif */
                } while (!flag);
                break;
            case '*':
                while (tmpStack[tmpStackIndex].ch[0] == '*' || tmpStack[tmpStackIndex].ch[0] == '/') {
                    RPNStack[++RPNStackIndex] = tmpStack[tmpStackIndex--];
                }
                tmpStack[++tmpStackIndex] = formRPNElementOp("*");
                break;
            case '/':
                while (tmpStack[tmpStackIndex].ch[0] == '*' || tmpStack[tmpStackIndex].ch[0] == '/') {
                    RPNStack[++RPNStackIndex] = tmpStack[tmpStackIndex--];
                }
                tmpStack[++tmpStackIndex] = formRPNElementOp("/");
                break;
            case '(':
                tmpStack[++tmpStackIndex] = formRPNElementOp("(");
                break;
            case ')':
                while (tmpStack[tmpStackIndex].ch[0] != '(' || tmpStackIndex == 0) {
                    RPNStack[++RPNStackIndex] = tmpStack[tmpStackIndex--];
                }
                if (tmpStack[tmpStackIndex].ch[0] == '(') {
                    tmpStackIndex--;
                }
                if (tmpStackIndex == 0) {
                    //error
                }
                if (strcmp(tmpStack[tmpStackIndex].ch,"sin") == 0 ||
                    strcmp(tmpStack[tmpStackIndex].ch,"cos") == 0 ||
                    strcmp(tmpStack[tmpStackIndex].ch,"exp") == 0 ) {

                    RPNStack[++RPNStackIndex] = tmpStack[tmpStackIndex--];
                }
                break;
            case ' ':
                break;
            default:
                //error
                break;
        }
    }
    while (tmpStackIndex != 0) {
        RPNStack[++RPNStackIndex] = tmpStack[tmpStackIndex--];
    }

    return RPNStackIndex;

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
