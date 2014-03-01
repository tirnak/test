#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

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

static const float PI = 3.14159265359;
static const float E = 2.71828182846;

int parseIntoRPN(char input[], struct RPNElement *RPNStack);
struct RPNElement formRPNElementNum(float num);
struct RPNElement formRPNElementOp(char charBuffer[]);
float calculate(struct RPNElement RPNStack[], int RPNStackIndex);

int main() {

    char input[50];
    
    struct RPNElement RPNStack[40];
    int RPNStackIndex = 0;

    float result;

    fgets(input, 50, stdin);

    // parse input from infix to reverse polish notation
    RPNStackIndex = parseIntoRPN(input, RPNStack);

    // calculate RPNed expression
    result = calculate(RPNStack, RPNStackIndex);

    printf("\n%f\n", result);
    return 0;
}

// returns RPNStackIndex
int parseIntoRPN(char input[], struct RPNElement *RPNStack) {
    int i;
    char charBuffer[15];
    int charBufferLast = 0;

    struct RPNElement tmpStack[20];
    int tmpStackIndex = 0, RPNStackIndex = 0;

    bool flag;

    for (i = 0; i < strlen(input)-1; i++) {
        charBuffer[charBufferLast] = input[i];
        switch (charBuffer[charBufferLast]) {
            case 'e':
                if (input[i+1] != 'x' || input[i+2] != 'p') {
                    //error
                    charBuffer[++charBufferLast] = input[++i];
                    charBuffer[++charBufferLast] = input[++i];
                    charBuffer[++charBufferLast] = '\0';
                    fprintf(stderr, "Error: invalid token: '%s'. \n", RPNStack[i].ch);
                    exit(EXIT_FAILURE);
                }
                tmpStack[++tmpStackIndex] = formRPNElementOp("exp");
                i = i+2;
                break;
            case 's':
                if (input[i+1] != 'i' || input[i+2] != 'n') {
                    //error
                    charBuffer[++charBufferLast] = input[++i];
                    charBuffer[++charBufferLast] = input[++i];
                    charBuffer[++charBufferLast] = '\0';
                    fprintf(stderr, "Error: invalid token: '%s'. \n", RPNStack[i].ch);
                    exit(EXIT_FAILURE);
                }
                tmpStack[++tmpStackIndex] = formRPNElementOp("sin");
                i = i+2;
                break;
            case 'c':
                if (input[i+1] != 'o' || input[i+2] != 's') {
                    //error
                    charBuffer[++charBufferLast] = input[++i];
                    charBuffer[++charBufferLast] = input[++i];
                    charBuffer[++charBufferLast] = '\0';
                    fprintf(stderr, "Error: invalid token: '%s'. \n", RPNStack[i].ch);
                    exit(EXIT_FAILURE);
                }
                tmpStack[++tmpStackIndex] = formRPNElementOp("cos");
                i = i+2;
                break;
            case 'P':
                if (input[i+1] != 'I') {
                    //error
                    charBuffer[++charBufferLast] = input[i+1];
                    charBuffer[++charBufferLast] = '\0';
                    fprintf(stderr, "Error: invalid token: '%s'. \n", RPNStack[i].ch);
                    exit(EXIT_FAILURE);
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
                } /* endif */
                break;
            case '.':
                if (!isdigit(input[i+1])) {
                    //error
                    charBuffer[++charBufferLast] = input[i+1];
                    charBuffer[++charBufferLast] = '\0';
                    fprintf(stderr, "Error: invalid token: '%s'. \n", RPNStack[i].ch);
                    exit(EXIT_FAILURE);
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
                        } /* endswitch */
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
                        }  /* endswitch */
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
                    fprintf(stderr, "Error: bad input syntax. \n");
                    exit(EXIT_FAILURE);
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
                charBuffer[++charBufferLast] = '\0';
                fprintf(stderr, "Error: invalid token: '%s'. \n", charBuffer);
                exit(EXIT_FAILURE);
                break;
        }
    }
    while (tmpStackIndex != 0) {
        RPNStack[++RPNStackIndex] = tmpStack[tmpStackIndex--];
    }

    return RPNStackIndex;

}

//returns result of calculation
float calculate(struct RPNElement RPNStack[], int RPNStackIndex) {

    float calcStack[20];
    int calcStackIndex = 0;
    int i;

    for (i = 1; i <= RPNStackIndex; i++) {
        if (RPNStack[i].isNumericFlag == true) {
            calcStack[++calcStackIndex] = RPNStack[i].f;
        } else {
            switch(RPNStack[i].ch[0]) {
                case '+':
                    calcStack[calcStackIndex-1] = calcStack[calcStackIndex-1] + calcStack[calcStackIndex];
                    calcStackIndex--;
                    break;
                case '-':
                    calcStack[calcStackIndex-1] = calcStack[calcStackIndex-1] - calcStack[calcStackIndex];
                    calcStackIndex--;
                    break;
                case '/':
                    if (calcStack[calcStackIndex] == 0) {
                        //error
                        fprintf(stderr, "Error: division by zero. \n");
                        exit(EXIT_FAILURE);
                    } /* endif */
                    calcStack[calcStackIndex-1] = calcStack[calcStackIndex-1] / calcStack[calcStackIndex];
                    calcStackIndex--;
                    break;
                case '*':
                    calcStack[calcStackIndex-1] = calcStack[calcStackIndex-1] * calcStack[calcStackIndex];
                    calcStackIndex--;
                    break;
                case 's':
                    if (strcmp(RPNStack[i].ch, "sin") == 0) {
                        calcStack[calcStackIndex] = sin(calcStack[calcStackIndex]);
                    } else {
                        //error
                        fprintf(stderr, "Error: invalid token: '%s'. \n", RPNStack[i].ch);
                        exit(EXIT_FAILURE);
                    }  /* endif */
                    break;
                case 'c':
                    if (strcmp(RPNStack[i].ch, "cos") == 0) {
                        calcStack[calcStackIndex] = cos(calcStack[calcStackIndex]);
                    } else {
                        //error
                        fprintf(stderr, "Error: invalid token: '%s'. \n", RPNStack[i].ch);
                        exit(EXIT_FAILURE);
                    } /* endif */
                    break;
                case 'e':
                    if (strcmp(RPNStack[i].ch, "exp") == 0) {
                        calcStack[calcStackIndex] = exp(calcStack[calcStackIndex]);
                    } else {
                        //error
                        fprintf(stderr, "Error: invalid token: '%s'. \n", RPNStack[i].ch);
                        exit(EXIT_FAILURE);
                    } /* endif */
                    break;
            }
        }
    }
    return calcStack[1];
}

// form operator element for stack
struct RPNElement formRPNElementOp(char charBuffer[])
{
    struct RPNElement tmp;

    strcpy(tmp.ch, charBuffer);
    tmp.isNumericFlag = false;

    return (tmp);
}

// form number element for stack
struct RPNElement formRPNElementNum(float num)
{
    struct RPNElement tmp;

    tmp.f = num;
    tmp.isNumericFlag = true;

    return (tmp);
}
