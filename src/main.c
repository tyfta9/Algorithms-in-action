#include "..\include\CarPartProduct.h"
#include "..\include\ReadProductFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    part *products = 0;
    int size = 0;

    // count the number of products
    size = FGetProductCount();

    // allocate memory of the needed size and check for error
    if((products = calloc(size, sizeof(part))) == NULL)
    {
        fprintf(stderr, "Error, couldn't allocate memory.\n");
        getchar();
        return 1;
    }

    // read products
    FReadProduct(products, size);

    printf("red products\n");

    PrintParts(products, size);

    printf("sorted products\n");

    // sort product by weight
    SortByWeight(products, 0, size-1);

    PrintParts(products, size);

    // free the memory spaces
    free(products);

    return 0;
}