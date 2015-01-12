/* CS261- Assignment 2 - Part 3*/
/* Name: Jen Anderson
 * Date: 7/14/13
 * Solution description: This program uses dynamic arrays to create a reverse polish notation calculator.
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <math.h>

#include "dynamicArray.h"

#define PI  3.14159265
#define E   2.7182818

/* param: s the string
   param: num a pointer to double
   returns: true (1) if s is a number else 0 or false.
   postcondition: if it is a number, num will hold
   the value of the number
*/
int isNumber(char *s, double *num)
{
    char *end;
    double returnNum;

    if(strcmp(s, "0") == 0)
    {
        *num = 0;
        return 1;
    }
    else
    {
        returnNum = strtod(s, &end);
        /* If there's anythin in end, it's bad */
        if((returnNum != 0.0) && (strcmp(end, "") == 0))
        {
            *num = returnNum;
            return 1;
        }
    }
    return 0;  //if got here, it was not a number
}

/*  param: stackSize current size of the stack
           minSize   minimum size for operation
    Tests whether the stack size is at least minSize. If not minSize,
    report error and exit program.
*/
void charSizeAtLeast(int stackSize, int operatorNumber)
{
    if (stackSize < operatorNumber)
    {
       printf("Your amount of numbers doesn't match your amount of operators.\n");
       exit(0);
    }
}

/*    param: stack the stack being manipulated
    pre: the stack contains at least two elements
    post: the top two elements are popped and
    their sum is pushed back onto the stack.
*/
void add(struct DynArr *stack)
{
    TYPE sum = 0; //Whatever type is given in the command line is the same type the answer is given in

    charSizeAtLeast(sizeDynArr(stack), 2);
    assert(sizeDynArr(stack) >= 2);

    //Adds the first two numbers to sum and removes the numbers from the stack.
    sum += topDynArr(stack);
    popDynArr(stack);
    sum += topDynArr(stack);
    popDynArr(stack);

    //The sum goes back on the top of the stack
    pushDynArr(stack, sum);
}

/*    param: stack the stack being manipulated
    pre: the stack contains at least two elements
    post: the top two elements are popped and
    their difference is pushed back onto the stack.
*/
void subtract(struct DynArr *stack)
{
    TYPE firstNumber;
    TYPE secondNumber;
    TYPE difference;

    charSizeAtLeast(sizeDynArr(stack), 2);
    assert(sizeDynArr(stack) >= 2);

    secondNumber = topDynArr(stack);
    popDynArr(stack);

    firstNumber = topDynArr(stack);
    popDynArr(stack);

    difference = firstNumber - secondNumber;

    pushDynArr(stack, difference);
}

/*    param: stack the stack being manipulated
    pre: the stack contains at least two elements
    post: the top two elements are popped and
    their quotient is pushed back onto the stack.
*/
void divide(struct DynArr *stack)
{
    TYPE firstNumber;
    TYPE secondNumber;
    TYPE quotient;

    charSizeAtLeast(sizeDynArr(stack), 2);
    assert(sizeDynArr(stack) >= 2);

    secondNumber = topDynArr(stack);
    popDynArr(stack);

    firstNumber = topDynArr(stack);
    popDynArr(stack);

    quotient = firstNumber / secondNumber;

    /* Push the quotient to the top of the stack */
    pushDynArr(stack, quotient);
}

/*    param: stack the stack being manipulated
    pre: the stack contains at least two elements
    post: the top two elements are popped and
    their product is pushed back onto the stack.
*/
void multiply(struct DynArr *stack)
{
    TYPE firstNumber;
    TYPE secondNumber;
    TYPE product;

    charSizeAtLeast(sizeDynArr(stack), 2);
    assert(sizeDynArr(stack) >= 2);

    secondNumber = topDynArr(stack);
    popDynArr(stack);

    firstNumber = topDynArr(stack);
    popDynArr(stack);

    product = firstNumber * secondNumber;

    /* Push the product to the top of the stack */
    pushDynArr(stack, product);
}

/*    param: stack the stack being manipulated
    pre: the stack contains at least two elements
    post: the top two elements are popped and
    the inital number's power is pushed back onto the stack.
*/
void power(struct DynArr *stack)
{
    TYPE base;
    TYPE exponent;
    TYPE result;

    charSizeAtLeast(sizeDynArr(stack), 2);
    assert(sizeDynArr(stack) >= 2);

    exponent = topDynArr(stack);
    popDynArr(stack);

    base = topDynArr(stack);
    popDynArr(stack);

    result = pow(base, exponent);

    /* Push the result to the top of the stack */
    pushDynArr(stack, result);
}

/*    param: stack the stack being manipulated
    pre: the stack contains at least one element
    post: the top element is popped and
    the absolute value of the number is pushed back onto the stack.
*/
void absoluteValue(struct DynArr *stack)
{
    TYPE result;

    charSizeAtLeast(sizeDynArr(stack), 1);
    assert(sizeDynArr(stack) >= 1);

    result = topDynArr(stack);
    popDynArr(stack);
    if (result < 0)
    {
        result *= (-1);
    }
    pushDynArr(stack, result);
}

