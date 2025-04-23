#include "..\include\CarPartProduct.h"
#include "..\include\ReadProductFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

// prompts user to search and displays results of search
void SearchProductMenu(part *product, int size);
// displays report
void DisplayReport(part *products, int productsNumber);

int main(void)
{
    part *products = 0;
    int size = 0;

    // Task 4, count products, O(N)
    // count the number of products
    size = FGetProductCount();

    // allocate memory of the needed size and check for error
    if((products = calloc(size, sizeof(part))) == NULL)
    {
        fprintf(stderr, "Error, couldn't allocate memory.\n");
        // let user read before closing exiting program
        getchar();
        return 1;
    }

    // Task 2, Merge files in one list, O(N)
    // read products
    FReadProduct(products, size);

    printf("\n\n\tList of Unsorted products\n\n");

    PrintParts(products, size);
    
    // Task 1, Sort list by weight, O(NLog(N))
    // sort product by weight
    SortByWeight(products, 0, size-1);

    printf("\n\n\tList of Sorted products\n\n");

    PrintParts(products, size);

    // Task 3, Search for product, O(Log(N))
    SearchProductMenu(products, size);

    // Task 4, display product count
    DisplayReport(products, size);

    // free the memory spaces
    free(products);

    return 0;
}

void DisplayReport(part *products, int productsNumber)
{
    printf("\n\tReport\n");
    printf("\tTotal Product Number - %d items\n", productsNumber);
    printf("\tTotal Weight - %.2f kg\n\n", CountTotalWeight(products, productsNumber));
}

// prompts user to search and displays results of search
void SearchProductMenu(part *products, int size)
{
    float weight = 0;
    part *product = 0;
    char command = 0;

    // do while command is equal to 'a'
    do
    {
        printf("\nEnter weight you want to find: ");
        scanf("%f", &weight);
    
        // Task 3, Search for product, O(Log(N))
        product = FindPartByWeight(products, size, weight);
        
        if(product != NULL)
        {
            PrintParts(product, 1);
        }
        else
        {
            printf("Could not find specified product\n");
        }

        // clean the buffer
        while(getchar() != '\n');

        // do while command is not 'a' or 'q'
        do
        {
            printf("\nEnter \'a\' to go again or \'q\' to exit..\n");
        } while((command = getchar()) != 'a' && command != 'q'); 
    } while(command == 'a');
}