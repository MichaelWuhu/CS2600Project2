// prompt for polynomials if they don't already exist
    if (strlen(polynomial1) == 0 || strlen(polynomial2) == 0)
    {
        enterPolynomials(polynomial1, polynomial2);
    }

    printf("polynomial1: %s\npolynomial2: %s\n\n", polynomial1, polynomial2);
