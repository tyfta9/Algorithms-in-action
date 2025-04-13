#include "..\include\CarPartProduct.h"
#include "..\include\ReadProductFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// // sorts the products by weight
// void Merge_SortByWeight(part *products, int low, int high);
// // merge for merge sort 
// void Merge(part *products, int low, int mid, int high);

int main(void)
{
    part *products = 0;
    int size = 0;

    // count the size and check for error
    if((size = FGetProductCount()) == -1)
    {
        fprintf(stderr, "Error, couldn't count product.\n");
        return 1;
    }

    // read products
    products = FReadProduct(size);
    

    // sort product by weight
    //                  Merge_SortByWeight(products, 0, size-1);

    printf("%s\n", products[19].name);

    // free the memory spaces
    free(products);

    return 0;
}

// void Merge_SortByWeight(part *products, int low, int high)
// {
//     int mid = (high-low)/2;
//     // if n < 2
//     if(low == high)
//         return;
//     Merge_SortByWeight(products, low, mid);
//     Merge_SortByWeight(products, mid+1, high);
//     Merge(products, low, mid, high);
// }