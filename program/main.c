#include <stdio.h>
#include <string.h>

// date length
#define DATELEN 9
// name length
#define NAMELEN 30
// target engine code length
#define ENGINECODELEN 6
// amount of files
#define FILERANGE 4
// file path length
#define PATHLEN 30
// string row length of a file
#define ROWLEN 150

struct product
{
    // line code
    unsigned short line;
    // batch code
    unsigned int batch;
    // product ID
    unsigned short id;
    // bin number
    unsigned short bin;
    // product weight
    float weight;
    // batch date & time
    char date[DATELEN];
    // product name
    char name[NAMELEN];
    // target engine code
    char engine[ENGINECODELEN];   
};

// get total product or line count in all files
int FGetProductCount();

// file path
const char *fPath = "..\\data\\";
// file name
const char *fName = "line";
// file extension 
const char *fExt = ".csv";

int main(void)
{
    int size = 0;

    size = FGetProductCount();

    printf("size of array is %d\n", size);

    return 0;
}

// time complexity is O(N),
// where N is number of rows in files
int FGetProductCount()
{
    int count = 0;
    char fullPath[PATHLEN];
    char row[ROWLEN];
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
            return 0;
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