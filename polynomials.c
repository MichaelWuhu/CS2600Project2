#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int countTerms(const char *polyStr) {
    // this function will only count the exponents to see how big the array size should be
    int count = 0;
    const char *ptr = polyStr;

    while (*ptr) {
        if (*ptr == '^') {
            count++;
        }
        ptr++;
    }

    return count;
}

void parsePolynomial(const char *polyStr, int **coeff, int **expo, int *numTerms) {
    // TODO: implement
}

int main() {
    const char *testCase1 = "-4x^0 + x^1 + 4x^3 - 4x^5 - 3x^7";
    int *coeff;
    int *expo;
    int numTerms;

    numTerms = countTerms(testCase1);
    printf("Number of terms: %d\n", numTerms);

    // parsePolynomial(testCase1, &coeff, &expo, &numTerms);



    // Print the coefficients array
    for (int i = 0; i < numTerms; i++) {
        printf("%d ", coeff[i]);
    }
    printf("\n");

    // Print the exponents array
    for (int i = 0; i < numTerms; i++) {
        printf("%d ", expo[i]);
    }

    printf("\n");

    free(coeff);
    free(expo);
    
    
    // printf(""
    //        "(1) Addition\n"
    //        "(2) Subtraction\n"
    //        "(3) Enter two new polynomials\n"
    //        "(4) Exit\n");

    // int choice;
    // scanf("%d", &choice);
    
    return 0;
}