/*
Name        : Busala Sai Divakar.

Date        : 07-03-2025.

Project     : Arbitrary Precision Calculator (APC).

Description : An Arbitrary Precision Calculator (APC) is a software tool that allows users to perform mathematical 
calculations with numbers of arbitrary size and precision. Unlike standard calculators that are limited by the 
fixed size of data types, an APC can handle numbers with hundreds or even thousands of digits, making it suitable 
for applications that require high precision, such as scientific computations, cryptography, and financial calculations. 
The APC typically supports basic arithmetic operations (addition, subtraction, multiplication, division,and modulus) 
as well as while ensuring accurate results regardless of the size of the operands.
*/

#include "apc.h"

int main(int argc, char *argv[])
{
    node *head1 = NULL, *tail1 = NULL, *head2 = NULL, *tail2 = NULL, *headR = NULL, *tailR = NULL; //Initialize head and tail pointers for operand1, operand2 and result lists to NULL

    if (cla_validation(argc, argv) != 0) // Validate the command line arguments and check if they are in the correct format
    {
        printf("Usage: ./a.out <OPERAND1> <OPERATOR> <OPERAND2>\n"); // print usear message give the correct format
        return FAILURE; // Return failure if the command line arguments are not in the correct format
    }

    int sign1 = (argv[1][0] == '-') ? -1 : 1; // Determine the sign of operand1 based on the first character of the input string
    int sign2 = (argv[3][0] == '-') ? -1 : 1; // Determine the sign of operand2 based on the first character of the input string

    create_list((argv[1][0] == '-' || argv[1][0] == '+') ? &argv[1][1] : argv[1], &head1, &tail1); //create the list for op1 is sign is pass the next char otherwise pass the whole string
    create_list((argv[3][0] == '-' || argv[3][0] == '+') ? &argv[3][1] : argv[3], &head2, &tail2); //create the list for op2 is sign is pass the next char otherwise pass the whole string

    remove_pre_zeros(&head1); //starting zeros are remove in operand1 file
    remove_pre_zeros(&head2); //starting zeros are remove in operand2 file

    printf("OPERAND1 -> %s", (sign1 == -1) ? "-" : ""); // Print the sign of operand1 if it is negative
    print_list(head1); // print the digits of operand1

    printf("OPERATOR -> %s\n", argv[2]); // print the operator

    printf("OPERAND2 -> %s", (sign2 == -1) ? "-" : ""); // Print the sign of operand2 if it is negative
    print_list(head2); // print the digits of operand2
    
    printf("RESULT   -> "); // print the result label

    int cmp = compare_list(head1, head2);   // compare once and store the result 
    switch (argv[2][0]) // Switch statement to perform the operation based on the operator provided in the command line arguments
    {
        case '+': // preforn the addition operation
            if (sign1 == sign2) //if both opreands sign is same then do the addition operation
            {
                if (sign1 == -1) // If operand1 is negative, print the negative sign before the result
                {
                    printf("-"); // print the negative sign before the result
                }
                addition(tail1, tail2, &headR, &tailR); // perform the addition operation
            }
            else
            {
                if (cmp == OPERAND1) // If operand1 is greater than operand2, then perform subtraction of operand2 from operand1
                {
                    if (sign1 == -1) // If operand1 is negative, print the negative sign before the result
                    {
                        printf("-"); // print the negative sign before the result
                    }
                    subtraction(tail1, tail2, &headR, &tailR); // perform the subtraction operation of operand2 from operand1
                }
                else
                {
                    if (sign2 == -1) // If operand2 is negative, print the negative sign before the result
                    {
                        printf("-"); // perform the subtraction operation of operand1 from operand2
                    }
                    subtraction(tail2, tail1, &headR, &tailR); // perform the subtraction operation of operand1 from operand2
                }
            }
            break;

        case '-': // perform the subtraction operation
            if (sign1 != sign2) // If the signs of the operands are different, then perform addition
            {
                if (sign1 == -1) // If operand1 is negative, print the negative sign before the result
                {
                    printf("-"); // print the negative sign before the result
                }
                addition(tail1, tail2, &headR, &tailR); // perform the addition operation
            }
            else
            {
                if (cmp == OPERAND1) // If operand1 is greater than operand2, then perform subtraction of operand2 from operand1
                {
                    if (sign1 == -1) // If operand1 is negative, print the negative sign before the result
                    {
                        printf("-"); // print the negative sign before the result 
                    }
                    subtraction(tail1, tail2, &headR, &tailR); // perform the subtraction operation of operand2 from operand1
                }
                else
                {
                    if (sign1 == 1) // If operand1 is positive, print the negative sign before the result
                    {
                        printf("-"); // print the negative sign before the result
                    }
                    subtraction(tail2, tail1, &headR, &tailR); // perform the subtraction operation of operand1 from operand2
                }
            }
            break;

        case 'x': case 'X': // perform the multiplication operation

            if (sign1 != sign2) // If the signs of the operands are different, then the result will be negative
            {
                printf("-"); // print the negative sign before the result
            }
            multiplication(tail1, tail2, &headR, &tailR); // perform the multiplication operation
            break;

        case '/': // perform the division operation

            if (sign1 != sign2) // If the signs of the operands are different, then the result will be negative
            {
                printf("-"); // print the negative sign before the result
            }
            division(head1, head2, tail2, &headR, &tailR); // perform the division operation
            break;

        case '%': // perform the modulus operation

            modulus(head1, head2, tail2, &headR, &tailR); // perform the modulus operation
            if (sign1 == -1 && !(headR->data == 0 && headR->next == NULL)) // If operand1 is negative and the result is not zero
            {
                printf("-");// print the negative sign before the result
            }
            break;

        default: // if operator is invalid
            printf("Invalid Operator -> Try Again!\n"); 
            return FAILURE; // Return failure if the operator is invalid
    }
    remove_pre_zeros(&headR); // Remove leading zeros from the result list

    // If the result is zero, print 0, otherwise print the digits of the result
    ((argv[2][0] == '-' || argv[2][0] != '%' && argv[2][0] != '/')&&( headR -> data == 0 || headR == NULL )) ? printf("\b0\n") : print_list(headR); 

    delete_list(&head1, &tail1); // freed the memory allocated for operand1 list
    delete_list(&head2, &tail2); // freed the memory allocated for operand2 list
    delete_list(&headR, &tailR); // freed the memory allocated for result list
    return 0; // return success
}