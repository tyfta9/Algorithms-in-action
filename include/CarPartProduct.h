// if CarPartProduct.h is already included, no need to include it again
#if !defined(CARPARTPRODUCT_H)
#define CARPARTPRODUCT_H

// date length
#define DATELEN 9
// name length
#define NAMELEN 30
// target engine code length
#define ENGINECODELEN 6

typedef struct carPartProduct
{
    // line code
    int line;

    // batch code
    int batch;

    // bin number
    int bin;

    // product weight
    float weight;

    // product ID
    int id;

    // batch date & time
    char date[DATELEN];

    // product name
    char name[NAMELEN];

    // target engine code
    char engine[ENGINECODELEN];   
} 
part;

#endif