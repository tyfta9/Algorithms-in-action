// if ReadProductFile.h is not included, do so
#if !defined(READPRODUCTFILE_H)
#define READPRODUCTFILE_H

#include "CarPartProduct.h"
// public functions of a ReadProductFile.c file

// get total product or line count in all files excluding headers
int FGetProductCount();

// read all product from file
void FReadProduct(part* products, int size);

#endif