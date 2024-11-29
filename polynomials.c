#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// function to count the exponents in a polynomial (the exponents tell us the number of 'terms' where something like '4x^2' is considered a 'term')
int countTerms(char *polynomial)
{
    // this function will only count the exponents to see how big the array size should be
    int count = 0;
    char *ptr = polynomial;

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

// function to parse polynomials
void parsePolynomial(char *polynomial, int **coefficients, int **exponents, int numTerms)
{
    *coefficients = (int *)malloc(numTerms * sizeof(int)); // Allocate memory for coefficients
    *exponents = (int *)malloc(numTerms * sizeof(int));    // Allocate memory for exponents

    char *ptr = polynomial; // Pointer to traverse the input string

    int termIndex = 0; // Index for the current term
    int coefficient, exponent;
    char sign = '+';

    while (*ptr)
    {
        // check sign
        if (*ptr == '+' || *ptr == '-')
        {
            sign = *ptr;
            ptr++;
        }

        // checking coefficient
        if (isdigit(*ptr) || *ptr == 'x')
        {
            // if dereferenced pointer is 'x', then assign the sign
            if (*ptr == 'x')
            {
                coefficient = (sign == '-') ? -1 : 1;
            }
            // if not x, then get the coefficient
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

            // checking exponent
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

            // assign the values
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

// function to get user inputted polynomials
void enterPolynomials(char *polynomial1, char *polynomial2)
{
    int isValid;
    while (1)
    {
        isValid = 1;
        printf("\nEnter the first polynomial in the format like this (-4x^0 + x^1 + 4x^3 - 4x^5 - 3x^7): \n");
        fgets(polynomial1, 256, stdin);

        size_t len = strlen(polynomial1);
        if (len > 0 && polynomial1[len - 1] == '\n')
        {
            polynomial1[len - 1] = '\0';
        }

        // verify a polynomial was entered
        char *ptr = polynomial1;
        while (*ptr)
        {
            if (!(isdigit(*ptr) || *ptr == 'x' || *ptr == '+' || *ptr == '-' || *ptr == '^' || *ptr == ' '))
            {
                isValid = 0;
                break;
            }
            ptr++;
        }

        // reprompt if invalid
        if (isValid)
        {
            break;
        }
        else
        {
            printf("Invalid polynomial. Please try again.\n");
        }
    }

    while (1)
    {
        isValid = 1;
        printf("\nEnter the second polynomial in the format like this (-4x^0 + x^1 + 4x^3 - 4x^5 - 3x^7): \n");
        fgets(polynomial2, 256, stdin);

        size_t len = strlen(polynomial2);
        if (len > 0 && polynomial2[len - 1] == '\n')
        {
            polynomial2[len - 1] = '\0';
        }

        // verify a polynomial was entered
        char *ptr = polynomial1;
        while (*ptr)
        {
            if (!(isdigit(*ptr) || *ptr == 'x' || *ptr == '+' || *ptr == '-' || *ptr == '^' || *ptr == ' '))
            {
                isValid = 0;
                break;
            }
            ptr++;
        }

        // reprompt if invalid
        if (isValid)
        {
            break;
        }
        else
        {
            printf("Invalid polynomial. Please try again.\n");
        }
    }
}

// function to add polynomials
void addPolynomials(char* resultPolynomial, int *coefficients1, int *exponents1, int *coefficients2, int *exponents2, int numTerms1, int numTerms2) {
    int maxExponent = 0;

    // Find the maximum exponent in both polynomials
    for (int i = 0; i < numTerms1; i++) {
        if (exponents1[i] > maxExponent) {
            maxExponent = exponents1[i];
        }
    }
    for (int i = 0; i < numTerms2; i++) {
        if (exponents2[i] > maxExponent) {
            maxExponent = exponents2[i];
        }
    }

    // Allocate memory for the result coefficients
    int *resultCoefficients = (int *)calloc(maxExponent + 1, sizeof(int));

    // Add coefficients of the first polynomial
    for (int i = 0; i < numTerms1; i++) {
        resultCoefficients[exponents1[i]] += coefficients1[i];
    }

    // Add coefficients of the second polynomial
    for (int i = 0; i < numTerms2; i++) {
        resultCoefficients[exponents2[i]] += coefficients2[i];
    }

    // Build the result polynomial string
    int pos = 0;
    for (int i = maxExponent; i >= 0; i--) {
        if (resultCoefficients[i] != 0) {
            if (pos > 0 && resultCoefficients[i] > 0) {
                pos += sprintf(resultPolynomial + pos, " + ");
            } else if (resultCoefficients[i] < 0) {
                pos += sprintf(resultPolynomial + pos, " - ");
                resultCoefficients[i] = -resultCoefficients[i];
            }
            if (i == 0) {
                pos += sprintf(resultPolynomial + pos, "%d", resultCoefficients[i]);
            } else if (i == 1) {
                pos += sprintf(resultPolynomial + pos, "%dx", resultCoefficients[i]);
            } else {
                pos += sprintf(resultPolynomial + pos, "%dx^%d", resultCoefficients[i], i);
            }
        }
    }

    free(resultCoefficients);
}

int main()
{
    // char *testCase1 = "-4x^0 + x^1 + 4x^3 - 4x^5 - 3x^7";
    int *coefficients1;
    int *exponents1;
    int numTerms1;
    
    int *coefficients2;
    int *exponents2;
    int numTerms2;
   
    char polynomial1[256] = "";
    char polynomial2[256] = "";
    char resultPolynomial[256] = "";

    int choice;

    // print menu, while loop to validate input
    while (1)
    {
        printf("(1) Addition\n"
               "(2) Subtraction\n"
               "(3) Enter two new polynomials\n"
               "(4) Exit\n");

        scanf("%d", &choice);
        while (getchar() != '\n')
            ; // Clear the input buffer

        if (1 <= choice && 4 >= choice)
        {
            break;
        }
        else
        {
            printf("Invalid choice. Please try again.\n\n");
        }
    }

    // prompt for polynomials if they don't already exist
    if (strlen(polynomial1) == 0 || strlen(polynomial2) == 0)
    {
        enterPolynomials(polynomial1, polynomial2);
    }

    numTerms1 = countTerms(polynomial1);
    parsePolynomial(polynomial1, &coefficients1, &exponents1, numTerms1);

    numTerms2 = countTerms(polynomial2);
    parsePolynomial(polynomial2, &coefficients2, &exponents2, numTerms2);

//////////////////////////////////////
    printf("polynomial 1:\n");
    printf("Coefficients:\n");
    for (int i = 0; i < numTerms1; i++)
    {
        printf("%d ", coefficients1[i]);
    }
    printf("Exponents:\n");
    for (int i = 0; i < numTerms1; i++)
    {
        printf("%d ", exponents1[i]);
    }
    printf("\n");

    printf("polynomial 2:\n");
    printf("Coefficients:\n");
    for (int i = 0; i < numTerms2; i++)
    {
        printf("%d ", coefficients2[i]);
    }
    printf("Exponents:\n");
    for (int i = 0; i < numTerms2; i++)
    {
        printf("%d ", exponents2[i]);
    }
    printf("\n");
////////////////////////////////////


    // printf("polynomial1: %s\npolynomial2: %s\n\n", polynomial1, polynomial2);

    switch (choice)
    {
    case 1:
        // Add the two polynomials
        printf("adding the polynomials");
        addPolynomials(resultPolynomial, coefficients1, exponents1, coefficients2, exponents2, numTerms1, numTerms2);
        printf("Result: %s", resultPolynomial);    
        break;
    case 2:
        // Subtract the two polynomials
        printf("subtracting the polynomials");
        break;
    case 3:
        // Enter two new polynomials
        printf("entering 2 new polynomials");
        enterPolynomials(polynomial1, polynomial2);
        break;
    case 4:
        // Exit the program
        printf("exiting");
        break;
    }

    free(coefficients1);
    free(exponents1);
    coefficients1 = NULL;
    exponents1 = NULL;

    free(coefficients2);
    free(exponents2);
    coefficients2 = NULL;
    exponents2 = NULL;

    return 0;
}