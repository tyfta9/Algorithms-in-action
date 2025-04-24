#include "..\include\CarPartProduct.h"
#include <stdio.h>
#include <stdlib.h>

// string row length of a file
#define ROWLEN 150

// get total product or line count in all files excluding headers
int FGetRowCount(char *fullFilePath);
// read all product from file
void FReadProducts(part **products, int size, char *fullFilePath, char *delim);

int FGetRowCount(char *fullFilePath)
{
    int count = 0;
    char row[ROWLEN] = {0};
    FILE *fp = 0;

    // open file to read
    fp = fopen(fullFilePath, "r");
        
    // check for a successful opening
    if(fp == NULL)
    {
        fprintf(stderr, "Could not open file, path: %s\n", fullFilePath);
        // let user read before closing exiting program
        getchar();
        exit(1);
    }

    // go trough all rows and count
    while(fgets(row, ROWLEN, fp))
    {
        count++;
    }
    
    fclose(fp);

    return count;
}

// read product from file 
void FReadProducts(part **products, int size, char *fullFilePath, char *delim)
{
    FILE *fp = 0;
    char row[ROWLEN] = {0};

    // open the file
    fp = fopen(fullFilePath, "r");
    // check for successful opening
    if(fp == NULL)
    {
        fprintf(stderr, "Could not open file, path: %s\n", fullFilePath);
        // let user read before closing exiting program
        getchar();
        exit(1);
    }

    // skip first header row
    fgets(row, ROWLEN, fp);

    // go through products
    while(fgets(row, ROWLEN, fp) && size > 0)
    {
        (*(*products)++) = RowToProduct(row, delim);
        size--;
    }
    
    // close the file
    fclose(fp);
}