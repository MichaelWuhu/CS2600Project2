#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int countTerms(const char *polyStr)
{
    // this function will only count the exponents to see how big the array size should be
    int count = 0;
    const char *ptr = polyStr;

    while (*ptr)
    {
        if (*ptr == '^')
        {
            count++;
        }
        ptr++;
    }

    return count;
}

void parsePolynomial(const char *polynomial, int **coefficients, int **exponents, int numTerms)
{
    *coefficients = (int *)malloc(numTerms * sizeof(int)); // Allocate memory for coefficients
    *exponents = (int *)malloc(numTerms * sizeof(int));    // Allocate memory for exponents

    const char *ptr = polynomial; // Pointer to traverse the input string

    int termIndex = 0; // Index for the current term
    int coefficient, exponent;
    char sign = '+';

    while (*ptr)
    {
        if (*ptr == '+' || *ptr == '-')
        {
            sign = *ptr;
            ptr++;
        }

        if (isdigit(*ptr) || *ptr == 'x')
        {
            if (*ptr == 'x')
            {
                coefficient = (sign == '-') ? -1 : 1;
            }
            else
            {
                coefficient = 0;
                while (isdigit(*ptr))
                {
                    coefficient = coefficient * 10 + (*ptr - '0');
                    ptr++;
                }
                if (sign == '-')
                {
                    coefficient = -coefficient;
                }
            }

            if (*ptr == 'x')
            {
                ptr++;
                if (*ptr == '^')
                {
                    ptr++;
                    exponent = 0;
                    while (isdigit(*ptr))
                    {
                        exponent = exponent * 10 + (*ptr - '0');
                        ptr++;
                    }
                }
                else
                {
                    exponent = 1;
                }
            }
            else
            {
                exponent = 0;
            }

            (*coefficients)[termIndex] = coefficient;
            (*exponents)[termIndex] = exponent;
            termIndex++;
        }
        else
        {
            ptr++;
        }
    }
}

int main()
{
    const char *testCase1 = "-4x^0 + x^1 + 4x^3 - 4x^5 - 3x^7";
    int *coefficients;
    int *exponents;
    int numTerms;

    numTerms = countTerms(testCase1);
    printf("Number of terms: %d\n", numTerms);

    parsePolynomial(testCase1, &coefficients, &exponents, numTerms);

    // Print the coefficients array
    for (int i = 0; i < numTerms; i++)
    {
        printf("%d ", coefficients[i]);
    }
    printf("\n");

    // Print the exponents array
    for (int i = 0; i < numTerms; i++)
    {
        printf("%d ", exponents[i]);
    }

    printf("\n");

    free(coefficients);
    free(exponents);

    // printf(""
    //        "(1) Addition\n"
    //        "(2) Subtraction\n"
    //        "(3) Enter two new polynomials\n"
    //        "(4) Exit\n");

    // int choice;
    // scanf("%d", &choice);

    return 0;
}