void parsePolynomial(const char *polynomial, int **coefficients, int **exponents, int numTerms)
{
    *coefficients = (int *)malloc(numTerms * sizeof(int)); // Allocate memory for coefficients
    *exponents = (int *)malloc(numTerms * sizeof(int));    // Allocate memory for exponents

    const char *ptr = polynomial; // Pointer to traverse the input string
    int index = 0;                // Index to track the term position

    while (*ptr && index < numTerms)
    {
        int coefficient = 0, exponent = 0, sign = 1;

        // Check for a sign
        if (*ptr == '-')
        {
            sign = -1;
            ptr++;
        }
        else if (*ptr == '+')
        {
            sign = 1;
            ptr++;
        }

        // Check the coefficient
        while (isdigit(*ptr))
        {
            coefficient = coefficient * 10 + (*ptr - '0');
            ptr++;
        } 
        
        if (coefficient == 0 && *ptr == 'x')
        {
            coefficient = 1;
        }

        if (*ptr == 'x')
        {
            ptr++;
            if (*ptr == '^')
            {
                ptr++;
                while (isdigit(*ptr))
                {
                    exponent = exponent * 10 + (*ptr - '0');
                    ptr++;
                }
                if (exponent == 0) {
                    exponent = 1;
                }
            }
        }

        // Store the coefficient and exponent
        (*coefficients)[index] = coefficient * sign;
        (*exponents)[index] = exponent;
        index++;

        // Skip whitespace between terms
        while (*ptr == ' ')
        {
            ptr++;
        }
    }
}
