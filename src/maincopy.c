// #include "ReadProductFile.h"
// #include "CarPartProduct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// amount of files
#define FILERANGE 4
// file path length
#define PATHLEN 30
// string row length of a file
#define ROWLEN 150
// number of columns in files
#define COLNUM 8

// date length
#define DATELEN 9
// product id length
#define IDLEN 5
// name length
#define NAMELEN 30
// target engine code length
#define ENGINECODELEN 6

typedef struct carPartProduct
{
    // line code
    char line;

    // batch code
    unsigned int batch;

    // bin number
    char bin;

    // product weight
    float weight;

    // product ID
    char id[IDLEN];

    // batch date & time
    char date[DATELEN];

    // product name
    char name[NAMELEN];

    // target engine code
    char engine[ENGINECODELEN];   
} 
part;

// get total product or line count in all files
int FGetProductCount();
// converts row of a file to product structure,
// uses specified delimeter
part RowToProduct(char *row, char *delim);
// read all product from file
part* FReadProduct(int size);

// // sorts the products by weight
// void Merge_SortByWeight(part *products, int low, int high);
// // merge for merge sort 
// void Merge(part *products, int low, int mid, int high);

// file path
const char *fPath = "..\\data\\";
// file name
const char *fName = "line";
// file extension 
const char *fExt = ".csv";

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

    printf("%s\n", products[20].name);

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

// read product from file 
part* FReadProduct(int size)
{
    part *products = 0;
    FILE *fp = 0;
    char fullPath[PATHLEN] = {0};
    char row[ROWLEN] = {0};

    
    // allocate memory of the needed size
    products = malloc(sizeof(part)*size);
    // error checking 
    if(products == NULL)
    {
        fprintf(stderr, "Error, couldn't allocate memory.\n");
        return NULL;
    }

    // go through the file range
    for(int i = 0, j = 0; i < FILERANGE; i++)
    {        
        // assemble full file path to i file
        snprintf(fullPath, PATHLEN, "%s%s%d%s", fPath, fName, i+1, fExt);
        // open the file
        fp = fopen(fullPath, "r");
        // check for successful opening
        if(fp == NULL)
        {
            fprintf(stderr, "Error, Couldn't open files.\n");
            return NULL;
        }

        // skip first header row
        fgets(row, ROWLEN, fp);

        // go through products
        while(fgets(row, ROWLEN, fp))
        {
            products[j] = RowToProduct(row, ",");
            j++;
        }
        
        // close the file
        fclose(fp);
    }

    return products;
}

// converts row of a file to product structure,
// uses specified delimeter
part RowToProduct(char *row, char *delim)
{
    part p;
    char *tokens[COLNUM] = {0};
    int size = 0;


    tokens[0] = strtok(row, delim);
    size++;

    while((tokens[size] = strtok(NULL, delim)) != NULL)
    {
        size++;
    }

    if(size != COLNUM)
    {
        fprintf(stderr, "Error, wrong file format.\n");
        return p;
    }
    
    p.line = *tokens[0];
    p.batch = atoi(tokens[1]);
    strcpy(p.date, tokens[2]);
    strcpy(p.id, tokens[3]);
    strcpy(p.name, tokens[4]);
    strcpy(p.engine, tokens[5]);
    p.bin = *tokens[6];
    p.weight = (float)atof(tokens[7]);

    return p;
}

// time complexity is O(N),
// where N is number of rows in files
int FGetProductCount()
{
    int count = 0;
    char fullPath[PATHLEN];                                                             // TO REFACTOR: = {0};
    char row[ROWLEN];                                                                   // TO REFACTOR: = {0};
    FILE *fp = 0;
    
    // go through all the files
    for(int i = 0; i < FILERANGE; i++)
    {
        // cat all the strings to complete file path
        snprintf(fullPath, PATHLEN, "%s%s%d%s", fPath, fName, i+1, fExt);
        // open file to read
        fp = fopen(fullPath, "r");
        
        // check for a successful opening
        if(fp == NULL)
        {
            fprintf(stderr, "Could not open file, path: %s\n", fullPath);
            return -1;
        }

        // go trough all rows and count
        while(fgets(row, ROWLEN, fp))
        {
            count++;
        }

        // count header out
        count--;
        
        fclose(fp);        
    }

    return count;
}