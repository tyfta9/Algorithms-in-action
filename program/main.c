#include <stdio.h>

// date length
#define DATELEN 9
// name length
#define NAMELEN 30
// target engine code length
#define ENGINECODELEN 6

// Line Code,Batch Code,Batch Date & Time,Product ID,Product Name,Target Engine Code,Bin#,Weight
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


int main(void)
{
    return 0;
}