/*    param: stack the stack being manipulated
    pre: the stack contains at least one element
    post: the top element is popped and
    the square root of the number is pushed back onto the stack.
*/
void squareRoot(struct DynArr *stack)
{
    TYPE result;

    charSizeAtLeast(sizeDynArr(stack), 1);
    assert(sizeDynArr(stack) >= 1);

    result = topDynArr(stack);
    popDynArr(stack);

    //The result is the square root of itself
    result = sqrt(result);

    /* Push the result to the top of the stack */
    pushDynArr(stack, result);
}

/*    param: stack the stack being manipulated
    pre: the stack contains at least one element
    post: the top element is popped and e is pushed before pushing
    the popped number to the stack. The power function is then called.
*/
void exponential(struct DynArr *stack)
{
    TYPE temp;

    charSizeAtLeast(sizeDynArr(stack), 1);
    assert(sizeDynArr(stack) >= 1);

    /* Add e before the number */
    temp = topDynArr(stack);
    popDynArr(stack);
    pushDynArr(stack, E);
    pushDynArr(stack, temp);

    /* Call the power function */
    power(stack);
}

/*  param: stack the stack being manipulated
    pre: the stack contains at least one element
    post: the top element is popped and e is pushed before pushing
    the popped number to the stack. The power function is then called.
*/
void naturalLogarithm(struct DynArr *stack)
{
    TYPE result;

    result = topDynArr(stack);
    popDynArr(stack);
    result = log(result);
    pushDynArr(stack, result);
}

/*  param: stack the stack being manipulated
    pre: the stack contains at least one element
    post: the top element is popped and e is pushed before pushing
    the popped number to the stack. The power function is then called.
*/
void logarithm(struct DynArr *stack) //base is 1 for ln and 0 for log
{
    TYPE result;

    charSizeAtLeast(sizeDynArr(stack), 1);
    assert(sizeDynArr(stack) >= 1);

    /* log of the popped number */
    result = topDynArr(stack);
    popDynArr(stack);
    result = log10(result);

    /* Push the result to the top of the stack */
    pushDynArr(stack, result);
}

double calculate(int numInputTokens, char **inputString)
{
    int i;
    double result = 0.0;
    char *s = (char *) malloc (numInputTokens * sizeof(char));
    struct DynArr *stack;

    //set up the stack
    stack = createDynArr(20);

    // start at 1 to skip the name of the calculator calc
    for(i=1;i < numInputTokens;i++)
    {
        s = inputString[i];

        // Hint: General algorithm:
        // (1) Check if the string s is in the list of operators.
        //   (1a) If it is, perform corresponding operations.
        //   (1b) Otherwise, check if s is a number.
        //     (1b - I) If s is not a number, produce an error.
        //     (1b - II) If s is a number, push it onto the stack

        if(strcmp(s, "+") == 0)
        {
            add(stack);
        }
        else if(strcmp(s,"-") == 0)
        {
            subtract(stack);
        }
        else if(strcmp(s, "/") == 0)
        {
            divide(stack);
        }
        else if(strcmp(s, "x") == 0)
        {
            multiply(stack);
        }
        else if(strcmp(s, "^") == 0)
        {
            power(stack);
        }
        else if(strcmp(s, "^2") == 0)
        {
            pushDynArr(stack, 2);
            power(stack);
        }
        else if(strcmp(s, "^3") == 0)
        {
            pushDynArr(stack, 3);
            power(stack);
        }
        else if(strcmp(s, "abs") == 0)
        {
            absoluteValue(stack);
        }
        else if(strcmp(s, "sqrt") == 0)
        {
            squareRoot(stack);
        }
        else if(strcmp(s, "exp") == 0)
        {
            exponential(stack);
        }
        else if(strcmp(s, "ln") == 0)
        {
           naturalLogarithm(stack);
        }
        else if(strcmp(s, "log") == 0)
        {
            logarithm(stack);
        }
        else
        {
            double *n = (double *) malloc(sizeof(double));
            if (isNumber(s, n))
            {
                pushDynArr(stack, *n);
            }
            else if (strcmp(s, "e") == 0)
            {
                pushDynArr(stack, E);
            }
            else if (strcmp(s, "pi") == 0)
            {
                pushDynArr(stack, PI);
            }
            else
            {
                printf("%s is not a legal operator, so this program can't run\n", s);
                exit(0);
            }
        }
    }

    if (sizeDynArr(stack) > 1)
    {
        printf("There are two many numbers entered in the command line.");
        exit(0);
    }
    result = topDynArr(stack);
    printf("The result is: %f\n", result);
    return result;
}

int main(int argc, char** argv)
{
    // assume each argument is contained in the argv array
    // argc-1 determines the number of operands + operators
     if (argc == 1)
        return 0;

    calculate(argc,argv);
    return 0;
}


