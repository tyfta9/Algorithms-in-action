// if CarPartProduct.h is already included, no need to include it again
#if !defined(CARPARTPRODUCT_H)
#define CARPARTPRODUCT_H

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

#endif