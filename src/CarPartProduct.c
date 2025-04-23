#include "..\include\CarPartProduct.h"
#include <stdio.h>
#include <stdlib.h>

// counts total weight of all provided products
float CountTotalWeight(part *products, int size);
// looks for a part with specified weight trough the provided products
part *FindPartByWeight(part *products, int size, float weight);
// prints list of parts
void PrintParts(part *products, int size);
// sorts the products by weight
void SortByWeight(part *products, int low, int high);
// merge for merge sort 
void Merge(part *products, int low, int mid, int high);

// counts total weight of all provided products
float CountTotalWeight(part *products, int size)
{
    float sum = 0;

    for(int i = 0; i < size; i++)
    {
        sum += (*(products+i)).weight;
    }

    return sum;
}

// looks for a product with specified weight
part *FindPartByWeight(part *products, int size, float weight)
{
    int left = 0;
    int mid = 0;
    int right = 0;


    // left is outside
    left = -1;
    // right is last index
    right = size-1;
    // mid is middle index
    mid = left+(right-left)/2;
    // go through products
    while(1+left != right)
    {
        // if weight less or equal to found one
        if(weight <= (*(products+mid)).weight)
        {
            right = mid;
            mid = left+(right-left)/2;
        }
        else
        {
            left = mid;
            mid = left+(right-left)/2;
        }
    }

    // if weight equals to the found one
    if(weight == (*(products+right)).weight)
    {
        // return pointer to the found product
        return (products+right);
    }
    
    // else return null
    return NULL;
} 

// prints list of parts
void PrintParts(part *products, int size)
{
    // go through products and print each part
    for(int i = 0; i < size; i++)
    {
        printf("%d,%5d,", (*(products+i)).line, (*(products+i)).batch);
        printf("%9s,", (*(products+i)).date);
        printf("%4d,%27s,", (*(products+i)).id, (*(products+i)).name);
        printf("%6s,%2d,", (*(products+i)).engine, (*(products+i)).bin);
        printf("%6.2f\n", (*(products+i)).weight);
    }
}

// running time is O(NLog(N))
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

void Merge(part *products, int low, int mid, int high) //                   TO DO - CHANGE SQ BRACKET NOTATION TO POINTER NOTATION 
{
    part *tempProd = NULL;
    int size = high-low+1;

    // allocate temporary memory and check for successful allocation
    if((tempProd = calloc(size, sizeof(part))) == NULL)
    {
        fprintf(stderr, "Error, could not allocate temporary memory.\n");
        // let user read before closing exiting program
        getchar();
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