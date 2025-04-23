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

// counts total weight of all provided products
int CountTotalWeight(part *products, int size);
// looks for a part with specified weight trough the provided products
part *FindPartByWeight(part *products, int size, float weight);
// prints list of parts
void PrintParts(part *products, int size);
// sorts the products by weight
void SortByWeight(part *products, int low, int high);
// merge for merge sort 
void Merge(part *products, int low, int mid, int high);

#endif