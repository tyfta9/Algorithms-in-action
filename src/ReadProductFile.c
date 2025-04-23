#include "..\include\CarPartProduct.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// amount of files
#define FILERANGE 4
// file path length
#define PATHLEN 100
// string row length of a file
#define ROWLEN 150
// number of columns in files
#define COLNUM 8

// file path                                                TO DO - CHANGE FROM RELEVENT PATH TO ABSOLUTE
const char *fPath = "D:\\Mytki\\TudProjects\\Algorithm&Design\\Algorithms-in-action\\data\\";               
// file name
const char *fName = "line";
// file extension 
const char *fExt = ".csv";

// get total product or line count in all files excluding headers
int FGetProductCount();
// converts row of a file to product structure,
// uses specified delimeter
part RowToProduct(char *row, char *delim);
// read all product from file
void FReadProduct(part *products, int size);

// read product from file 
void FReadProduct(part *products, int size)
{
    FILE *fp = 0;
    char fullPath[PATHLEN] = {0};
    char row[ROWLEN] = {0};
    char *delim = ",";


    // go through the file range
    for(int i = 0, j = 0; i < FILERANGE; i++)
    {
        //                                                                  GetModuleFileName(NULL, fullPath, PATHLEN);
        // assemble full file path to i file
        snprintf(fullPath, PATHLEN, "%s%s%d%s", fPath, fName, i+1, fExt);
        // open the file
        fp = fopen(fullPath, "r");
        // check for successful opening
        if(fp == NULL)
        {
            fprintf(stderr, "Could not open file, path: %s\n", fullPath);
            // let user read before closing exiting program
            getchar();
            exit(1);
        }

        // skip first header row
        fgets(row, ROWLEN, fp);

        // go through products
        while(fgets(row, ROWLEN, fp) && j < size)
        {
            (*(products + j)) = RowToProduct(row, delim);
            j++;
        }

        if(j >= size)
            return;
        
        // close the file
        fclose(fp);
    }
}

// converts row of a file to product structure,
// uses specified delimeter
part RowToProduct(char *row, char *delim)
{
    part p;
    char *tokens[COLNUM] = {0};
    int size = 0;


    // start strtok and read first column
    tokens[0] = strtok(row, delim);
    size++;

    // keep reading columns until null
    while((tokens[size] = strtok(NULL, delim)) != NULL)
    {
        size++;
    }

    // check if size equal to specified column number
    if(size != COLNUM)
    {
        fprintf(stderr, "Error, wrong file format.\n");
        // let user read before closing exiting program
        getchar();
        exit(1);
    }
    
    // asign all columns to related structure variables
    p.line = atoi(tokens[0]);
    p.batch = atoi(tokens[1]);
    strcpy(p.date, tokens[2]);
    p.id = atoi(tokens[3]);
    strcpy(p.name, tokens[4]);
    strcpy(p.engine, tokens[5]);
    p.bin = atoi(tokens[6]);
    p.weight = (float)atof(tokens[7]);

    return p;
}

// time complexity is O(N),
// where N is number of rows in files
int FGetProductCount()
{
    int count = 0;
    char fullPath[PATHLEN] = {0};
    char row[ROWLEN] = {0};
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
            // let user read before closing exiting program
            getchar();
            exit(1);
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