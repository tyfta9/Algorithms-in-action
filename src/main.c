#include "..\include\CarPartProduct.h"
#include "..\include\ReadProductFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    part *products = 0;
    int size = 0;
    float weight = 0;
    part *product = 0;

    // Task 4, count products, O(N)
    // count the number of products
    size = FGetProductCount();

    // allocate memory of the needed size and check for error
    if((products = calloc(size, sizeof(part))) == NULL)
    {
        fprintf(stderr, "Error, couldn't allocate memory.\n");
        getchar();
        return 1;
    }

    // Task 2, Merge files in one list, O(N)
    // read products
    FReadProduct(products, size);

    printf("\n\n\tList of Unsorted products\n\n");

    PrintParts(products, size);

    printf("\n\n\tList of Sorted products\n\n");

    // Task 1, Sort list by weight, O(NLog(N))
    // sort product by weight
    SortByWeight(products, 0, size-1);

    PrintParts(products, size);

    printf("\nEnter weight you want to find: ");
    scanf("%f", &weight);

    product = FindPartByWeight(products, size, weight);

    // Task 3, Search for product, O(Log(N))
    PrintParts(product, 1);

    // free the memory spaces
    free(products);

    return 0;
}