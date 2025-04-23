#include "..\include\CarPartProduct.h"
#include "..\include\ReadProductFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// sorts the products by weight
void SortByWeight(part *products, int low, int high);
// merge for merge sort 
void Merge(part *products, int low, int mid, int high);

// prints list of parts
void PrintParts(part *p, int size);

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

// prints list of parts
void PrintParts(part *p, int size)
{
    // go through products and print each part
    for(int i = 0; i < size; i++)
    {
        printf("%d,%5d,", (*(p+i)).line, (*(p+i)).batch);
        printf("%9s,", (*(p+i)).date);
        printf("%4d,%27s,", (*(p+i)).id, (*(p+i)).name);
        printf("%6s,%2d,", (*(p+i)).engine, (*(p+i)).bin);
        printf("%6.2f\n", (*(p+i)).weight);
    }
}

void SortByWeight(part *products, int low, int high)
{
    // if n < 2
    if(low == high)
        return;
    // count mid pointer
    int mid = low + (high-low)/2;
    // sort left half
    SortByWeight(products, low, mid);
    // sort right half
    SortByWeight(products, mid+1, high);
    // merge two halfs
    Merge(products, low, mid, high);
}

void Merge(part *products, int low, int mid, int high)
{
    part *tempProd = NULL;
    int size = high-low+1;

    // allocate temporary memory and check for successful allocation
    if((tempProd = calloc(size, sizeof(part))) == NULL)
    {
        fprintf(stderr, "Error, could not allocate temporary memory.\n");
        exit(1);
    }

    // go trough temporary arr
    for(int i = 0, left = low, right = mid+1; i < size;)
    {
        // if left pointer didn't get to mid and right didn't get to end of list
        if(left <= mid && right <= high)
        {
            // if left product's weight less or equal then right's
            if(products[left].weight <= products[right].weight)
            {
                // copy it to temp arr
                tempProd[i++] = products[left++];
            }
            else
            {
                // copy it to temp arr
                tempProd[i++] = products[right++];
            }
        }
        else
        {
            // go trough remaining left products
            while(left <= mid)
            {
                // copy to temp arr
                tempProd[i++] = products[left++];
            }
            // go through remaining right products
            while(right <= high)
            {
                // copy to temp arr
                tempProd[i++] = products[right++];
            }
        }
    }

    // go through temp arr 
    for(int i = 0; i < size;)
    {
        // copy to the actual products arrray
        products[low++] = tempProd[i++];
    }

    free(tempProd);
}