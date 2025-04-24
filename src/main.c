#include "..\include\CarPartProduct.h"
#include "..\include\ReadProductFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// file path length
#define PATHLEN 100
// amount of files
#define FILERANGE 4

// file path
const char *fPath = "./data/";             
// file name
const char *fName = "line";
// file extension 
const char *fExt = ".csv";
// file delimeter
char *delim = ",";

// read products from files
void ReadProductFiles(part *products, int size);
// counts products in files
int CountProductFiles();
// prompts user to search and displays results of search
void SearchProductMenu(part *product, int size);
// displays report
void DisplayReport(part *products, int productsNumber);
// displays product list menu
void ListProductsMenu(part *products, int size);

int main(int argc, char *argv[])
{
    part *products = 0;
    int size = 0;

    
    // Task 4, count products, O(N)
    // count the number of products
    size = CountProductFiles();

    // allocate memory of the needed size and check for error
    if((products = calloc(size, sizeof(part))) == NULL)
    {
        fprintf(stderr, "Error, couldn't allocate memory.\n");
        // let user read before closing exiting program
        getchar();
        return 1;
    }

    // Task 1, Task 2
    ListProductsMenu(products, size);

    // Task 3, Search for product, O(Log(N))
    SearchProductMenu(products, size);

    // Task 4, display product count
    DisplayReport(products, size);

    // free the memory spaces
    free(products);

    return 0;
}

void ReadProductFiles(part *products, int size)
{
    char fullFilePath[PATHLEN] = {0};


    // go through all the files
    for(int i = 0; i < FILERANGE; i++)
    {
        // cat all the strings to complete file path
        snprintf(fullFilePath, PATHLEN, "%s%s%d%s", fPath, fName, i+1, fExt);
        // read products from the file
        FReadProducts(&products, size, fullFilePath, delim);
    }
}

int CountProductFiles()
{
    int count = 0;
    char fullFilePath[PATHLEN] = {0};
    

    // go through all the files
    for(int i = 0; i < FILERANGE; i++)
    {
        // cat all the strings to complete file path
        snprintf(fullFilePath, PATHLEN, "%s%s%d%s", fPath, fName, i+1, fExt);
        // count row in the file
        count += FGetRowCount(fullFilePath);
        // exclude header the file
        count--;
    }

    return count;
}

// displays product list menu
void ListProductsMenu(part *products, int size)
{
    // Task 2, Merge files in one list, O(N)
    // read products
    ReadProductFiles(products, size);

    printf("\n\n\tList of Unsorted products\n\n");

    PrintParts(products, size);
    
    // Task 1, Sort list by weight, O(NLog(N))
    // sort product by weight
    SortByWeight(products, 0, size-1);

    printf("\n\n\tList of Sorted products\n\n");

    PrintParts(products, size);
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
    char command = 'a';


    // while command is equal to 'a'
    while(command == 'a')
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

        // prompt user to input
        printf("\nEnter \'a\' to go again or \'q\' to exit..\n");
        
        // do while command is not 'a' or 'q'
        while((command = getchar()) != 'a' && command != 'q')
        {
            printf("\nError, wrong format, try again.\n");
            printf("Enter \'a\' to go again or \'q\' to exit..\n");
        }
    }
}